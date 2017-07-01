/*
	pStrike - A CLI tool for calculating theoretical asteroid strikes on
	planets in the solar system using data from NASA's Near Earth Object Web 
	Service API
	
	main.cpp

	@author Rob Cilla
	@version 0.0 24 Jun 17
*/

#include "../include/net_utils.hpp" 
#include "../include/neo_web_functs.hpp"
#include "../include/neo_class.hpp"
#include <stdlib.h>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>


using namespace std;


/*
	main - main prgm loop
	
	@param argc		argument count
	@param argv		arguments passed via command line
	@return			exit status

*/
int main(int argc, char* argv[]){
	const char DECORATION[] = "==============================================="
	"============\n";
	const char ROOT_TITLE[] = "\033[1;37;44mplanetStrike - Near Earth "
	"Object Collision Calculator\033[0m     |\n";

	string input = "";	
	
	//clear the screen, display startup information
	cout << "\033[2J\033[1;1H";
	cout << DECORATION << ROOT_TITLE << DECORATION;

    //begin self-check procedures
    string chk_setup = "PERFORMING START-UP TASKS|\n";
    string line_brk =  "--------------------------\n";
    cout << line_brk << chk_setup << line_brk;
	
	//check LAN/inet
	int comm_res = comms_check();

	//test API key & get current NEO data
	string initial_data = initial_neo_data_dl("DEMO_KEY");
    
    //near_earth_object neo1(6, 3214123, "obj1", 400, 200, true, "2017-07-30", 20000, 4000);

    //cout << neo1.get_name() << endl;

    //vector array holds contents of NEO data
    vector<string> returned_line;
    string temp_line;  

    string delimiter = ": ";
    string eol = ",";

    int num_neo_elements = -1;
    vector<float> neo_ptr;

    //read in NEO data
    stringstream ss(initial_data);
    
    if(!initial_data.empty()){
        while(getline(ss, temp_line, '\n')){
            //check for header containing element count
            if(temp_line.find("element_count") != string::npos){
                //find number of elements in NEO data
                num_neo_elements = atoi(temp_line.substr(temp_line.find(delimiter) + 2, 1).c_str());            
            //if line contains ref_id, it is the start of a new NEO obj
            }else if(temp_line.find("\"neo_reference_id\" : \"" != string::npos){
                //create new NEO object
                    
            }
        }
    }

    cout << "num elements: " << num_neo_elements << "\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	

	cout << "Press 'Enter' to continue......";
	getline(cin, input);
	
	//cleanup & exit
	return 0;
}
