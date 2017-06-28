#include "netUtils.hpp" 
#include <stdlib.h>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

/**
	EarthStrike - A TUI tool for calculating theoretical asteroid strikes on
	planets in the solar system
	
	main.cpp

	@author Rob Cilla
	@version 0.0 24 Jun 17
*/


/**
	Main program
	
	@param argc		argument count
	@param argv		arguments passed via command line
	@return			int    cout << res << endl;

*/
int main(int argc, char* argv[]){
	//set up constants
	const char DECORATION[] = "==============================================="
	"============\n";
	const char ROOT_TITLE[] = "\033[1;37;44mplanetStrike - Live Near Earth "
	"Object Collision Calculator\033[0m\n";
	string input = "";	
	
	//clear the screen, display startup information
	cout << "\033[2J\033[1;1H";
	cout << DECORATION << ROOT_TITLE << DECORATION;
	
	//check LAN/inet/API connections		
	netCheck();

	
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	

	cout << "Press 'Enter' to continue......";
	getline(cin, input);
	
	//cleanup & exit
	return 0;
}
