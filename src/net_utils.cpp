/*
    @project	pStrike
	@file		netUtils.cpp - centralizes various ntwrk-related functions
	@author		Rob Cilla
*/

#include "../include/net_utils.hpp"
#include "../include/ping.hpp"
#include "../include/neoWs.hpp"
#include <stdio.h>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

using namespace std;

/*
    conv_hex_ip:Converts hex IP address to 4-octet notation 
    
    @param *in array holding the (reversed as in proc table) GW IP addr in hex
    @returns convIP string holding ipv4 address of default LAN GW 
*/
string conv_hex_ip(const char *in){
    char *conv_ip = (char*)malloc(sizeof(char) * 16);

    unsigned int p, q, r, s;

    if (sscanf(in, "%2x%2x%2x%2x", &r, &q, &p, &s) != 4)
        return conv_ip;

    sprintf(conv_ip, "%u.%u.%u.%u", s, p, q, r);

    string conv_ip_str(conv_ip);

    return conv_ip_str;
}


/*
    parse_proc_file - Parses linux proc file to get default gateway addr
	(very much non-portable)
    
    @returns gatewayAddr char* array holding ipv4 address of default LAN GW 
    if now default GW found, returns 0
*/
string parse_proc_file(){
    //vector array holds contents of /proc
    vector <string> proc_tokens;
    string proc_line = " ";
    string token= " ";
	string f_location = "/proc/net/route";
    regex hex_ip("([A-Z]|[0-9]){8}");

    //read in proc file
    ifstream route_f(f_location);
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
}

/**
    connectivity_chk -Perform connectivity checks to network and NASA APIs. 
    Writes out the status of the checks
*/
bool comms_check(){
    //set up variables
    char addr_to_test[] = "8.8.8.8"; //change to use new site to test internet 
    struct hostent *external_site = NULL;
    struct in_addr external_addr;
    string proc_location = "/proc/net/route";

    //build display strings
    string net_chk = "Checking network connectivity.....................";
    string inet_chk = "Testing connection to internet....................";

    //check LAN connection by pinging gateway
    cout << net_chk << "\r";

    //parse the procfile, check results
    int ping_result = sys_ping(parse_proc_file(), 4);
    if(ping_result == 1){
        net_chk = net_chk + "[SUCCESS]\n";
        cout << net_chk;
    }else{
        net_chk = net_chk + "[FAILED]\n";
        cout << net_chk;
        printf("ERROR: unable to ping gateway...exiting\n");
        exit(0);
	}

    //check inet connectivity using gethstbyaddr (default: google dns)
    cout << inet_chk << "\r";
    inet_pton(AF_INET, addr_to_test, &external_addr);
    external_site = gethostbyaddr(&external_addr, sizeof external_addr, AF_INET);

    if(external_site != NULL){
        inet_chk = inet_chk + "[SUCCESS]\n";
        cout << inet_chk;
    }else{
        inet_chk = inet_chk + "[FAILED]\n";
        cout << inet_chk;
        cout << "ERROR: unable to reach internet...exiting\n";
        exit(0);
    }	
	
	return true;	
}
	
