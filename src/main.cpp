/*
	pStrike - A CLI tool for calculating theoretical asteroid strikes on
	planets in the solar system using data from NASA's Near Earth Object Web 
	Service API
	
	main.cpp

	@author Rob Cilla
	@version 0.0 24 Jun 17
*/

#include "../include/netUtils.hpp" 
#include <stdlib.h>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
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
	const char ROOT_TITLE[] = "\033[1;37;44mplanetStrike - Live Near Earth "
	"Object Collision Calculator\033[0m\n";
	string input = "";	
	string databaseDL = "Downloading Near Earth Object data for last 7 days....";

	
	//clear the screen, display startup information
	cout << "\033[2J\033[1;1H";
	cout << DECORATION << ROOT_TITLE << DECORATION;
	
	//check LAN/inet/API connections		
	netCheck();

	//get current NEO data
	cout << databaseDL << "\n";
	//someArray = getNEOData();

	
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	

	cout << "Press 'Enter' to continue......";
	getline(cin, input);
	
	//cleanup & exit
	return 0;
}
