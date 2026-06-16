#pragma once
#include <string>
#include<vector>
#include<algorithm>
#include"Circuito.h"
using namespace std;

struct logical_cones {
	string output_name;
	vector<string> inputs_name;
};

class Analisi
{
public:
	Analisi();
	~Analisi();
	Analisi(vector<struct nodo*> & pointers, vector<string> & description);

	//funzioni per i coni logici
	vector<struct logical_cones*> return_logical_cones();
	struct logical_cones * add_struct(string & output_str);
	void set_input_for_logical_cones(struct nodo * edge);
	bool double_edge(string & str);
	
	//funzioni per il path massimo
	int return_max_depth();
	int maxDepth(struct nodo * root);

	//funzioni per il path minimo
	int return_min_depth();
	int minDepth(struct nodo * root);

	//funzioni per il loop
	vector<string> compute_loop();
	bool is_assign(string & str);
	int min_loop_value();
	int max_loop_value();
	string min_loop_str();
	string max_loop_str();

	

private:
	vector<struct logical_cones*> vector_logical_cones;
	vector<struct nodo*> circuit;
	
	vector<string> circuit_description;
	vector<string> input_logical_cones;
	vector<string> flipflop;
	vector<string> operations;
	vector<string> components;
	vector<string> loops;

	vector<int> max_depth;
	vector<int> min_depth;

	string str_min_loop;
	string str_max_loop;

	int min_loop;
	int max_loop;

	
};

