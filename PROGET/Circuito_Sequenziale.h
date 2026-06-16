#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<iterator>
#include"Sotto_albero.h"

using namespace std;

class Circuito_Sequenziale
{
public:
	Circuito_Sequenziale();
	~Circuito_Sequenziale();
	Circuito_Sequenziale(vector<string> & str_);
	bool is_assign(string & str);
	void find_and_set_nodes_match(struct nodo * root1, struct nodo * root2);
	vector<struct nodo*> get_sequential_circuit();
	vector<string> divide_string_by_divisor(string & str_);
	string divide_string_by_assign(string & str_);

private:
	vector<string> links;
	vector<struct nodo*> pointers_circuit;
	vector<struct nodo *> subtree_pointers;


	

};