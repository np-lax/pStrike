/*
    @project    pStrike
    @file       ping.cpp - used to check for route to default gateway
    @author     Rob Cilla
*/

#include "ping.hpp"
int pingA::sysPing(std::string ipAddr, int attempts){
	//set up stream, file, buffer, and variables
	std::stringstream sstream;
	std::string sysCmd;
	FILE *inF;
	char buff[512];
	int exitCode;
	//attempt to use system to ping
	try{
		sysCmd = "ping -c " + std::to_string(attempts) + " " + ipAddr + " 2>&1"; 
		
		//std::cout << "syscmd:" << sysCmd << "\n";

		//start a read-only process
		if(!(inF = popen(sysCmd.c_str(), "r"))){
			//if error, spit it out and return -1
			std::cerr << __FILE__ << "(" << __FUNCTION__ << ":" << __LINE__ << 
			") | popen error = " << std::strerror(errno) << std::endl;
	
			return -1; 
		}
		
		//else, capture response in stream
		while(fgets(buff, sizeof(buff), inF) !=NULL){
			sstream << buff;
		}
		
		//get exit status of cmd
		exitCode = pclose(inF); 
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
	return (exitCode == 0);

} 
