#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include<iterator>
#include"Simulazione.h"
#include"Circuito.h"
#include"Libreria.h"


using namespace std;
class Controlli
{
public:
	Controlli();
	~Controlli();

	
	int file_circuit_is_correct(ifstream & _in);//controllo se file di definizione del circuito è corretto
	int file_input_is_correct(ifstream & _in);//controllo se file di input contiene 0 e 1
	bool is_vectorial(string & vectorial_string);//controlla se output/input sono di tipo vettoriale
	bool there_is_feedback(string & string_file);//controlla se c'è feedback per i circuiti combinatori 
	bool enough_input_for_leafs(vector<struct nodo*> & leafs, vector<vector<int>> & input);
	//controlla se ci sono abbastanza input per le foglie cioè numero input>=numero foglie
	bool is_an_operator(string & str);//controlla se e' una porta logica 
	bool is_ff(string & str);//controllo se e' un flipflop
	bool is_instance(string str);//controllo se la riga e' instance

	//scrittura risultato simulazione su file
	void write_simulation_file(ofstream & out, vector<vector<string>> & output, double & power_analysis);
	void set_string_input_name(string & string_);//divido la stringa letta da file in stringhe input
	void set_string_output_name(string & string_);//divido la stringa letta da file in stringhe output
    void get_input_vectorial(string & vectorial_input);//ottiene a[2] come a1,a2
	void get_output_vectorial(string & vectorial_output);//ottiene b[2] come b1,b2
	void set_string_input_output_name_in_subtree(string  string_);//divido input e output nei sotto alberi
	
	string open_return_library_file_name(ifstream & in); //legge e restituisce nel percorso file il nome
	//del file da aprire


	
	vector<vector<int>>  return_numbers_input_for_simulation();//ritorna input per la simulazione
	vector<string> return_vector_string_file();//ritorna le stringhe del file del circuito
	string return_circuit_name();//ritorna il nome del circuito
	



private:
	
	vector<string> string_file;//vector di nome input,nome output e collegamenti 
	string circuit_name; //serve per identificare il tipo di circuito
	vector<vector<int>> input_values;
	vector<string> input_name, output_name;//input e output definiti 
	vector<string> input_name_in_subtree, output_name_in_subtree;//input e output definiti dai sottoalberi 
};

