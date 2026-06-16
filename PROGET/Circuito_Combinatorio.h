#pragma once
#include<vector>
#include<string>
#include<iterator>
#include"Sotto_albero.h"
using namespace std;

class Circuito_Combinatorio
{
public:
	Circuito_Combinatorio();//distruttore
	~Circuito_Combinatorio();//costruttore di default
	Circuito_Combinatorio(vector<string> & string_);//costruttore che ha la stringa come parametro
	vector<struct nodo *> get_roots_pointers_of_circuit();//metodo che ritorna i puntatori alla struttura delle radici del singolo circuito


private:

	vector<struct nodo *> pointers_roots;//vector che contiene gli alberi (può essere piu' di uno nel caso in cui siano isolati)
	vector<string> str;//variabile stringa presa dal costruttore necessaria a lavorarci e costruirci l'albero
	vector<string>::iterator it;//iteratore che scorre i vector
	
};

