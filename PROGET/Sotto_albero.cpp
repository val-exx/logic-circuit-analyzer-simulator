#include"Sotto_albero.h"

Sotto_albero::Sotto_albero()
{
}

Sotto_albero::~Sotto_albero()
{
}

 nodo * Sotto_albero::get_sub_tree_left(string & str_sub_tree)
{
	string str = str_sub_tree;
	//costruzione sotto albero di sinistra
	if (str[0] == '(') {

		int ind_sx = find_closed_index(str, 0, str.length());
		struct nodo *sub_tree_sx = nullptr;
		struct nodo *sub_tree_dx = nullptr;


		if (str[1] == '(') { // ((a AND b) OR .......) OR .....
			int ind_sx_sx = find_closed_index(str, 1, ind_sx);
			vector<string> sx_sx = divide_string_by_space(str, 2, ind_sx_sx - 1);

			if (is_not(sx_sx) == true) { //((NOT a) OR ....) OR....
				sub_tree_sx = get_sub_tree_not(sx_sx);
			}
			if (is_not(sx_sx) != true) {   //((a AND b) OR ....) OR...
				sub_tree_sx = get_sub_tree(sx_sx);
			}

			if (str[ind_sx - 1] == ')') {  // ((a AND b) OR (...)) OR......
				
				int ind_par_aperta = find_opened_index(str, ind_sx_sx + 1, ind_sx - 1);
				vector<string> sx_dx = divide_string_by_space(str, ind_par_aperta + 1, ind_sx - 2);


				if (is_not(sx_sx) == true) {//((....) OR (NOT c)) OR ...
					sub_tree_dx = get_sub_tree_not(sx_dx);
					string root = str.substr(ind_sx_sx + 2, ind_par_aperta - 3 - ind_sx_sx);
					struct nodo * _root = add_nodo(root);
					sub_tree_left = get_union_sub_tree(sub_tree_sx, _root, sub_tree_dx);
				}
				if (is_not(sx_dx) != true) { //(....) OR (c AND d)) OR ....
					sub_tree_dx = get_sub_tree(sx_dx);
					string root = str.substr(ind_sx_sx + 2, ind_par_aperta - 3 - ind_sx_sx);
					struct nodo * _root = add_nodo(root);
					sub_tree_left = get_union_sub_tree(sub_tree_sx, _root, sub_tree_dx);
				}



			}
			if (str[ind_sx - 1] != ')') {//((a AND b) OR c) OR.......
				vector<string> root_leaf_dx = divide_string_by_space(str, ind_sx_sx + 2, ind_sx - 1);
				struct nodo * sub_tree_root_leaf_dx = get_sub_tree_dx_leaf(root_leaf_dx);
				sub_tree_left = get_union_root_sub_tree_sx(sub_tree_sx, sub_tree_root_leaf_dx);

			}


		}

		if (str[1] != '(') {  //(a OR ......) OR.....


			if (str[ind_sx - 1] == ')') { //(a OR (....)) OR...

				int ind = find_opened_index(str, 1, ind_sx - 1);
				vector<string>  vect1 = divide_string_by_space(str, 1, ind - 2);
				struct nodo *_root = get_sub_tree_sx_leaf(vect1);
				//struct nodo *sub_tree_dx;
				vector<string> vect = divide_string_by_space(str, ind + 1, ind_sx - 2);

				if (is_not(vect) == true) {//(a OR (NOT b)) OR....
					sub_tree_dx = get_sub_tree_not(vect);
				}
				if (is_not(vect) != true) { //(a OR (b AND c)) OR .....

					sub_tree_dx = get_sub_tree(vect);

				}
				sub_tree_left = get_union_root_sub_tree_dx(sub_tree_dx, _root);


			}
			if (str[ind_sx - 1] != ')') { //(a OR b) OR ....
				vector<string>vect = divide_string_by_space(str, 1, ind_sx - 1);
				if (is_not(vect) == true) {
					sub_tree_left = get_sub_tree_not(vect);
				}
				if (is_not(vect) != true) { sub_tree_left = get_sub_tree(vect); }
			}




		}
	}//fine if

	if (str[0] != '(') { //....radice_principale
		size_t pos_del = 0;
		string del = " ";
		pos_del = str.find(del);
		string nodo = str.substr(0, pos_del);
		sub_tree_left = add_nodo(nodo); //foglia a sinistra

	}
	return sub_tree_left;
}

struct nodo * Sotto_albero::get_sub_tree_right(string & str_sub_tree)
{
	string str = str_sub_tree;
	if (str[str.length() - 1] == ')') { //........ OR (....)

		int ind_dx = find_opened_index(str, 0, str.length() - 1);
		struct nodo *sub_tree_sx = nullptr;
		struct nodo *sub_tree_dx = nullptr;

		if (str[ind_dx + 1] == '(') { // ..... OR ((....) OR .....)
			int dx_sx = find_closed_index(str, ind_dx + 1, str.length() - 1);
			vector<string> vett = divide_string_by_space(str, ind_dx + 2, dx_sx - 1);
			/*struct nodo * sub_tree_sx;
			struct nodo *sub_tree_dx;*/
			if (is_not(vett) == true) {//.....OR ((NOT a) OR....)
				sub_tree_sx = get_sub_tree_not(vett);
			}
			if (is_not(vett) != true) {//.....OR((a AND b) OR....)
				sub_tree_sx = get_sub_tree(vett);
			}




			if (str[str.length() - 2] == ')') {//.....OR ((....) OR (c AND d))
				//struct nodo * sub_tree_sx;
				//struct nodo *sub_tree_dx;
				int ind_aperta2 = find_opened_index(str, dx_sx + 1, str.length() - 2);
				vector<string> vett1 = divide_string_by_space(str, ind_aperta2 + 1, str.length() - 3);
				string root_ = str.substr(dx_sx + 2, ind_aperta2 - 3 - dx_sx);
				struct nodo * _root = add_nodo(root_);

				if (is_not(vett1) == true) {
					sub_tree_dx = get_sub_tree_not(vett1);
				}
				if (is_not(vett1) != true) {
					sub_tree_dx = get_sub_tree(vett1);
				}

				sub_tree_right = get_union_sub_tree(sub_tree_sx, _root, sub_tree_dx);

			}

			if (str[str.length() - 2] != ')') {//......OR ((a AND b) OR c)
				vector<string> vett1 = divide_string_by_space(str, dx_sx + 2, str.length() - 2);
				sub_tree_dx = get_sub_tree_dx_leaf(vett1);
				sub_tree_right = get_union_root_sub_tree_sx(sub_tree_sx, sub_tree_dx);


			}



		}

		if (str[ind_dx + 1] != '(') { //......OR (a OR .....)

			if (str[str.length() - 2] == ')') {//.....OR (a OR (b AND c))
				
				int dx_dx = find_opened_index(str, ind_dx + 1, str.length() - 2);
				vector<string>vett1 = divide_string_by_space(str, ind_dx + 1, dx_dx - 2);
				sub_tree_sx = get_sub_tree_sx_leaf(vett1);

				vector<string>vett = divide_string_by_space(str, dx_dx + 1, str.length() - 3);

				if (is_not(vett) == true) {
					sub_tree_dx = get_sub_tree_not(vett);
				}
				if (is_not(vett) != true) {
					sub_tree_dx = get_sub_tree(vett);
				}



				sub_tree_right = get_union_root_sub_tree_dx(sub_tree_dx, sub_tree_sx);

			}
			if (str[str.length() - 2] != ')') { //.....OR (a OR b)
				vector<string>vett = divide_string_by_space(str, ind_dx + 1, str.length() - 2);
				if (is_not(vett) == true) {
					sub_tree_right = get_sub_tree_not(vett);
				}
				if (is_not(vett) != true) {
					sub_tree_right = get_sub_tree(vett);
				}


			}


		}


	}
	if (str[str.length() - 1] != ')') { //......OR c
		vector<string> invert_str = divide_string_by_space(str, 0, str.length() - 1);
		sub_tree_right = add_nodo(*(invert_str.end() - 1)); //foglia a destra

	}
	return sub_tree_right;
}

struct nodo * Sotto_albero::get_final_sub_tree(string & str_)
{
	
	
	string _main_root = find_main_root(str_);
	main_root = add_nodo(_main_root);
	if (_main_root == "NOT") {
		sub_tree_right = get_sub_tree_right(str_);
		main_root=get_union_root_sub_tree_sx(sub_tree_right, main_root);
	}
	else {
		sub_tree_left = get_sub_tree_left(str_);
		sub_tree_right = get_sub_tree_right(str_);
		main_root = get_tree(sub_tree_left, main_root, sub_tree_right);
	}
	
	
	return main_root;
}

vector<string> Sotto_albero::divide_string_by_space(string & _str, int _pos1, int _pos2)
{
	string del = " ", token;
	size_t pos1 = _pos1;
	size_t pos2 = _pos2;
	string str = _str.substr(pos1, pos2 - pos1 + 1);
	pos1 = 0;
	vector<string> ss;

	while ((pos1 = str.find(del)) != string::npos) {

		token = str.substr(0, pos1);
		ss.push_back(token);
		str.erase(0, pos1 + del.length());
	}
	ss.push_back(str);
	return ss;
}

 struct nodo * Sotto_albero::add_nodo(string & _valore)
{
	 
	struct nodo * neww = new struct nodo ;
	neww->info = _valore;
	neww->right = nullptr;
	neww->left = nullptr;
	neww->parent = nullptr;
	neww->value = -1;
	return   neww;
}

int Sotto_albero::find_closed_index(string & _str, int _beg, int _end)
{
	int flag = 0;//numero parentesi aperte

	for (int i = _beg; i < _end; i++) {

		if (_str[i] == '(' && flag == 0) {//incontra la prima parentesi aperta
			flag++;

		}
		if (_str[i] == '(' && flag >= 1) {
			flag++;//flag1=1 è stato trovato lindice di chiusura parentesi piu interna
		}

		if (_str[i] == ')' && flag > 1) {

			flag--;
		}
		if (_str[i] == ')' && flag == 1) {

			return i;
		}



	}
}

int Sotto_albero::find_opened_index(string & str, int _beg, int _end)
{
	
	int flag = 0;

	for (int i = _end; i >= _beg; i--) {
		if (str[i] == ')' && flag == 0) {//incontra la prima parentesi aperta
			flag++;

		}
		if (str[i] == ')' && flag >= 1) {
			flag++;//flag1=1 è stato trovato l'indice di chiusura parentesi piu interna
		}

		if (str[i] == '(' && flag > 1) {

			flag--;
		}
		if (str[i] == '(' && flag == 1) {

			return i;

		}

	}
}

struct nodo * Sotto_albero::get_sub_tree(vector<string>& _vect)
{
	struct nodo * _left = add_nodo(*_vect.begin());
	struct nodo * _root = add_nodo(*(_vect.begin() + 1));
	struct nodo *_right = add_nodo(*(_vect.begin() + 2));
	_root->left = _left;
	_root->right = _right;
	_left->parent = _root;
	_right->parent = _root;
	return _root;
}

struct nodo * Sotto_albero::get_sub_tree_dx_leaf(vector<string>& _vect)
{
	struct nodo * _root = add_nodo(*(_vect.begin()));
	struct nodo *_right = add_nodo(*(_vect.begin() + 1));
	_root->right = _right;
	_right->parent = _root;
	return _root;
}

struct nodo * Sotto_albero::get_sub_tree_sx_leaf(vector<string>& _vect)
{
	struct nodo * _left = add_nodo(*(_vect.begin()));
	struct nodo *_root = add_nodo(*(_vect.begin() + 1));
	_root->left = _left;
	_left->parent = _root;
	return _root;
}

struct nodo * Sotto_albero::get_union_sub_tree(struct nodo * sub_tree_sx, struct nodo * _root, struct nodo * sub_tree_dx)
{
	_root->left = sub_tree_sx;
	_root->right = sub_tree_dx;
	sub_tree_dx->parent = _root;
	sub_tree_sx->parent = _root;
	return _root;
}

 struct nodo * Sotto_albero::get_union_root_sub_tree_sx(struct nodo * sub_tree_sx, struct nodo * _root)
{
	_root->left = sub_tree_sx;
	sub_tree_sx->parent = _root;
	return _root;
}

 struct nodo * Sotto_albero::get_union_root_sub_tree_dx(struct nodo * sub_tree_dx,struct nodo * _root)
{
	_root->right = sub_tree_dx;
	sub_tree_dx->parent = _root;
	return _root;
}

string Sotto_albero::find_main_root(string & _str)
{
	
	string _main_root;
	if (_str[0] == '(' && _str[_str.length() - 1] == ')') {//(...) OR (....) primo caso

		int _chiusa = find_closed_index(_str, 0, _str.length());
		int _aperta = find_opened_index(_str, 0, _str.length() - 1);
		vector<string> tmp = divide_string_by_space(_str, _chiusa + 2, _aperta - 2);
		_main_root = *tmp.begin();

	}
	if (_str[0] == '(' && _str[_str.length() - 1] != ')') {//(...) OR c secondo caso
		int _chiusa = find_closed_index(_str, 0, _str.length());
		vector<string> tmp = divide_string_by_space(_str, _chiusa + 2, _str.length() - 1);
		_main_root = *tmp.begin();

	}
	if (_str[0] != '(' && _str[_str.length() - 1] == ')') { // a OR (...) terzo caso
		int _aperta = find_opened_index(_str, 0, _str.length() - 1);
		vector<string> tmp = divide_string_by_space(_str, 0, _aperta - 2);
		_main_root = *(tmp.begin() + 1);

	}
	if (_str[0] != '(' && _str[_str.length() - 1] != ')') {// a OR c quarto caso
		vector<string> tmp =divide_string_by_space(_str, 0, _str.length() - 1);
		if (tmp.size() > 2) { _main_root = *(tmp.begin() + 1); }
		if (tmp.size() == 2) { _main_root = *tmp.begin();}
	}
	
	return _main_root;
}

 struct nodo * Sotto_albero::get_tree(struct nodo * sx_,struct  nodo * root_, struct nodo * dx_)
{
	root_->left = sx_;
	sx_->parent = root_;
	root_->right = dx_;
	dx_->parent = root_;
	return root_;
}

bool Sotto_albero::is_not(vector<string>& vect)
{
	if (*vect.begin() == "NOT") {
		return true;
	}
	else return false;
}

 struct nodo * Sotto_albero::get_sub_tree_not(vector<string>& _not)
{
	struct nodo * not_ = add_nodo(*_not.begin());
	struct nodo * left_not = add_nodo(*(_not.begin() + 1));
	not_->left = left_not;
	left_not->parent = not_;
	return not_;
}










