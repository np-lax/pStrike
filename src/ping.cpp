/*
    @project    pStrike
    @file       ping.cpp - used to check for route to default gateway
    @author     Rob Cilla
*/

#include "../include/ping.hpp"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cerrno>
#include <cstring> 

int sys_ping(std::string ip_addr, int ping_attempts){
	//set up stream, file, buffer, and variables
	std::stringstream sstream;
	std::string sys_cmd;
	FILE *in_file;
	char response_buff[512];
	int exit_code;
	//attempt to use system to ping
	try{
		sys_cmd = "ping -c " + std::to_string(ping_attempts) + " " + ip_addr + " 2>&1"; 
		
		//start a read-only process
		if(!(in_file = popen(sys_cmd.c_str(), "r"))){
			//if error, spit it out and return -1
			std::cerr << __FILE__ << "(" << __FUNCTION__ << ":" << __LINE__ << 
			") | popen error = " << std::strerror(errno) << std::endl;
	
			return -1; 
		}
		
		//else, capture response in stream
		while(fgets(response_buff, sizeof(response_buff), in_file) !=NULL){
			sstream << response_buff;
		}
		
		//get exit status of cmd
		exit_code = pclose(in_file); 
	}catch(const std::exception &e){
		std::cerr << 
		__FILE__ << 
		"(" << 
		__FUNCTION__ << 
		":" <<
		 __LINE__ << 
		") | e.what() = " << 
		e.what() << 
		std::endl;      
        
		return -2;
	}
	return (exit_code == 0);

} 
