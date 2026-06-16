#include "Analisi.h"



Analisi::Analisi()
{
}


int Analisi::return_max_depth()
{
	vector<struct nodo*>::iterator it = circuit.begin();
	for (it; it != circuit.end(); ++it) {
		max_depth.push_back( maxDepth(*it));
		
	}
	sort(max_depth.begin(), max_depth.end());
	return *(max_depth.end() - 1);

}

vector<struct logical_cones*> Analisi::return_logical_cones()
{
	vector<struct nodo*>::iterator it_root = circuit.begin();
	

	for (it_root; it_root != circuit.end(); ++it_root) {
		set_input_for_logical_cones(*it_root);//imposta le foglie dell'output nel vector
		struct logical_cones * root = add_struct((*it_root)->info);//crea struttura di un cono logico
		root->inputs_name = input_logical_cones;//imposta gli input
		vector_logical_cones.push_back(root);//aggiunge la struttura nel vector
		input_logical_cones.clear();//pulisce il vettore degli input 
	}
	return vector_logical_cones;
}

struct logical_cones * Analisi::add_struct(string & output_str)
{
	 struct logical_cones * neww = new struct logical_cones;
	neww->output_name = output_str;
	return neww;

}

void Analisi::set_input_for_logical_cones(nodo * edge)
{
	if (edge != nullptr) {
		if (edge->left == nullptr && edge->right == nullptr) {
			if (double_edge(edge->info) != true) { input_logical_cones.push_back(edge->info); }
		}
		else {
			set_input_for_logical_cones(edge->left);
			set_input_for_logical_cones(edge->right);
		}
	}
}

bool Analisi::double_edge(string & str)
{
	vector<string>::iterator it = input_logical_cones.begin();
	bool find = false;
	for (it; it != input_logical_cones.end(); ++it) {
		if (*it == str) {
			find = true;
		}
	}return find;
}


int Analisi::maxDepth(nodo * root)
{
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
		return 1;

	if (!root->left)
		return maxDepth(root->right) + 1;

	if (!root->right)
		return maxDepth(root->left) + 1;

	return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	
}

int Analisi::return_min_depth()
{
	vector<struct nodo*>::iterator it = circuit.begin();
	for (it; it != circuit.end(); ++it) {
		min_depth.push_back(minDepth(*it));

	}
	sort(min_depth.begin(), min_depth.end());
	return *(min_depth.begin());
	
}

int Analisi::minDepth(nodo * root)
{
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
		return 1;

	if (!root->left)
		return minDepth(root->right) + 1;

	if (!root->right)
		return minDepth(root->left) + 1;

	return min(minDepth(root->left), minDepth(root->right)) + 1;
}

vector<string> Analisi::compute_loop()
{
	size_t pos = 0, pos1;
	size_t pos2 = 0;
	size_t pos3 = 0;
	int waiting = 0;
	string del = " ", del1 = " = ", _token, _token2, loop, components;

	vector<string>::iterator it = circuit_description.begin();

	for (it; it != circuit_description.end(); ++it) {
		
		if (is_assign(*it) == false) {
			string str_tmp;
			string component_name;

			pos = (*it).find(del);
			component_name = (*it).substr(0, pos);
			flipflop.push_back(component_name);
			pos1 = (*it).find(del1);
			str_tmp = (*it).substr(pos1 + del1.length(), (*it).length());

			for (int n = 0; n < str_tmp.length(); n++) {
				if ((str_tmp[n] == '(') || (str_tmp[n] == ')')) {
					str_tmp.erase(n, 1);
				}
			}

			operations.push_back(str_tmp);


		}
	}

	vector<string>::iterator it_ff = flipflop.begin(), it_operation, it_loops;

	int i = 0,j;
	
	
	for (it_ff; it_ff != flipflop.end(); ++it_ff) {
		
		i++;
		//string str1;
		//string str2;
		//str1 = *it_ff;
		
		j = 0;
		for (it_operation = operations.begin(); it_operation != operations.end(); ++it_operation) {
			
			j++;
			string str2 = (*it_operation);
			
			while ((pos2 = str2.find(del)) != string::npos)  {
				
				_token = str2.substr(0, pos2);
				
				if (_token == *it_ff && j<i) {

						loop = *(it_ff - (i - j)) + " " + (*it_operation) + " " + (*(it_operation + (i - j)));
						loops.push_back(loop);
						

				}

				str2.erase(0, pos2 + 1);
			}
			
		}
		
	}

	if (!loops.empty()) {

		int counter;
		for (it_loops=loops.begin(); it_loops != loops.end(); it_loops++) {
			components = *it_loops;
			counter = 0;
			while ((pos3 = components.find(del)) != string::npos) {
				_token2 = components.substr(0, pos3);
				components.erase(0, pos3 + del.size());
				counter ++;
			}
			counter++;

			if (it_loops == loops.begin()) {

				max_loop = counter;
				min_loop = counter;
				str_max_loop = *it_loops;
				str_min_loop = *it_loops;

			}
			if (counter > max_loop) {
				max_loop = counter;
				str_max_loop = *it_loops;
			}
			if (counter < min_loop) {
				min_loop = counter;
				str_min_loop = *it_loops;
			}

		}

	}
	
	return loops;
}

bool Analisi::is_assign(string & str)
{
	size_t pos = 0;
	string del = " ", token;
	pos = str.find(del);
	token = str.substr(0, pos);
	if (token == "assign") { return true; }
	if (token != "assign") { return false; }
}

int Analisi::min_loop_value()
{
	return min_loop;
}

int Analisi::max_loop_value()
{
	return max_loop;
}

string Analisi::min_loop_str()
{
	return str_min_loop;
}

string Analisi::max_loop_str()
{
	return str_max_loop;
}



Analisi::~Analisi()
{
}

Analisi::Analisi(vector<struct nodo*>& pointers, vector<string>& description)
{
	circuit = pointers;
	circuit_description = description;
}
