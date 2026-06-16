#pragma once
#include<fstream>
#include<string>
#include<vector>
#include"Circuito_Composito.h"
#include"Circuito.h"
using namespace std;
struct circuit {
	string name;
	vector<string> description;
	vector<struct nodo*> root_pointers;
};
class Libreria
{
public:
	Libreria();
	~Libreria();
	Libreria(vector<string> & description_library_circuit, struct circuit * circuit_pointer);
	struct circuit * get_library_circuit();
	bool is_instance(string str);
	string get_circuit_name_instance(string & str);
	void set_link_string(string str);


private:

	struct circuit * circuit_to_insert;
	vector<string> description_composite_circuit;
	vector<string> description_main_circuit;//descrizione circuito principale a cui verrà inserito un altro
	vector<string> links;
	struct circuit * final_circuit;

};

