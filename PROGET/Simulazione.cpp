#include "Simulazione.h"

Simulazione::Simulazione()
{
}

Simulazione::~Simulazione()
{
}

Simulazione::Simulazione(vector<string> & circuit_string, vector<struct nodo*> & circuit_roots, vector<vector<int>> & Input, ifstream & consumption_file)
{
	

	roots = circuit_roots;
	description_circuit_file = circuit_string;
	input = Input;

	int it = 0;
	string str;
	vector<string> vett_string;

	
	while (!consumption_file.eof()) {
		
		getline(consumption_file, str);
		it++;
		if (it > 1 ) {
			
			vett_string = divide_string_for_divisor(str);
			struct Operator * operator_pointer = add_operator(vett_string);
			operators_pointers.push_back(operator_pointer);

		}


	}
	consumption_file.close();
	

}

void Simulazione::set_values_after_simulation()
{
	vector<struct Operator*>::iterator it_op = operators_pointers.begin();
	for (it_op; it_op != operators_pointers.end(); ++it_op) {

		if ((*it_op)->operator_name == "NOT") {
			(*it_op)->output_values = _not.get_all_values();
		}
		if ((*it_op)->operator_name == "AND") {
			(*it_op)->output_values = _and.get_all_values();
			if ((*it_op)->operator_name == "NAND") {
				(*it_op)->output_values = _nand.get_all_values();
			}
			if ((*it_op)->operator_name == "OR") {
				(*it_op)->output_values = _or.get_all_values();
			}
			if ((*it_op)->operator_name == "XOR") {
				(*it_op)->output_values = _xor.get_all_values();
			}
			if ((*it_op)->operator_name == "NOR") {
				(*it_op)->output_values = _nor.get_all_values();
			}
			if ((*it_op)->operator_name == "XNOR") {
				(*it_op)->output_values = _xnor.get_all_values();
			}
			if ((*it_op)->operator_name == "FF") {
				(*it_op)->output_values = _ff.get_all_values();
			}
		}
	}
}

void Simulazione::find_and_set_leafs(nodo * _nodo)
{
	
	if (_nodo->left == nullptr && _nodo->right == nullptr) {
		
		leafs.push_back(_nodo);
	}
	if (_nodo->left == nullptr && _nodo->right != nullptr) {
		find_and_set_leafs(_nodo->right);


	}
	if (_nodo->left != nullptr && _nodo->right == nullptr) {
		find_and_set_leafs(_nodo->left);

	}
	if (_nodo->left != nullptr && _nodo->right != nullptr) {
		find_and_set_leafs(_nodo->left);
		find_and_set_leafs(_nodo->right);


	}
}

void Simulazione::set_leaf_value_for_simulation(vector<int>& input_for_leafs)
{
	vector<int>::iterator it_input = input_for_leafs.begin();
	vector<struct nodo *>::iterator it_leafs = leafs.begin();

	for (it_input; it_input != input_for_leafs.end(); ++it_input) {


	}
}

vector<vector<string>> Simulazione::circuit_simulation()
{

	vector<vector<int>>::iterator it_esterno = input.begin();
	vector<int>::iterator it_interno = (*it_esterno).begin();
	vector<int>::iterator fine_it_interno;

	vector<struct nodo*>::iterator it_leafs = leafs.begin();
	vector<struct nodo*>::iterator it_roots = roots.begin();

	for (it_roots; it_roots != roots.end(); ++it_roots) {
		find_and_set_leafs(*it_roots);
	}
	
	it_roots = roots.begin();

	Controlli c;
	bool start_simulation = c.enough_input_for_leafs(leafs, input);
	int waiting = 0;
	if (start_simulation == false) { //in caso negativo la simulazione si ferma
		vector<string> str; str.push_back("-1"); output.push_back(str);//ritornando nel vector la stringa "-1"
		//necessaria a riconoscere nel main il tipo di errore
		return output;
	}

	if (start_simulation == true) {
		bool is_sequential=false;
		if (circuit_to_control.type_of_circuit(description_circuit_file) == "Sequential") {
			waiting = compute_waiting(description_circuit_file);
			is_sequential = true;
			vector<string> tmp;
			int output_number = roots.size();

			for (int i = 0; i < output_number; i++) {
				tmp.push_back("x");
			}

			for (int j = 0; j < waiting; j++) {
				output.push_back(tmp);
			}

		}

		it_esterno = input.begin() + waiting;
		
		for (it_esterno ; it_esterno != input.end(); ++it_esterno) {
			
			it_interno = (*it_esterno).begin();
			it_leafs = leafs.begin(); 
			
		
			for (it_leafs,it_interno; it_leafs != leafs.end() ;++it_leafs) {
				
				if (is_double_edge((*it_leafs)->info, it_leafs) == false) 
{
					(*it_leafs)->value = *it_interno;
					it_interno++;
				}

				else {
					int double_edge_value = return_double_edge_value((*it_leafs)->info,  it_leafs);
					
					if (double_edge_value == -1) {
						(*it_leafs)->value = *it_interno;
						it_interno++;
					}
					else {
						(*it_leafs)->value = double_edge_value;
					}
				}
			}
			
			for (it_roots; it_roots != roots.end(); ++it_roots) {
				
				int int_to_convert = simulation((*it_roots)->left); 
				
				tmp_output.push_back(to_string(int_to_convert));

			}

			//inizializzo tutti i valori delle foglie a -1
			it_leafs = leafs.begin();
			for (it_leafs; it_leafs != leafs.end(); ++it_leafs) {
				(*it_leafs)->value = -1;
			}

			output.push_back(tmp_output);
			tmp_output.clear();

			it_roots = roots.begin();
		}
		
		if (is_sequential == true) {
			int clk = 0;//inizializzo il colpo di clock
			vector<vector<string>>::iterator it_output = output.begin();
			vector<string>::iterator it; 
			for (it_output; it_output != output.end(); ++it_output) {
				clk++;
				it = (*it_output).begin();
				(*it_output).insert(it, to_string(clk));
			}

		}
		return output;
	}
	
}

double Simulazione::get_total_consumption()
{
	
	
	double final_result = 0;
	if (used_operator_in_operators_file() == false) { final_result = -1; }
	else {
		set_values_after_simulation();


		bool before_is_one = false;
		bool before_is_zero = false;

		vector<struct Operator*>::iterator it_op = operators_pointers.begin();
		for (it_op; it_op != operators_pointers.end(); ++it_op) {

			vector<int>::iterator it_values = (*it_op)->output_values.begin();
			vector<int>::iterator end_it_values = (*it_op)->output_values.end();
			double zero_one = (*it_op)->from_zero_to_one;
			double one_zero = (*it_op)->from_one_to_zero;
			for (it_values; it_values != end_it_values; ++it_values) {

				if (*it_values == 1) {

					if (before_is_zero == true) {
						final_result += zero_one;
					}
					before_is_one = true;
				}
				if (*it_values == 0) {

					if (before_is_one == true) {
						final_result += one_zero;
					}
					before_is_zero = true;
				}
			}
			before_is_one = false;
			before_is_zero = false;

		}

	}return final_result;
}

Operator * Simulazione::add_operator(vector<string> & vect_str)
{
	struct Operator * neww = new struct Operator;
	string Name = *(vect_str.begin());
	string a = *(vect_str.begin() + 1);
	string b = *(vect_str.begin() + 2);

	neww->operator_name = Name;
	neww->from_zero_to_one = stod(a);
	neww->from_one_to_zero = stod(b);

	return neww;
}

vector<string> Simulazione::divide_string_for_divisor(string & str)
{
	vector<string> prova;
	string del = ";", token;
	size_t pos = 0;
	while ((pos = str.find(del)) != string::npos) {
		token = str.substr(0, pos);
		prova.push_back(token);
		str.erase(0, pos + del.length());

	}
	prova.push_back(str);
	return prova;
}

bool Simulazione::is_an_operator(string & _str)
{
	if (_str == "NOT" || _str == "AND" || _str == "NAND" || _str == "OR" || _str == "XOR" || _str == "NOR" || _str == "XNOR" || is_ff(_str) == true) { return true; }
	else { return false; }

}

bool Simulazione::find_operator_in_struct(string & operator_str)
{
	bool find_it = false;


	vector<struct Operator*>::iterator it_op = operators_pointers.begin();
	for (it_op; it_op != operators_pointers.end(); ++it_op) {
		if ((*it_op)->operator_name == operator_str) {
			find_it = true;
			return find_it;
		}

	}
	if (find_it == false) { return find_it; }
}

bool Simulazione::find_operator_on_vector(string & str)
{
	vector<string>::iterator it = used_operators.begin();
	for (it; it != used_operators.end(); ++it) {
		if (*it == str) { return true; }
	}
	return false;
}

bool Simulazione::used_operator_in_operators_file()
{
	vector<string>::iterator it1 = used_operators.begin();
	vector<struct Operator*>::iterator it2 = operators_pointers.begin(), end_it2;
	
	bool flag = true;
	bool find;
	for (it1; it1 != used_operators.end(); ++it1) {

		it2 = operators_pointers.begin();
		end_it2 = operators_pointers.end();
		find = false;

		for (it2; it2 != end_it2; ++it2) {
			
			if (*it1 == (*it2)->operator_name) {
				find = true;
			}

		}
		if (find == false) {
			flag = false;
		}

	}
	return flag;
}

int Simulazione::get_result_logic_operator(int a, int b, string & _operator)
{
	
	if (find_operator_on_vector(_operator) != true && is_ff(_operator) != true) { used_operators.push_back(_operator); }
	if (find_operator_on_vector(_operator) != true && is_ff(_operator) == true) { used_operators.push_back("FF"); }

	if (_operator == "OR") {

		_or.set_two_input(a, b);
		return _or.get_result();
	}
	if (_operator == "AND") {
		_and.set_two_input(a, b);
		return _and.get_result();
	}
	if (_operator == "NOT") {
		_not.set_one_input(a); 
		return _not.get_result();
	}
	if (_operator == "NAND") {
		_nand.set_two_input(a, b);
		return _nand.get_result();
	}
	if (_operator == "XOR") {
		_xor.set_two_input(a, b);
		return _xor.get_result();
	}
	if (_operator == "NOR") {
		_nor.set_two_input(a, b);
		return _nor.get_result();
	}
	if (_operator == "XNOR") {
		_xnor.set_two_input(a, b);
		return _xnor.get_result();
	}
	if (is_ff(_operator) == true) {
		_ff.set_one_input(a);
		return _ff.get_result();
	}
}

int Simulazione::simulation(nodo * _nodo)
{


	if (is_an_operator(_nodo->info) != true) {
	
		return _nodo->value;
	}
	else {

		if (_nodo->info == "NOT" || is_ff(_nodo->info) == true) {
			
			int left_val = simulation(_nodo->left); 
			int right_val = -1;
			return get_result_logic_operator(left_val, right_val, _nodo->info);
		}
		else {
			int left_val = simulation(_nodo->left);
			int right_val = simulation(_nodo->right);
			return get_result_logic_operator(left_val, right_val, _nodo->info);
		}

	}
}

int Simulazione::compute_waiting(vector<string> & string_file)
{
	vector<string> flipflop, operations;
	size_t pos1 = 0;
	size_t pos2 = 0;
	int waiting = 0;
	string del = " ", token;

	vector<string>::iterator it = string_file.begin();

	for (it = string_file.begin(); it != string_file.end(); ++it) {
		if (is_assign(*it) == false) {
			string str = *it;
			string component_name;
			pos1 = str.find(del);
			component_name = str.substr(0, pos1);

			flipflop.push_back(component_name);

			 str.erase(0, pos1 + 3);
			for (int n = 0; n < str.size(); n++) {
				if ((str[n] == '(') || (str[n] == ')')) {
					str.erase(n, 1);
				}
			}
			
			operations.push_back(str);


		}
	}
	vector<string>::iterator it2 = flipflop.begin(), it3 = operations.begin();
	int i = 0;
	int j;
	int flag = 0;
	for (it2 = flipflop.begin(); it2 != flipflop.end(); ++it2) {

		i = i + 1;
		string str1;
		string str2;
		str1 = *it2;
		j = 0;
		flag = 0;
		for (it3 = operations.begin(); it3 != operations.end(); ++it3) {

			j = j + 1;
			str2 = *it3;


			while (((pos2 = str2.find(del)) != string::npos) && flag == 0) {

				token = str2.substr(0, pos1);
				if (token == str1) {

					if (j > i) {
						if (flag == 0)
							waiting++;
						flag = 1;
					}
					if (j < i) {
						if (flag == 0)
							waiting++;
						flag = 1;
					}

				}

				str2 = str2.erase(0, pos2 + 1);
			}

		}

	}
	return waiting;

}

int Simulazione::return_double_edge_value(string & str, vector<struct nodo*>::iterator & it)
{
	vector<struct nodo*>::iterator it1 = leafs.begin();
	int match_value;

	for (it1; it1 != leafs.end(); ++it1) {
		if ((*it1)->info == str && it1 != it) {

			match_value = (*it1)->value;

		}

	}

	return match_value;
}

bool Simulazione::is_double_edge(string & str, vector<struct nodo*>::iterator & it)
{
	vector<struct nodo*>::iterator it1 = leafs.begin();
	bool find = false;

	for (it1; it1 != leafs.end(); ++it1) {
		if ((*it1)->info == str && it1 != it) { find = true; }

	}

	return find;
}

bool Simulazione::is_ff(string & str)
{
	if (*str.begin() == 'F' && *(str.begin() + 1) == 'F') { return true; }
	else { return false; }
}

bool Simulazione::is_assign(string & str)
{
	size_t pos = 0;
	string del = " ", token;
	pos = str.find(del);
	token = str.substr(0, pos);
	if (token == "assign") { return true; }
	if (token != "assign") { return false; }
}
