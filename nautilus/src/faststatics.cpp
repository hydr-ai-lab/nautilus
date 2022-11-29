#include "lib/SuperficieN.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std; 
vector<string> split(string str, char delimiter) { 
  vector<string> internal; 
  stringstream ss(str); // Turn the string into a stream. 
  string tok; 
 
  while(getline(ss, tok, delimiter)) { 
    internal.push_back(tok); 
  } 
 
  return internal; 
}

int main(int argc, char** argv){
	std::string inFile = "";
	std::string outFile = "";
	std::string cutfile = "";
	std::ofstream myfile;
	
	if(argc<3){
		std::cout<<"Error: Wrong number of arguments. It is manditory to specify Input file (STL) and Draft(s)\n"
		"Optionally you can also specify an output file for the hydrostatics and submeged volume."
		<<std::endl;												// write error to the terminal
	}
	else{

		inFile = argv[1];											// get the input file
		std::cout<<"Read file: "<<inFile<<std::endl;

		vector<string> T = split(argv[2], ','); 					// vector of drafts

		if (argc>3){
			outFile = argv[3];										// get the output file
			myfile.open(outFile, std::ios::app);
			std::cout<<"Write file: "<<outFile<<std::endl;	
		}
			
		Superficie a;												// initialize the Superficie object
		a.readSTL(inFile);											// read STL

		for(string t : T){											// loop over trims 
			Vettore<double> risBody, risSect;						// initialize the output for Hydrostatic method
			
			risSect = a.SectionFast(Punto(0,0,stod(t)),Punto(0,0,1));// call the Section method and write to Vettore object
			risBody = a.HydrostaticFast(Punto(0,0,stod(t)),Punto(0,0,1));// call the Hydrostatic method and write to Vettore object
						
			if (argc>3){
				myfile<<t;											// write the trim to the file
			}
			else{
				std::cout<<t;										// write the trim to the terminal
			}
			
			for(int i=0;i<risBody.size();++i){
				if(argc>3){
					myfile<<", "<<risBody[i];						// write the body hydrostatics to the file
				}
				else{
					std::cout<<", "<<risBody[i];					// write the body hydrostatics to the terminal
				}
			}
			for(int i=0;i<risSect.size();++i){
				if (argc>3){
					myfile<<", "<<risSect[i];						// write the section hydrostatics to the file	
				}
				else{
					std::cout<<", "<<risSect[i];					// write the section hydrostatics to the terminal
				}
			}
			if (argc>3){
				myfile<<"\n";										// write newline to the file
			}
			else{
				std::cout<<std::endl;
			}
		}
		if (argc>3){
			myfile.close();											// close file
		}
	}
}
