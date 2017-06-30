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
    vector <string> tokens;

    //read in NEO data
    istringstream iss(initial_data);
    while(getline(route_f, proc_line)){
        istringstream iss(proc_line);
        //tokenize file - columns are delimited by tabs
        while(getline(iss, token,'\t')){
            /* use RE to check the token for hex-formatted IP addresses,
            if match, add to array */
            if(regex_match(token, hex_ip)){
                proc_tokens.push_back(token);
            }
        }
        //when line ingested, check for default GW in token array
        if((proc_tokens.size() >= 1) && (proc_tokens.at(0) == "00000000")){
            //if line contains default GW, convert IP to octet notation
            string dec_ip = conv_hex_ip(proc_tokens.at(1).c_str());
            if(dec_ip != ""){
                route_f.close();
                return dec_ip;
            }
        }
        //clear out token array for next line
        proc_tokens.clear();

    }
    //clean up & return
    route_f.close();
    return "-1";



	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	

	cout << "Press 'Enter' to continue......";
	getline(cin, input);
	
	//cleanup & exit
	return 0;
}
