#pragma once
#include<string>
#include<vector>
#include<fstream>
#include"Porta_logica.h"
#include"Circuito.h"
#include "Controlli.h"
using namespace std;

struct Operator {
	string operator_name;
	double from_zero_to_one;
	double from_one_to_zero;
	vector<int> output_values;
};

class Simulazione
{
public:
	Simulazione();
	~Simulazione();
	Simulazione(vector<string> & circuit_string, vector<struct nodo*> & circuit_roots, vector<vector<int>> & Input, ifstream & consumption_file);


	void set_values_after_simulation();//nella struct dei consumi degli operatori vengono aggiunti i valori 
										 // dati dalla simulazione 
	void find_and_set_leafs(struct nodo * _nodo);//trova i puntatori alle foglie e li inserisce nel vector leafs
	void set_leaf_value_for_simulation(vector<int> & input_for_leafs);

	vector<vector<string>> circuit_simulation();//simulazione che restituisce l'output 
	double get_total_consumption();//consumo totale di potenza
	struct Operator* add_operator(vector<string> & vect_str);
	vector<string> divide_string_for_divisor(string & str);

	int get_result_logic_operator(int a, int b, string & _operator);//ottiene il risultato dell'operatore
	int simulation(struct nodo * _nodo);//simulazione circuito tramite ricorsione
	int compute_waiting(vector<string> & string_file);//calcola l'attesa del circuito sequenziale ovvero
													   //il numero di clock opportuno
	int return_double_edge_value(string & str, vector<struct nodo*>::iterator & it);
	//se due o più nodi con stesso nome,ritorna il valore che uno dei nodi uguali ha assunto durante l'assegnazione
	//del valore alle foglie

	bool is_double_edge(string & str, vector<struct nodo*>::iterator & it);
	bool is_ff(string & str);//controlla data una stringa se e' un flip flop
	bool is_assign(string & str); //controlla se la stringa e' assign ... = ...
	bool is_an_operator(string & _str);//controlla se la stringa e' un operatore OR,AND,NOT,....
	bool find_operator_in_struct(string & operator_str);//cerca se un operatore(definito dal file dei consumi
														//esiste nella struct degli operatori
	bool find_operator_on_vector(string & str);//controlla se eventualmente esiste gia' un operatore (chiamato str) nel vector di operatori utilizzati nella simulazione 
							//evita le ripetizion degli operatori utilizzati in simulazione

	bool used_operator_in_operators_file();//controllo se tutti gli operatori
										  //utilizzati nella simulazione siano presenti nel file dei consumi

private:
	vector<struct nodo*> roots; //puntatori alle radici principali del circuito
	vector<struct nodo*> leafs;//puntatori alle foglie del circuito
	vector<struct Operator*> operators_pointers;
	vector<vector<int>> input;// vettore di input per la simulazione
	vector<vector<string>> output;//vettore output in uscita della simulazione
	vector<string> tmp_output;//vettore temporaneo che calcola gli output delle radici 
	vector<string> description_circuit_file;//descrizione file circuito
	vector<string> used_operators;//operatori utilizzati nel circuito

	Circuito circuit_to_control;//ottiene il tipo di circuito



	NOT _not;
	AND _and;
	NAND _nand;
	OR _or;
	XOR _xor;
	NOR _nor;
	XNOR _xnor;
	FF _ff;





};

