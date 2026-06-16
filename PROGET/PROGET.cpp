#include "Controlli.h"
#include "Circuito.h"
#include"Libreria.h"
#include"Analisi.h"
#include "Simulazione.h"
#include <iostream>
#include<fstream>
#include <string>
#include<vector>

using namespace std;

void print_output_simulation(vector<vector<string>> & output,double & power_tot);



void stampa_albero(struct nodo * root);
int main(int argc, char *argv[])
{
	//controlla se il numero di argomenti passati è corretto
	if (argc != 2) {
		cerr << "Errore numero argomenti" << endl;
		return 0;
	}

	ifstream in; //lettura file messo da linea di comando
	ifstream in_lib;//lettura file modalità libreria contenente i percorsi file dei circuiti
	ifstream in_power;//lettura file consumi di potenza degli operatori
	ifstream in_input;//lettura file valori di input
	ofstream output_file; //scrittura file degli output/consumo di potenza totale
	
	string file_lib_name; //nome file libreria inserito da utente
	string file_input_name;//nome file contenente gli input per la simulazione
	string file_power_name;//nome file contenenete i consumi di potenza di ogni operatore
	string file_output_name;//nome file scrittura output

	vector<vector<int>> input_for_simulation;

	vector<vector<string>> output_simulation;//output della simulazione
	double power_analysis;// risultato consumo totale di potenza

	vector<vector<string>>::iterator it_output_external;//iteratore degli output a seguito della simulazione
	vector<string>::iterator it_output_internal, end_it_output_internal;

	Controlli Controls;//creazione oggetto controlli 
	
	

	string circuit_name;//nome circuito
	vector<struct nodo*> circuit_pointers;//puntatori alle radici del circuito
	vector<string> circuit_description;//descrizione circuit
	struct circuit* Circuit;//struttura che contiene le caratteristiche del circuito
	vector<struct logical_cones*> vector_logical_cones;

	int minimum_path;//path minimo
	int maximum_path;//path massimo
	

	/*vector<vector<string>>::iterator it_output_external;//iteratore degli output a seguito della simulazione
	vector<string>::iterator it_output_internal,end_it_output_internal;*/

	//Controlli Controls;//creazione oggetto controlli 
	
	in.open(argv[1]);
	
	
	//controlla se il file di definizione del circuito si è aperto correttamente
	if (!in.is_open()) {
		
		cerr << "Impossibile aprire file circuito " << endl;
		return 1;
	}

	int result_control_circuit_file; result_control_circuit_file = Controls.file_circuit_is_correct(in);

	//controlla se il file è vuoto
	if (result_control_circuit_file==0) {
		cerr << "Errore file vuoto";
		return 0;
	}

	//controllo se file di definizione del circuito è corretto
	if(result_control_circuit_file ==-1){
		cerr << "Errore gli output del circuito non corrispondono alla definizione";
		return 3;

	}

	//controllo se gli input siano definiti correttamente
	if (result_control_circuit_file == -2) {
		cerr << "Errore gli input del circuito non corrispondono alla definizione";
		return 2;

	}

	//in caso il circuito fosse combinatorio controlla se c'è feedback nella descrizione
	if (result_control_circuit_file == -3) {
		cerr << "Errore il circuito combinatorio descritto contiene feedback";
		return 4;

	}

	
	else {//se il file è aperto,non è vuoto ed è stato aperto correttamente costruisci l'albero del circuito
		circuit_description = Controls.return_vector_string_file();
		circuit_name = Controls.return_circuit_name(); 
		Circuito circuit_object(circuit_description);
		circuit_pointers = circuit_object.get_circuit();
		Circuit = new struct circuit;
		Circuit->name = circuit_name;
		Circuit->description = circuit_description;
		Circuit->root_pointers = circuit_pointers;
		

		int scelta;
		int scelta_simulazione_schermo_file;


		cout << "1. Simulazione circuito" << endl << "2. Analisi circuito" << endl << "3. Modalita' Libreria" << endl;
		
		cin >> scelta;

		switch (scelta)
		{
			//simulazione circuito
		case 1: {

			cout << "Inserire nome file input : " << endl;
			cin >> file_input_name;
			file_input_name += ".txt";

			in_input.open(file_input_name);

			int result_file_input = Controls.file_input_is_correct(in_input);

			if (result_file_input == 1) {//controllo se file input e' vuoto
				cerr << "Errore il file di input vuoto" << endl;
				return 0;
			}

			if (result_file_input == 2) {//controllo se file input contiene 0 e 1
				cerr << "Errore il file di input non e' stato scritto correttamente" << endl;
				return 5;

			}

			if (result_file_input == 3) {//se è stato scritto correttamente
				cout << "Inserire nome file consumo degli operatori : " << endl;
				cin >> file_power_name;
				file_power_name += ".txt";
				in_power.open(file_power_name);

				if (in_power.is_open() != true) {//controllo se file input si è aperto correttamente
					cerr << "Errore apertura file consumo operatori" << endl;
					return 1;
				}



				input_for_simulation = Controls.return_numbers_input_for_simulation();
				in_input.close();

				if (input_for_simulation.empty() == true) {
					cerr << "Errore input non salvati " << endl;
					return 6;
				}


				Simulazione s(circuit_description, circuit_pointers, input_for_simulation, in_power);

				output_simulation = s.circuit_simulation();
				power_analysis = s.get_total_consumption();

				if (*(*output_simulation.begin()).begin() == "-1") {
					cerr << "Errore non ci sono abbastanza input per foglia" << endl;
					return 7;
				}

				if (power_analysis == -1) {
					cerr << "Errore non tutti gli operatori del circuito sono presenti nel file" << endl;
					return 8;
				}
				int scelta_simulazione_schermo_file;
				cout << "1. Stampa output a schermo" << endl << "2. Stampa output su file" << endl;
				cin >> scelta_simulazione_schermo_file;

				if (scelta_simulazione_schermo_file == 1) {//stampa su schermo

					print_output_simulation(output_simulation, power_analysis);

				}

				if (scelta_simulazione_schermo_file == 2) {//stampa su file
					cout << "Inserire nome file degli output :";
					cin >> file_output_name;
					file_output_name += ".txt";
					output_file.open(file_output_name);

					if (output_file.is_open() != true) {
						cout << "Errore apertura file output" << endl;
						return 1;
					}
					else {
						Controls.write_simulation_file(output_file, output_simulation, power_analysis);
					}
				}



			}
			break;
        }

				//analisi circuito
		case 2: {
			
			Analisi analysis(circuit_pointers,circuit_description);
			//vector<struct logical_cones*> 

			//path minimo
			minimum_path= analysis.return_min_depth();
			cout<<"Path minimo del circuito : "<<minimum_path<<endl;

			//path massimo
			maximum_path = analysis.return_max_depth();
			cout<<"Path massimo del circuito : "<<maximum_path<<endl;

			//coni logici
			vector_logical_cones=analysis.return_logical_cones();
			vector<struct logical_cones*>::iterator it_cones=vector_logical_cones.begin();
			for(it_cones;it_cones!=vector_logical_cones.end();++it_cones){

			cout<<"Gli input necessari per "<<(*it_cones)->output_name<<" sono : ";

			vector<string>::iterator it_input=((*it_cones)->inputs_name).begin();
			vector<string>::iterator end_it_input=((*it_cones)->inputs_name).end();

			for(it_input;it_input!=end_it_input;++it_input){
			cout<<*it_input<<" ";
			}
			cout<<endl;
			}

			Circuito is_sequential;
			if (is_sequential.type_of_circuit(circuit_description)=="Sequential") {
				//loop massimo e minimo
				vector<string> loops = analysis.compute_loop(); 
				if (loops.empty() == true) { cerr << "In questo circuito non ci sono loop" << endl; }

				else {
					if (analysis.min_loop_str() != analysis.max_loop_str()) {
						cout << "il loop massimo e' " << analysis.max_loop_str() << " ed e' lungo " << analysis.max_loop_value() << endl;
						cout << "il loop minimo e' " << analysis.min_loop_str() << " ed e' lungo " << analysis.min_loop_value() << endl;
					}
					else {
						cout << "E' presente un solo loop o sono tutti della stessa lunghezza "
							<< analysis.max_loop_str() << " ed e' lungo " << analysis.max_loop_value() << endl;
					}
				}
			}

			break;
		}

				//modalita' libreria
		case 3: {
			cout << "Inserire nome percorso file : " << endl;
			cin >> file_lib_name;
			file_lib_name += ".txt";
			in_lib.open(file_lib_name);

			if (!in_lib.is_open()) {
				cerr << "Errore apertura file contenente i percorsi" << endl;
				return 1;
			}

			file_lib_name = Controls.open_return_library_file_name(in_lib);
			in_lib.close();
			if (file_lib_name == "vuoto") {
				cerr << "Errore file contenente i percorsi e' vuoto" << endl;
				return 0;
			}

			in_lib.open(file_lib_name);

			if (!in_lib.is_open()) {
				cerr << "Errore apertura file " << endl;
				return 1;
			}

			Controlli control;
			int control_composite = control.file_circuit_is_correct(in_lib);
			//controlla se il file è vuoto
			if (control_composite == 0) {
				cerr << "Errore file vuoto";
				return 0;
			}

			//controllo se file di definizione del circuito è corretto
			if (control_composite == -1) {
				cerr << "Errore gli output del circuito non corrispondono alla definizione";
				return 3;

			}

			//controllo se gli input siano definiti correttamente
			if (control_composite == -2) {
				cerr << "Errore gli input del circuito non corrispondono alla definizione";
				return 2;

			}
			else {
			vector<string> vector_composite_description = control.return_vector_string_file();
			in_lib.close();
			Libreria library(vector_composite_description, Circuit);
			Circuit = library.get_library_circuit();

			cout << "1. Simulazione circuito" << endl << "2. Analisi circuito" << endl;
			cin >> scelta;
			//simulazione circuito composito
			if (scelta == 1) {


				cout << "Inserire nome file input : " << endl;
				cin >> file_input_name;
				file_input_name += ".txt";

				in_input.open(file_input_name);

				int result_file_input = Controls.file_input_is_correct(in_input);

				if (result_file_input == 1) {//controllo se file input e' vuoto
					cerr << "Errore il file di input vuoto" << endl;
					return 0;
				}

				if (result_file_input == 2) {//controllo se file input contiene 0 e 1
					cerr << "Errore il file di input non e' stato scritto correttamente" << endl;
					return 5;

				}

				if (result_file_input == 3) {//se è stato scritto correttamente
					cout << "Inserire nome file consumo degli operatori : " << endl;
					cin >> file_power_name;
					file_power_name += ".txt";
					in_power.open(file_power_name);

					if (in_power.is_open() != true) {//controllo se file input si è aperto correttamente
						cerr << "Errore apertura file consumo operatori" << endl;
						return 1;
					}



					input_for_simulation = Controls.return_numbers_input_for_simulation();
					in_input.close();

					if (input_for_simulation.empty() == true) {
						cerr << "Errore input non salvati " << endl;
						return 6;
					}


					Simulazione s(Circuit->description, Circuit->root_pointers, input_for_simulation, in_power);

					output_simulation = s.circuit_simulation();
					power_analysis = s.get_total_consumption();

					if (*(*output_simulation.begin()).begin() == "-1") {
						cerr << "Errore non ci sono abbastanza input per foglia" << endl;
						return 7;
					}

					if (power_analysis == -1) {
						cerr << "Errore non tutti gli operatori del circuito sono presenti nel file" << endl;
						return 8;
					}
					int scelta_simulazione_schermo_file;
					cout << "1. Stampa output a schermo" << endl << "2. Stampa output su file" << endl;
					cin >> scelta_simulazione_schermo_file;

					if (scelta_simulazione_schermo_file == 1) {//stampa su schermo

						print_output_simulation(output_simulation, power_analysis);

					}

					if (scelta_simulazione_schermo_file == 2) {//stampa su file
						cout << "Inserire nome file degli output :";
						cin >> file_output_name;
						file_output_name += ".txt";
						output_file.open(file_output_name);

						if (output_file.is_open() != true) {
							cout << "Errore apertura file output" << endl;
							return 1;
						}
						else {
							Controls.write_simulation_file(output_file, output_simulation, power_analysis);
						}
					}



				}
				break;

			}
			//analisi circuito composito
			if (scelta == 2) {

				Analisi analysis(Circuit->root_pointers, Circuit->description);


				//path minimo
				minimum_path = analysis.return_min_depth();
				cout << "Path minimo del circuito : " << minimum_path << endl;

				//path massimo
				maximum_path = analysis.return_max_depth();
				cout << "Path massimo del circuito : " << maximum_path << endl;

				//coni logici
				vector_logical_cones = analysis.return_logical_cones();
				vector<struct logical_cones*>::iterator it_cones = vector_logical_cones.begin();
				for (it_cones; it_cones != vector_logical_cones.end(); ++it_cones) {

					cout << "Gli input necessari per " << (*it_cones)->output_name << " sono : ";

					vector<string>::iterator it_input = ((*it_cones)->inputs_name).begin();
					vector<string>::iterator end_it_input = ((*it_cones)->inputs_name).end();

					for (it_input; it_input != end_it_input; ++it_input) {
						cout << *it_input << " ";
					}
					cout << endl;
				}

				Circuito is_sequential; 
				if (is_sequential.type_of_circuit(Circuit->description) == "Sequential") {
					//loop massimo e minimo
					vector<string> loops = analysis.compute_loop();
					if (loops.empty() == true) { cerr << "In questo circuito non ci sono loop" << endl; }

					else {
						if (analysis.min_loop_str() != analysis.max_loop_str()) {
							cout << "il loop massimo e' " << analysis.max_loop_str() << " ed e' lungo " << analysis.max_loop_value() << endl;
							cout << "il loop minimo e' " << analysis.min_loop_str() << " ed e' lungo " << analysis.min_loop_value() << endl;
						}
						else {
							cout << "E' presente un solo loop o sono tutti della stessa lunghezza "
								<< analysis.max_loop_str() << " ed e' lungo " << analysis.max_loop_value() << endl;
						}
					}
				}

			}

			else { cerr << "Errore inserimento scelta" << endl; return -1; }
		}
        }//fine caso 3


		
		}
		
	}
}

void print_output_simulation(vector<vector<string>> & output, double & power_tot)
{

	vector<vector<string>>::iterator it_output_external;
	vector<string>::iterator it_output_internal, end_it_output_internal;

			cout << "Risultato della simulazione : " << endl << endl;

			
			for (it_output_external = output.begin(); it_output_external != output.end(); ++it_output_external) {
				it_output_internal = (*it_output_external).begin();
				end_it_output_internal = (*it_output_external).end();
				
				for (it_output_internal; it_output_internal != end_it_output_internal; ++it_output_internal) {
					cout<< *it_output_internal << " ";

				} cout << endl;

			}


			cout << endl << endl << "Consumo totale di potenza del circuito : ";

			cout << power_tot;



		}

	


void stampa_albero(nodo * root)
{
	if (root != nullptr) {
		cout << root->info << endl; 
		stampa_albero(root->left); 
		stampa_albero(root->right);
}
}
