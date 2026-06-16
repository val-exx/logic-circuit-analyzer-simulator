#include "Circuito_Combinatorio.h"



Circuito_Combinatorio::Circuito_Combinatorio()
{
}


Circuito_Combinatorio::~Circuito_Combinatorio()
{
}



Circuito_Combinatorio::Circuito_Combinatorio(vector<string> & string_)
{
	str = string_;

}

vector<struct nodo*> Circuito_Combinatorio::get_roots_pointers_of_circuit()
{
	struct nodo * root;
	struct nodo * subtree;
	string tmp, del = " = ", del1 = "assign ", token, token_assign;
	size_t pos = 0, pos1 = 0;

	for (it = str.begin(); it != str.end(); ++it) {
		pos = (*it).find(del);
		token = (*it).substr(pos + del.size(), (*it).length());//stringa che contiene il sotto albero al nome dell'output
		(*it).erase(pos, (*it).length());
		pos1 = (*it).find(del1);
		token_assign = (*it).substr(pos1 + del1.length(), (*it).length());

		Sotto_albero sub_tree, output_assign;//creo due oggetti della classe sotto albero

		subtree = sub_tree.get_final_sub_tree(token);//ritorna il puntatore alla radice del sotto albero
		root = output_assign.add_nodo(token_assign);
		root->left = subtree;
		pointers_roots.push_back(root);

		
	}

	return pointers_roots;
}



