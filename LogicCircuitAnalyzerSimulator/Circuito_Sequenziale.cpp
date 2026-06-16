#include "Circuito_Sequenziale.h"


Circuito_Sequenziale::Circuito_Sequenziale()
{
}


Circuito_Sequenziale::~Circuito_Sequenziale()
{
}

Circuito_Sequenziale::Circuito_Sequenziale(vector<string>& str_)
{
	links = str_;
}

bool Circuito_Sequenziale::is_assign(string & str)
{
	size_t pos = 0;
	string del = " ", token;
	pos = str.find(del);
	token = str.substr(0, pos);
	if (token == "assign") { return true; }
	if (token != "assign") { return false; }
}

void Circuito_Sequenziale::find_and_set_nodes_match(nodo * root1, nodo * root2)
{
	if (root1 != nullptr) {
		if (root1->info == root2->info) {

			root1->left = root2->left;


		}
		else {
			find_and_set_nodes_match(root1->left, root2);
			find_and_set_nodes_match(root1->right, root2);
		}
	}
}


vector<struct nodo*> Circuito_Sequenziale::get_sequential_circuit()
{
	vector<string>::iterator it =links.begin();
	vector<string> str;
	struct nodo * tmp;
	struct nodo * root;
	string name_output;

	for (it; it != links.end(); ++it) {
		if (is_assign(*it) != true) {
			Sotto_albero SubTree, addNodo;
			str = divide_string_by_divisor(*it);

			tmp = SubTree.get_final_sub_tree(*(str.begin() + 1)); 
			root = addNodo.add_nodo(*(str.begin())); 

			root->left = tmp;
			subtree_pointers.push_back(root);
			str.clear();

		}
		else {
			str = divide_string_by_divisor(*it);
			Sotto_albero SubTree, addNodo;
			string output_name = divide_string_by_assign(*str.begin());
			root = addNodo.add_nodo(output_name);
			tmp = SubTree.get_final_sub_tree(*(str.begin() + 1));
			root->left = tmp;
			pointers_circuit.push_back(root);
			str.clear();


		}
	}

	vector<struct nodo *>::iterator it_root = subtree_pointers.begin();
	vector<struct nodo*>::iterator it_root_ = subtree_pointers.begin();
	struct nodo * puntatore_corrispondente;
	for (it_root; it_root != subtree_pointers.end(); ++it_root) {

		for (it_root_; it_root_ != subtree_pointers.end(); ++it_root_) {
			if (it_root != it_root_) { find_and_set_nodes_match(*it_root_, *it_root); }

		}
	}


	vector<struct  nodo*>::iterator it_pointer_circuit = pointers_circuit.begin();
	vector<struct nodo*>::iterator it_sub_tree = subtree_pointers.begin();
	for (it_pointer_circuit; it_pointer_circuit != pointers_circuit.end(); ++it_pointer_circuit) {
		for (it_sub_tree; it_sub_tree != subtree_pointers.end(); ++it_sub_tree) {

			find_and_set_nodes_match(*it_pointer_circuit, *it_sub_tree);


		}
	}

	return pointers_circuit;
}

vector<string> Circuito_Sequenziale::divide_string_by_divisor(string & str_)
{
	string del = " = ";
	string token;
	size_t pos = 0;
	vector<string> vett;
	pos = str_.find(del);
	token = str_.substr(0, pos);
	str_.erase(0, pos + del.length());
	vett.push_back(token);
	vett.push_back(str_);
	return vett;
}

string Circuito_Sequenziale::divide_string_by_assign(string & str_)
{
	string  del = "assign";
	size_t pos = str_.find(del);
	str_.erase(0, pos + del.length());
	return str_;
}