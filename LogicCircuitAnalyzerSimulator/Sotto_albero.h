#pragma once
#include <vector>
#include <string>
#include<iostream>


using namespace std;

 struct nodo {
	int value;
	string info;
	struct nodo * left;
	struct nodo * right;
	struct nodo * parent;
	

};
class Sotto_albero
{
public:

	Sotto_albero();
	~Sotto_albero();
	

	struct nodo * get_sub_tree_left(string & str_sub_tree);
	struct nodo * get_sub_tree_right(string & str_sub_tree);
	struct nodo * get_final_sub_tree(string & str_);

	vector<string> divide_string_by_space(string & _str, int _pos1, int _pos2);
	 struct nodo * add_nodo(string & _valore);
	int find_closed_index(string & _str, int _beg, int _end);//trova indice corrispondente alla parentesi aperta
	int find_opened_index(string & str, int _beg, int _end);
	struct nodo * get_sub_tree(vector<string> & _vect);
	struct nodo * get_sub_tree_dx_leaf (vector<string> & _vect);
	struct nodo *  get_sub_tree_sx_leaf(vector<string> & _vect);
	struct nodo * get_union_sub_tree(struct nodo * sub_tree_sx, struct nodo * _root, struct nodo *sub_tree_dx);
    struct nodo *  get_union_root_sub_tree_sx(struct nodo * sub_tree_sx, struct nodo *_root);
	struct nodo * get_union_root_sub_tree_dx(struct nodo * sub_tree_dx, struct nodo *_root);
	string find_main_root(string & _str);
	struct nodo * get_tree(struct nodo * sx_, struct nodo * root_, struct nodo * dx_);
	bool is_not(vector<string> & vect);
	struct nodo * get_sub_tree_not(vector<string> & _not);
	
	
	

private:

	struct nodo * sub_tree_left;
	struct nodo * sub_tree_right;
    struct nodo * main_root;
	
	
	
	

	
};

