#include "Circuito_Composito.h"



Circuito_Composito::Circuito_Composito()
{
}


Circuito_Composito::~Circuito_Composito()
{
}
Circuito_Composito::Circuito_Composito(vector<struct nodo*> & Circuit_to_insert, vector<struct nodo*>& Main_circuit, vector<string>& Links)
{
	circuit_to_insert = Circuit_to_insert;
	main_circuit = Main_circuit;
	links = Links;
}

vector<struct nodo*> Circuito_Composito::get_composite_circuit()
{
	vector<string>::iterator it_link = links.begin();
	vector<struct nodo*>::iterator it_main = main_circuit.begin();
	vector<struct nodo*>::iterator it_ins = circuit_to_insert.begin();
	vector<string> str;
	struct nodo * edge1 = nullptr;
	


	for (it_link; it_link != links.end(); ++it_link) {
		str = get_name_pointers_to_link(*it_link);

		it_ins = circuit_to_insert.begin();

		for (it_ins; it_ins != circuit_to_insert.end(); ++it_ins) {

			if (*str.begin() == (*it_ins)->info) {
				it_main = main_circuit.begin();

				for (it_main; it_main != main_circuit.end(); ++it_main) {
					
					link_pointers(*it_main, *it_ins, *(str.begin() + 1));
				}
				
			}
		}

	}
	return main_circuit;
}

void Circuito_Composito::link_pointers(nodo * pointer_main_circuit, nodo * pointer_to_insert, string & edge_name_to_insert)
{

	if (pointer_main_circuit != nullptr) {
		if (pointer_main_circuit->info == edge_name_to_insert) {
			if (pointer_main_circuit->left == nullptr && pointer_main_circuit->right == nullptr) {
				pointer_main_circuit->left = pointer_to_insert->left;
			}
			if (pointer_main_circuit->left == nullptr && pointer_main_circuit->right != nullptr) {
				pointer_main_circuit->left = pointer_to_insert->left;
			}
			if (pointer_main_circuit->left != nullptr && pointer_main_circuit->right == nullptr) {
				pointer_main_circuit->right = pointer_to_insert->left;
			}
		}
		else {
			link_pointers(pointer_main_circuit->left, pointer_to_insert, edge_name_to_insert);
			link_pointers(pointer_main_circuit->right, pointer_to_insert, edge_name_to_insert);
		}
	}
}



vector<string> Circuito_Composito::get_name_pointers_to_link(string & str)
{
	vector<string> vect_str;
	string tmp1, tmp2;
	string del1 = " = ", del2 = ".";
	size_t pos1, pos2;
	pos1 = str.find(del1);
	tmp1 = str.substr(0, pos1);
	tmp2 = str.substr(pos1 + del1.length(), str.length());

	pos2 = tmp1.find(del2);
	tmp1.erase(pos2, del2.length());
	vect_str.push_back(tmp1);
	vect_str.push_back(tmp2);
	return vect_str;

}



bool Circuito_Composito::is_assign(string & str)
{
	size_t pos = 0;
	string del = " ", token;
	pos = str.find(del);
	token = str.substr(0, pos);
	if (token == "assign") { return true; }
	if (token != "assign") { return false; }
}

string Circuito_Composito::get_output_name(string str)
{
	string del2 = " ", del1 = " = ";
	size_t pos1, pos2;
	string token;
	pos1 = str.find(del1);
	str.erase(pos1, str.length());
	pos2 = str.find(del2);
	token = str.substr(pos2 + del2.length(), str.length());
	return token;
}

string Circuito_Composito::get_description(string str)
{
	string token, del = " = ";
	size_t pos;
	pos = str.find(del);
	token = str.substr(pos + del.length(), str.length());
	return token;
}

vector<string> Circuito_Composito::get_edge_names_to_link(string & str)
{
	vector<string> vect_str;
	string tmp1, tmp2;
	string del1 = " = ", del2 = ".";
	size_t pos1, pos2;
	pos1 = str.find(del1);
	tmp1 = str.substr(0, pos1);
	tmp2 = str.substr(pos1 + del1.length(), str.length());

	pos2 = tmp1.find(del2);
	tmp1.erase(pos2, del2.length());
	vect_str.push_back(tmp1);
	vect_str.push_back(tmp2);
	return vect_str;
}

vector<string> Circuito_Composito::union_description_circuit(vector<string>& description_circuit_to_insert, vector<string>& description_main_circuit, vector<string>& circuits_link)
{
	vector<string>::iterator it_link = circuits_link.begin();
	vector<string>::iterator it_insert = description_circuit_to_insert.begin();
	string str, del = " = ";
	vector<string> tmp;



	for (it_link; it_link != circuits_link.end(); ++it_link) {
		tmp = get_edge_names_to_link(*it_link);

		it_insert = description_circuit_to_insert.begin();

		for (it_insert; it_insert != description_circuit_to_insert.end(); ++it_insert) {

			if (is_assign(*it_insert) == true) {

				str = get_output_name(*it_insert);

				if (*tmp.begin() == str) {

					description_main_circuit.insert(description_main_circuit.begin(), *(tmp.begin() + 1) + del + get_description(*it_insert));
				}

			}
		}

	} return description_main_circuit;
}