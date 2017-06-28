/*
    @project	pStrike
	@file		netUtils.cpp - centralizes various ntwrk-related functions
	@author		Rob Cilla
*/

#include "../include/netUtils.hpp"
#include "../include/neoAPI.hpp"
#include "../include/ping.hpp"
#include <stdio.h>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

/*
    hex2DecIP:Converts hex IP address to 4-octet notation 
    
    @param *in array holding the (reversed as in proc table) GW IP addr in hex
    @returns convIP string holding ipv4 address of default LAN GW 
*/
string hex2DecIP(const char *in)
{
    char *convIP = (char*)malloc(sizeof(char) * 16);

    unsigned int p, q, r, s;

    if (sscanf(in, "%2x%2x%2x%2x", &r, &q, &p, &s) != 4)
        return convIP;

    sprintf(convIP, "%u.%u.%u.%u", s, p, q, r);

    string convIPStr(convIP);

    return convIPStr;
}


/*
    parseProc - Parses linux proc file to get default gateway addr
	(very much non-portable)
    
    @returns gatewayAddr char* array holding ipv4 address of default LAN GW 
    if now default GW found, returns 0
*/
string parseProc(){
    //vector array holds contents of /proc
    vector <string> procTokens;
    string procLine = " ";
    string token= " ";
	string fLocation = "/proc/net/route";
    int colCount = 0;
    regex hexIP("([A-Z]|[0-9]){8}");

    //read in proc file
    ifstream routeF(fLocation);
    while(getline(routeF, procLine)){
        istringstream iss(procLine);
        //tokenize file - columns are delimited by tabs
        while(getline(iss, token,'\t')){
            /* use RE to check the token for hex-formatted IP addresses,
            if match, add to array */
            if(regex_match(token, hexIP)){
                procTokens.push_back(token);
            }
        }
        //when line ingested, check for default GW in token array
        if((procTokens.size() >= 1) && (procTokens.at(0) == "00000000")){
            //if line contains default GW, convert IP to octet notation
			string decIP = hex2DecIP(procTokens.at(1).c_str());
            if(decIP != ""){
                routeF.close();
                return decIP;
            }
        }
        //clear out token array for next line
        procTokens.clear();

    }
    //clean up & return
    routeF.close();
    return "-1";
}

/**
    Perform connectivity checks to network and NASA APIs. Writes out the status 
    of the checks
*/
void netCheck(){
    //set up variables
    bool ntwrkOK = false;
    char addrToTest[] = "8.8.8.8"; //change to use new site to test internet 
    struct hostent *externalSite = NULL;
    struct in_addr externalAddr;
    string procLocation = "/proc/net/route";


    //build display strings
    string chkSetup = "PERFORMING START-UP TASKS\n";
    string lineBrk = "-----------------------\n";
    string netChk = "Checking network connectivity....";
    string inetChk = "Testing connection to internet....";
    string nasaChk = "Attempting to connect to NASA Near Earth Object "
    "Database....";

    //begin self-check procedures
    cout << lineBrk << chkSetup << lineBrk;

    //check LAN connection by pinging gateway
    cout << netChk << "\r";

    pingA pingTestObj;
    string test = parseProc();
    int result = pingTestObj.sysPing(parseProc(), 4);
    if(result == 1){
        netChk = netChk + "[SUCCESS]\n";
        cout << netChk;
    }else{
        netChk = netChk + "[FAILED]\n";
        cout << netChk;
        printf("ERROR: unable to ping gateway...exiting\n");
        exit(0);
	}

    //check inet connectivity using gethstbyaddr (default: google dns)
    cout << inetChk << "\r";
    inet_pton(AF_INET, addrToTest, &externalAddr);
    externalSite = gethostbyaddr(&externalAddr, sizeof externalAddr, AF_INET);

    if(externalSite != NULL){
        inetChk = inetChk + "[SUCCESS]\n";
        cout << inetChk;
    }else{
        inetChk = inetChk + "[FAILED]\n";
        cout << inetChk;
        cout << "ERROR: unable to reach internet...exiting\n";
        exit(0);
    }

    //check ability to recieve NASA NEO API data
    cout << nasaChk << "\r";

    NEOAPI n;

    if(n.testAPIConn()){
        nasaChk = nasaChk + "[SUCCESS]\n\n\n";
        cout << nasaChk;
    }else{
        nasaChk = nasaChk + "[FAILED]\n";
        cout << nasaChk;
        cout << "ERROR: unable to get data from NASA NEO server...exiting\n";
        exit(0);
    }
}
	
