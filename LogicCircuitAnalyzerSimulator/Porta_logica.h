#pragma once
#include<vector>
#include<iostream>


using namespace std;

class Porta_logica
{
public:
	Porta_logica();
	~Porta_logica();
	virtual int get_result() = 0;

	virtual vector<int> get_all_values() = 0;//valori assunti per ogni chiamata alla classe

};

class NOT :public Porta_logica {
public:
	NOT();
	~NOT();

	virtual int get_result();
	void set_one_input(int & Input);
	virtual vector<int> get_all_values();
private:
	vector<int> values;
	int result, input;


};

class AND :public Porta_logica {
public:
	AND();
	~AND();

	void set_two_input(int & Input1, int & Input2);
	virtual int get_result();
	vector<int> get_all_values();
protected:
	vector<int> values;
private:
	int result, input1, input2;
};

class NAND :public Porta_logica {
public:
	NAND();
	~NAND();
	void set_two_input(int & Input1, int & Input2);
	virtual int get_result();
	virtual  vector<int> get_all_values();
protected:
	vector<int> values;
private:
	int result, input1, input2;
};

class OR :public Porta_logica {
public:
	OR();
	~OR();
	void set_two_input(int & Input1, int & Input2);
	virtual int get_result();
	virtual vector<int> get_all_values();
protected:
	vector<int> values;
private:
	int  result, input1, input2;
};

class XOR :public Porta_logica {
public:
	XOR();
	~XOR();
	void set_two_input(int & Input1, int & Input2);
	virtual int get_result();
	virtual vector<int> get_all_values();
private:
	vector<int> values;
	int result, input1, input2;
};

class NOR :public Porta_logica {
public:
	NOR();
	~NOR();
	void set_two_input(int & Input1, int & Input2);
	virtual int get_result();
	virtual vector<int> get_all_values();
private:
	vector<int> values;
	int result, input1, input2;
};

class XNOR :public Porta_logica {
public:
	XNOR();
	~XNOR();
	void set_two_input(int & Input1, int & Input2);
	virtual int get_result();
	virtual vector<int> get_all_values();
private:
	vector<int> values;
	int  result, input1, input2;

};

class FF : public Porta_logica {
public:
	FF();
	~FF();
	void set_one_input(int & Input);
	virtual int get_result();
	virtual vector<int> get_all_values();
private:
	vector<int> values;
	int result, input;

};



