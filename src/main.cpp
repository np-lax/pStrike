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
#include "../include/neo_calcs.hpp"
#include <stdlib.h>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

const char DECORATION[] = "==============================================="
	"============\n";
const char ROOT_TITLE[] = "\033[1;37;44mplanetStrike - Near Earth "
	"Object Collision Calculator\033[0m     |\n";

void print_header() {
	//clear the screen, display startup information
	cout << "\033[2J\033[1;1H";
	cout << DECORATION << ROOT_TITLE << DECORATION << flush;
}


/*
	main - main prgm loop
	
	@param argc		argument count
	@param argv		arguments passed via command line
	@return			exit status

*/
int main(int argc, char* argv[]){
    string input = "";
    
    print_header();

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
    	
	cout << "\nPress 'Enter' to continue......" << endl;
    getline(cin, input);

    //main program loop

    int menu_selection;

    while (true) {
        print_header();
        
        //print column headers
        cout << setw(25) << left << "OBJ NAME" << setw(18) << left << 
        "SIZE (meters)" << setw(15) << left << "SPEED (KM/H)" << endl;
        cout << "-----------------------------------------------------" << endl;
        
        //display neo objects
        for (int x = 0; x < neo_arr.size(); x++) {
            cout << x << ") " << setw(25) << left << neo_arr[x].get_name() << 
            setw(18) << left << round(neo_arr[x].get_size()) << setw(15) << 
            left << round(neo_arr[x].get_speed()) << endl;
        }

        //print exit condition
        cout << (neo_arr.size() + 1) << ") Quit" << endl;

        //capture user input at main menu     
        cout << "user selection: ";
        cin >>  menu_selection;
   
        if (!cin.fail()) {      
            if (menu_selection >= 0 && menu_selection < neo_arr.size()) {
                print_header();
                obj_selected(neo_arr[menu_selection]);
            } else if (menu_selection == neo_arr.size() + 1){
                break;    
            } else {
                cout << "* please select a valid menu entry *" << endl;    
            }
        } else {
            cout << "* please select a valid menu entry *" << endl;    
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
     

        
        this_thread::sleep_for (std::chrono::seconds(2));


                
            //    cout << "1) Earth impact information | 2) Lunar impact information | 3) Return to object list" << endl;
            
        
        //allow user to select object

        //allow user to view data about object
        //allow user to simulate planetary impact 
    }
    
//cleanup & exit
return 0;
}
