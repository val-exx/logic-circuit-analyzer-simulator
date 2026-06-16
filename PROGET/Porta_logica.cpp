#include "Porta_logica.h"



Porta_logica::Porta_logica()
{
}


Porta_logica::~Porta_logica()
{
}


NOT::NOT()
{
}

NOT::~NOT()
{
}



int NOT::get_result()
{
	if (input == 1) { result = 0; }
	if (input == 0) { result = 1; }
	values.push_back(result); 
	return result;
}

void NOT::set_one_input(int & Input)
{
	input = Input;
}



vector<int> NOT::get_all_values()
{
	
	return values;
}


AND::AND()
{
}

AND::~AND()
{
}




void AND::set_two_input(int & Input1, int & Input2)
{
	input1 = Input1;
	input2 = Input2;
}

int AND::get_result()
{
	result = input1 && input2;

	values.push_back(result); 

	return result;
}

vector<int> AND::get_all_values()
{

	return values;
}


NAND::NAND()
{
}

NAND::~NAND()
{
}

void NAND::set_two_input(int & Input1, int & Input2)
{
	input1 = Input1;
	input2 = Input2;
}



int NAND::get_result()
{
	if (input1 == 0 && input2 == 0) { result = 1; }
	if (input1 == 0 && input2 == 1) { result = 1; }
	if (input1 == 1 && input2 == 0) { result = 1; }
	if (input1 == 1 && input2 == 1) { result = 0; }
	values.push_back(result);
	return result;
}

vector<int> NAND::get_all_values()
{
	return values;
}


OR::OR()
{
}

OR::~OR()
{
}

void OR::set_two_input(int & Input1, int & Input2)
{
	input1 = Input1;
	input2 = Input2;
}

int OR::get_result()
{

	result = input1 || input2; 
	return result;
}

vector<int> OR::get_all_values()
{
	return values;
}


XOR::XOR()
{
}

XOR::~XOR()
{
}

void XOR::set_two_input(int & Input1, int & Input2)
{
	input1 = Input1;
	input2 = Input2;
}


int XOR::get_result()
{
	if (input1 == 0 && input2 == 0) { result = 0; }
	if (input1 == 0 && input2 == 1) { result = 1; }
	if (input1 == 1 && input2 == 0) { result = 1; }
	if (input1 == 1 && input2 == 1) { result = 0; }
	values.push_back(result);
	return result;
}

vector<int> XOR::get_all_values()
{
	return values;
}


NOR::NOR()
{
}

NOR::~NOR()
{
}

void NOR::set_two_input(int & Input1, int & Input2)
{
	input1 = Input1;
	input2 = Input2;
}



int NOR::get_result()
{
	if (input1 == 0 && input2 == 0) { result = 1; }
	if (input1 == 0 && input2 == 1) { result = 0; }
	if (input1 == 1 && input2 == 0) { result = 0; }
	if (input1 == 1 && input2 == 1) { result = 0; }
	values.push_back(result);
	return result;
}

vector<int> NOR::get_all_values()
{
	return values;
}


XNOR::XNOR()
{
}

XNOR::~XNOR()
{
}

void XNOR::set_two_input(int & Input1, int & Input2)
{
	input1 = Input1;
	input2 = Input2;
}

int XNOR::get_result()
{
	if (input1 == 0 && input2 == 0) { result = 1; }
	if (input1 == 0 && input2 == 1) { result = 0; }
	if (input1 == 1 && input2 == 0) { result = 0; }
	if (input1 == 1 && input2 == 1) { result = 1; }
	values.push_back(result);
	return result;
}

vector<int> XNOR::get_all_values()
{
	return values;
}


FF::FF()
{
}

FF::~FF()
{
}

void FF::set_one_input(int & Input)
{
	input = Input;
}

int FF::get_result()
{
	result = input;
	values.push_back(result);
	return result;
}

vector<int> FF::get_all_values()
{
	return values;
}

