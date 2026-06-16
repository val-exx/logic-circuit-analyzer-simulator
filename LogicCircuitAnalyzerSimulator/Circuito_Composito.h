#pragma once
#include"Sotto_albero.h"
class Circuito_Composito
{
public:
	Circuito_Composito();
	~Circuito_Composito();
	Circuito_Composito(vector<struct nodo*> & Circuit_to_insert, vector<struct nodo*> & Main_circuit, vector<string> & Links);
	vector<struct nodo*> get_composite_circuit();
	void link_pointers(struct nodo * pointer_main_circuit, struct nodo * pointer_to_insert, string & edge_name_to_insert);
	vector<string> get_name_pointers_to_link(string & str);
	bool is_assign(string & str);
	// considero assign x = a AND b
	string get_output_name(string  str);//ritorna l'output x
	string get_description(string  str);//ritorna il sottoalbero a AND b
	vector<string> get_edge_names_to_link(string & str);
	vector<string> union_description_circuit(vector<string> & description_circuit_to_insert, vector<string> & description_main_circuit, vector<string> & circuits_link);
	


private:
	vector<struct nodo*> circuit_to_insert, main_circuit;
	vector<string> links;
	vector<string> description_composite_circuit;
};

