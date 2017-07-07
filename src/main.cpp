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
#include <math.h>

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
  
    //build NEO objects with today's NeoWs data
    vector<Near_earth_object> neo_arr = build_neo_objs(initial_data);
    	
	cout << "\nPress 'Enter' to continue......";
    getline(cin, input);

    //clear screen
    cout << "\033[2J\033[1;1H";
	cout << DECORATION << ROOT_TITLE << DECORATION;
    cout << "Select a near earth object:" << endl;

    string header = "\tNAME\t\t\tSIZE\t\tSPEED\t\t\n";

    cout << header << endl;

    //display objects
    for (int x = 0; x < neo_arr.size(); x++) {
        cout << x << ") " << neo_arr[x].get_name() << "\t\t\t" << round(neo_arr[x].get_size()) << " meters\t\t" << round(neo_arr[x].get_speed()) << "KM/H\t\t" << endl;
    }

    cout << "User selection: ";
    getline(cin, input);

    //allow user to select object

    //allow user to view data about object

    //allow user to simulate planetary impact 

	//cleanup & exit
	return 0;
}
