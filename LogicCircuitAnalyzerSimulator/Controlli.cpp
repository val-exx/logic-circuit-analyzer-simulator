#include "Controlli.h"


Controlli::Controlli()
{
}

Controlli::~Controlli()
{
}


int Controlli::file_circuit_is_correct(ifstream & _in)
{
	
	string endmodule = "endmodule", _assign = "assign", startmodule="module";
	string carattere_parentesi_aperta = "(";


	string string_input, string_output;
	string word, word1;

	bool flag_chiusura = 0;
	bool is_combinatorial=true;
	bool is_composite = false;

	int count = 0,final_result=-4;

	while (!_in.eof())
	{
		count++;
		_in >> startmodule >> circuit_name >> carattere_parentesi_aperta;

		while (flag_chiusura != 1) {
			_in >> word;
			count++;
			if (word == "clk") { is_combinatorial = false; }

			if (word == "input") {
				getline(_in, string_input); 
				set_string_input_name(string_input);

			}

			if (word == "output") {
				getline(_in, string_output);
				set_string_output_name(string_output);
			}
			if (word == ");") {
				getline(_in, word1); flag_chiusura = 1;
			}
		}

		flag_chiusura = 0;
		while (flag_chiusura != 1) {
			count++;
			getline(_in, word1); 
			if (word1 == endmodule) { flag_chiusura = 1; }
			else {
				string_file.push_back(word1);
				if (is_instance(word1) == true) { is_composite = true; }
			}


		}
	}
	
	if (count == 1) { final_result= 0; }//controllo se il file è vuoto

	//imposta input e output contenuti nei sotto alberi
	vector<string>::iterator it = string_file.begin();
	for (it; it != string_file.end(); ++it) {
		set_string_input_output_name_in_subtree(*it);
	}
	
	bool flag,feedback, find;
	vector<string>::iterator it1, it2;


	//controllo se e' combinatorio,in caso affermativo controllo se contiene feedback
	flag = false, feedback = false;
	if (is_combinatorial == true) {
		it1 = string_file.begin();
		for (it1; it1 != string_file.end(); ++it1) {
			if (there_is_feedback(*it1) == true) {
			flag = true;
			}
		}
		if (flag == true) { 
			feedback = true;
			
		}//errore il circuito combinatorio contiene feedback
	}


//controllo output/input contenuti siano corretti
	 it1 = output_name.begin(); it2 = output_name_in_subtree.begin();
     flag = true;
	
	for (it2; it2 != output_name_in_subtree.end(); ++it2) {
		it1 = output_name.begin();
		find = false;
		for (it1; it1 != output_name.end(); ++it1) {
			
			if (*it1 == *it2) {
				find = true;
			}
		}
		if (find == false) {
			flag = false;
		}
	}
	if (flag == false) {
		final_result =-1;//errore output non corrispondente
	}

	
		it1 = input_name.begin(); it2 = input_name_in_subtree.begin();
		flag = true;

		for (it2; it2 != input_name_in_subtree.end(); ++it2) {
			it1 = input_name.begin(); 
			find = false;
			for (it1; it1 != input_name.end(); ++it1) {
				if (*it1 == *it2) {
					find = true;
				}
			}
			if (find == false) {
				flag = false;
			}
		}
		if (flag == false) {
			final_result = -2;//errore input non corrispondente
		}
		if (feedback == true && final_result == -2) { final_result = -3; }
	

	return final_result;
	}

int Controlli::file_input_is_correct(ifstream & _in)//controllo se file input contiene solo 0 e 1
{ 
	string string_input, string_tmp; 
	bool correct_input_format = true;
	int count = 0,result;
	
	vector<int> vector_input;
	while (!_in.eof() && correct_input_format != false)
	{
		count++;

		getline(_in, string_input);
		
			
		for (int i = 0; i < string_input.size(); i++) {
			if (string_input[i] != '0' && string_input[i] != '1') {
				correct_input_format = false;
				vector_input.clear();
			}
			else {

				string_tmp = string_input[i];
				vector_input.push_back(stoi(string_tmp));

			}
		}
		if (correct_input_format == true) {

			input_values.push_back(vector_input);
			vector_input.clear();
		}
		else { input_values.clear(); }
	
	}
	if (count == 1 ) {result= 1; }
	if (correct_input_format == false) { input_values.clear(); result= 2; }
	if (correct_input_format == true && count!=1) {  result= 3; }
	
	return result;


}

void Controlli::write_simulation_file(ofstream & out, vector<vector<string>>& output_simulation, double & power_analysis)
{
	vector<vector<string>>::iterator it_output_external;
	it_output_external = output_simulation.begin();
	vector<string>::iterator it_output_internal,end_it_output_internal;

	
		out << "Risulatato della simulazione : " << endl << endl;
		
		for (it_output_external = output_simulation.begin(); it_output_external != output_simulation.end(); ++it_output_external) {
			it_output_internal = (*it_output_external).begin();
			end_it_output_internal = (*it_output_external).end();
			
			for (it_output_internal; it_output_internal != end_it_output_internal; ++it_output_internal) {
				out << *it_output_internal << " ";

			}out << endl;

		}


		out << endl << endl << "Consumo totale di potenza del circuito : ";

		out << power_analysis;
		out.close();
	
}

void Controlli::set_string_input_name(string & string_)
{
	
	string_.erase(0, 1); 
	string delimeter = ", ";
	size_t pos = 0;
	string token;
	size_t found = string_.find(delimeter);

	if (found == string::npos) { 
		token = string_.substr(0, string::npos); 
	if (is_vectorial(token) == true)//controlla se il token è di tipo vettoriale
	{ get_input_vectorial(token);}
	else { input_name.push_back(token);}
	} 



	else {
		
		while ((pos = string_.find(delimeter)) != string::npos) {
			token = string_.substr(0, pos);
			if (is_vectorial(token) == true)//controlla se il token è di tipo vettoriale
			{
				get_input_vectorial(token);
			}
			else {
				
				input_name.push_back(token);
			}

			string_.erase(0, pos + delimeter.size());

		}input_name.push_back(string_); 
	}
}

void Controlli::set_string_output_name(string & string_)
{
	string_.erase(0, 1);
	string delimeter = ", ";
	size_t pos = 0;
	string token;
	size_t found = string_.find(delimeter);
	if(found == string::npos){
		token = string_.substr(0, string::npos);
		if (is_vectorial(token) == true)//controlla se il token è di tipo vettoriale
		{
			get_output_vectorial(token);
		}
		else {
			output_name.push_back(token);
		}
	}
	else {
	while ((pos = string_.find(delimeter)) != string::npos) {
		token = string_.substr(0, pos);
		//controlla se input vettoriale
		if (is_vectorial(token) == true) {
			get_output_vectorial(token);
		}
		else {
			output_name.push_back(token);
		}
		string_.erase(0, pos + delimeter.size());
	}
	output_name.push_back(string_);
	}
}

bool Controlli::is_vectorial(string & vectorial_string)
{
	bool flag = false;
	for (int i = 0; i < vectorial_string.size(); i++) {
		if (vectorial_string[i] == '[') {
			flag = true;
		}
		if (vectorial_string[i] == ']' && flag==true) {
			flag = true;
		}
		

	}
	return flag ;
}

void Controlli::get_input_vectorial(string & vectorial_input)
{
	
	string del1 = "[";
	string del2 = "]";
	size_t pos1 = vectorial_input.find(del1);
	size_t pos2 = vectorial_input.find(del2);

	string number = vectorial_input.substr(pos1 + 1, pos2 - 2);
	string str_ = vectorial_input.substr(0, pos1);
	int n = stoi(number);
	for (int m = 0; m < n; m++) {
		string tmp = str_ +"[" +to_string(m)+"]";
		input_name.push_back(tmp);
	}


}

void Controlli::get_output_vectorial(string & vectorial_output)
{
	string del1 = "[";
	string del2 = "]";
	size_t pos1 = vectorial_output.find(del1);
	size_t pos2 = vectorial_output.find(del2);

	string number = vectorial_output.substr(pos1 + 1, pos2 - 2);
	string str_ = vectorial_output.substr(0, pos1);
	int n = stoi(number);
	for (int m = 0; m < n; m++) {
		string tmp = str_ + "[" + to_string(m) + "]";
		output_name.push_back(tmp);
	}

}

void Controlli::set_string_input_output_name_in_subtree(string  string_)
{
	if (is_instance(string_) != true) {
		string del = " = ", token, token1;
		size_t pos; pos = string_.find(del);
		token = string_.substr(0, pos);
		string_.erase(0, pos + del.length());

		del = " ", pos = 0;

		while ((pos = token.find(del)) != string::npos) {
			token1 = token.substr(0, pos);
			token.erase(0, pos + del.length());
		}
		if (token1 == "assign") {
			output_name_in_subtree.push_back(token);
		}


		del = "("; pos = 0;
		while ((pos = string_.find(del)) != string::npos) {
			string_.erase(pos, del.length());
		}
		del = ")"; pos = 0;
		while ((pos = string_.find(del)) != string::npos) {
			string_.erase(pos, del.length());
		}

		del = " "; pos = 0;
		while ((pos = string_.find(del)) != string::npos) {
			token = string_.substr(0, pos);
			if (is_an_operator(token) != true) {
				input_name_in_subtree.push_back(token);
			}

			string_.erase(0, pos + del.length());
		}
		if (is_ff(string_) != true) {
			input_name_in_subtree.push_back(string_);
		}
	}

	else {
		string del = "instance ";
		size_t pos = string_.find(del);
		string_.erase(0, pos + del.length());

		del = "("; pos = 0;
		while ((pos = string_.find(del)) != string::npos) {
			string_.erase(pos, del.length());
		}
		del = ")"; pos = 0;
		while ((pos = string_.find(del)) != string::npos) {
			string_.erase(pos, del.length());
		}
		del = ", "; pos = 0; size_t pos1; string token, del1 = " = ";
		while ((pos = string_.find(del)) != string::npos) {
			token = string_.substr(0, pos);
			pos1 = token.find(del1);
			token.erase(0, pos1 + del1.length());
			if (is_ff(token) != true) { input_name_in_subtree.push_back(token); }

			string_.erase(0, pos + del.length());
		}
		pos1 = string_.find(del1);
		string_.erase(0, pos1 + del1.length());
		if (is_ff(string_) != true) { input_name_in_subtree.push_back(string_); }
	}


}

string Controlli::open_return_library_file_name(ifstream & in)
{
	size_t pos = 0;
	string file_name_to_open, str, del = "\\";
	
	int count = 0;
	while (!in.eof()) {
		count++; 
		getline(in, str); 
		pos = 0;
		while ((pos = str.find(del)) != string::npos) {
			pos = str.find(del);
			str.erase(0, pos + del.length());
			
		}
		
		file_name_to_open = str;
	}
	if (count == 0) { file_name_to_open = "vuoto"; }
	return file_name_to_open;
}

bool Controlli::there_is_feedback(string & string_file)
{
	
	string del , token;
	size_t pos;
	string OutputName,Operation;
	bool flag_feedback = false;

	    del = " = "; pos = string_file.find(del);
		OutputName = string_file.substr(0, pos); 
		Operation = string_file.substr(pos + del.length(), string_file.length()); 
		del = "assign ";
		pos = OutputName.find(del); 
		OutputName.erase(pos, pos + del.length()); 
		
		del = "("; pos = 0;
		while ((pos = Operation.find(del)) != string::npos) {
			Operation.erase(pos, del.length());
		}
		del = ")"; pos = 0;
		while ((pos = Operation.find(del)) != string::npos) {
			Operation.erase(pos, del.length());
		}
		pos = 0; del = " ";
	while ((pos = Operation.find(del)) != string::npos) {
		
		token = Operation.substr(0, pos); 
		if (token == OutputName) {
			flag_feedback = true;
		}

		Operation.erase(0, pos + 1);
	}
	if (Operation == OutputName) {
		flag_feedback = true;
	}
	return flag_feedback;



	
}

bool Controlli::enough_input_for_leafs(vector<struct nodo*>& leafs, vector<vector<int>>& input)
{
	vector<string> leafs_name;
	vector<struct nodo*>::iterator it_leafs = leafs.begin();
	vector<string>::iterator it_leafs_name;
	bool find;
	
	for (it_leafs; it_leafs != leafs.end(); ++it_leafs) {
		
		if (leafs_name.size() > 0) {
			it_leafs_name = leafs_name.begin();
			find = false;
			for (it_leafs_name; it_leafs_name != leafs_name.end(); ++it_leafs_name) {
				if (*it_leafs_name == (*it_leafs)->info) {
					find = true; 
				}
			}
			if (find != true) {
				leafs_name.push_back((*it_leafs)->info);
			}
		}
		else {
			
			leafs_name.push_back((*it_leafs)->info);
		}
	}
	
	vector<vector<int>>::iterator it_est = input.begin();
	bool flag = true;
	
	for (it_est; it_est != input.end(); ++it_est) {
		
		if (leafs_name.size() > (*it_est).size()) { flag = false; }
		
	}
	return flag;
}

bool Controlli::is_an_operator(string & str)
{
	if (str == "AND") { return true; }
	if (str == "OR") { return true; }
	if (str == "NOT") { return true; }
	if (str == "NAND") { return true; }
	if (str == "NOR") { return true; }
	if (str == "XOR") { return true; }
	if (str == "XNOR") { return true; }
	if (*str.begin() == 'F' && *(str.begin() + 1) == 'F') { return true; }
	else { return false; }
}

bool Controlli::is_ff(string & str)
{
	if (*str.begin() == 'F' && *(str.begin() + 1) == 'F') { return true; }
	else { return false; }
}

bool Controlli::is_instance(string str)
{
	size_t pos;
	string del = " ",token;
	pos = str.find(del);
	str.erase(0, pos + del.length());
	pos = str.find(del);
	token = str.substr(0, pos);
	if (token == "instance") { return true; }
	else { return false; }
}

vector<vector<int>> Controlli::return_numbers_input_for_simulation()
{
	return input_values;
}

vector<string> Controlli::return_vector_string_file()
{
	return string_file;
}

string Controlli::return_circuit_name()
{
	return circuit_name;
}










