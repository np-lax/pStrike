#include <stdlib.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <regex>
#include <algorithm>
#include <iterator>

using namespace std;

/**
	EarthStrike - A TUI tool for calculating theoretical asteroid strikes on
	planets in the solar system
	
	main.cpp

	@author Rob Cilla
	@version 0.0 24 Jun 17
*/


static char* hex2DecIP(const char *in)
{
	char *out = (char*)malloc(sizeof(char) * 16);
    char *revOut = (char*)malloc(sizeof(char) * 16);

	unsigned int p, q, r, s;

    if (sscanf(in, "%2x%2x%2x%2x", &p, &q, &r, &s) != 4)
        return out;
//    sprintf(out, "%u.%u.%u.%u", p, q, r, s);
	
    sprintf(out, "%u.%u.%u.%u", s, r, q, p);
	
	/*int arrEnd = sizeof(out);
	
	for(int x=0; x<arrEnd; x++){
		out[x] = revOut[arrEnd];
		arrEnd -= 1;	
	}
	cout << out << "||" << revOut << "\n";
*/
    return out;
}

/**
	Parses linux proc file to get default gateway addr. Very non-portable. 
	
	@param fLocation location of proc file
	@returns gatewayAddr char* array holding ipv4 address of default LAN GW 
	if now default GW found, returns 0
*/
char* parseProc(string fLocation){
	//create vector to hold proc file contents
	vector <string> procTokens;
	string procLine;
	string token;
	int colCount = 0;
	regex hexIP("([A-Z]|[0-9]){8}");

	//read in proc file
	ifstream routeF(fLocation);
	while(getline(routeF, procLine)){
		istringstream iss(procLine);
		//tokenize file - columns are delimited by tabs
		while(getline(iss, token,'\t')){
			/* use RE to check the token for hex-formatted IP addresses,
			if match, add to vector array */
			if(regex_match(token, hexIP)){
				procTokens.push_back(token);
			}	
		}
		//when line ingested, check for default GW in token array
		if((procTokens.size() >= 1) && (procTokens.at(0) == "00000000")){
			char* decIP = hex2DecIP(procTokens.at(1).c_str());
			if(decIP){
				routeF.close();
				return decIP;
			}
			}	
		//clear out token array for next line
		procTokens.clear();
			
	}
	routeF.close();
	return 0;
}

/**
	Perform connectivity checks to network and NASA APIs. Writes out the status 
	of the checks
		
	@return	ntwrkOK		bool value - true if can connect to NASA APIs
*/
bool netCheck(){
	//set up variables
	bool ntwrkOK = false;
	char addrToTest[] = "8.8.8.8"; //change to use new site to test internet 
	struct hostent *externalSite = NULL;
	struct in_addr externalAddr;
	string procLocation = "/proc/net/route";	


	//build display strings
	string chkSetup = "PERFORMING SETUP TASKS\n";
	string lineBrk = "-----------------------\n";
	string netChk = "Checking network connectivity....";
	string inetChk = "Testing connection to internet....";
	char nasaC[] = "Attempting to communicate w/NASA API....";
	char goodStart[] = "INITALIZATION SUCCESSFUL";
	char badStart[] = "INITALIZATION FAILED";
	char success[] = "[OK]";
	char fail[] = "[FAILED]";
	char* gwIP;

		
	//begin self-check procedures
	cout << lineBrk << chkSetup << lineBrk;

	//check LAN connection
	gwIP = parseProc(procLocation);
	cout << "GATEWAY: " << gwIP << "\n";
	//check inet connectivity using gethstbyaddr (default: google dns)
	cout << inetChk << "\r";
	inet_pton(AF_INET, addrToTest, &externalAddr);
	externalSite = gethostbyaddr(&externalAddr, sizeof externalAddr, AF_INET);
	
	if(externalSite != NULL){
		inetChk = inetChk + "[SUCCESS]\n";
		cout << inetChk;
	}else{
		printf("ERROR: No internet connectivity");
	}



	/*
	//set up socket
	sockfd = -1;
	
	if(google_ent != NULL){
		if(sockfd = socket(google_ent->h_addrtype,SOCK_STREAM,IPPROTO_TCP) 
		!= -1){
				cout << "good thus far";
				cout << "sockfd" << sockfd;
				cout << "google_ent" << google_ent;
				cout << "socket" << socket(google_ent->h_addrtype,SOCK_STREAM,
				IPPROTO_TCP);
		}

}
	


	//clean up socket
	if(sockfd!=-1)
        close(sockfd);
*/
	return ntwrkOK;
}

/**
	Main program
	
	@param argc		argument count
	@param argv		arguments passed via command line
	@return			int
*/
int main(int argc, char* argv[]){
	//set up constants
	const char DECORATION[] = "==============================================="
	"============\n";
	const char ROOT_TITLE[] = "\033[1;37;44mplanetStrike - Live Near Earth "
	"Object Collision Calculator\033[0m\n";
	
	//set up variables
	string dummyInput = "";
	bool netStatus;
	
	//clear the screen, display startup information
	cout << DECORATION << ROOT_TITLE << DECORATION << "\n";

	string input = "";
		
	netStatus = netCheck();

	cout << "Press 'Enter' to continue......";
	getline(cin, input);
	
	//cleanup & exit
	return 0;
}
