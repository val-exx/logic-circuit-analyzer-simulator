#pragma once
#include"Circuito_Combinatorio.h"
#include"Circuito_Composito.h"
#include"Circuito_Sequenziale.h"
#include<string>
#include<vector>


class Circuito
{
public:
	Circuito();
	~Circuito();
	Circuito(vector<string> & description);

	vector<struct nodo*> get_sequential_circuit();
	vector<struct nodo*> get_combinatorial_circuit();
	string type_of_circuit(vector<string> & circuit_description);
	vector<struct nodo*> get_circuit();//funzione chiamata dal main per costruire l'albero del circuito
	bool is_a_flip_flop(string & str);
	

private:
	vector<string> file_circuit;
	string circuit_name;
	string kind_of_circuit;
	vector<struct nodo*> roots_pointers;
	vector<struct circuit*> circuit_pointers;

};

