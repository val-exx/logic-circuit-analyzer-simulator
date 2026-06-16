#include "Circuito.h"

Circuito::Circuito()
{
}


Circuito::~Circuito()
{
}

Circuito::Circuito(vector<string>& description)
{
	file_circuit = description;
}

vector<struct nodo*> Circuito::get_sequential_circuit()
{


	Circuito_Sequenziale cs(file_circuit);
	vector<struct nodo *> roots_sequential = cs.get_sequential_circuit();
	return roots_sequential;

}

vector<struct nodo*> Circuito::get_combinatorial_circuit()
{
	Circuito_Combinatorio cc(file_circuit);
	vector<struct nodo *> roots_combinatorial = cc.get_roots_pointers_of_circuit();
	return roots_combinatorial;
}

string Circuito::type_of_circuit(vector<string>& circuit_description)
{
	string flag;
	vector<string>::iterator it = circuit_description.begin();
	string del = " ";
	string token;
	size_t pos = 0;
	if (is_a_flip_flop(*it) == true) {
		flag = "Sequential";
	}
	else { flag = "Combinatorial"; }
	return flag;
}




vector<struct nodo*>  Circuito::get_circuit()
{
	string type_circuit = type_of_circuit(file_circuit); 
	if (type_circuit == "Combinatorial") {
		roots_pointers = get_combinatorial_circuit();
	}
	if (type_circuit == "Sequential") {
		roots_pointers = get_sequential_circuit();
	}
	return roots_pointers;
}

bool Circuito::is_a_flip_flop(string & str)
{

	if (*str.begin() == 'F' && *(str.begin() + 1) == 'F') { return true; }
	else { return false; }
}




