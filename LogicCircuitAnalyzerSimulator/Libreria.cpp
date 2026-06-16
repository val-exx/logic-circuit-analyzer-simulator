#include"Libreria.h"


Libreria::Libreria()
{
}


Libreria::~Libreria()
{
}

Libreria::Libreria(vector<string> & description_library_circuit, struct circuit * circuit_pointer)
{
	
	circuit_to_insert = circuit_pointer;
	description_composite_circuit = description_library_circuit;
}

struct circuit * Libreria::get_library_circuit()
{
	
	struct circuit * final_circuit = new struct circuit;
	vector<string>::iterator it = description_composite_circuit.begin();
	for (it; it != description_composite_circuit.end(); ++it) {
		
		if (is_instance(*it) == true) {
			if (get_circuit_name_instance(*it) == circuit_to_insert->name) {
				set_link_string(*it);
			}
			else {//il nome del circuito non corrisponde con il circuito già salvato
				final_circuit = nullptr;
				return final_circuit;//arresta funzione
			}
		}
		else {
			description_main_circuit.push_back(*it);
		}

	}

	Circuito MainCircuit(description_main_circuit);
	vector<struct nodo*> main_circuit_roots_pointers;
	main_circuit_roots_pointers = MainCircuit.get_circuit();

	Circuito_Composito CompositeCircuit(circuit_to_insert->root_pointers, main_circuit_roots_pointers, links);
	final_circuit->root_pointers = CompositeCircuit.get_composite_circuit();
	final_circuit->description = CompositeCircuit.union_description_circuit(circuit_to_insert->description, description_main_circuit, links);

	return final_circuit;
}


bool Libreria::is_instance(string str)
{
	string token, del = " ";
	size_t pos;
	pos = str.find(del);
	str.erase(0, pos + del.length());
	pos = str.find(del);
	token = str.substr(0, pos);
	if (token == "instance") { return true; }
	else { return false; }

}

string Libreria::get_circuit_name_instance(string & str)
{
	string token, del = " ";
	size_t pos;
	pos = str.find(del);
	token = str.substr(0, pos);
	return token;

}

void Libreria::set_link_string(string str)
{
	string del = "(", token;
	size_t pos;
	pos = str.find(del);
	str.erase(0, pos + del.length());
	del = ")";
	pos = str.find(del);
	str.erase(pos, str.length());
	del = ", ";
	pos = 0;
	while ((pos = str.find(del)) != string::npos) {
		token = str.substr(0, pos);
		links.push_back(token);
		str.erase(0, pos + del.length());
	}
	links.push_back(str);


}
