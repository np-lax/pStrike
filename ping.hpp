#ifndef __PING_HPP_
#define __PING_HPP_

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cerrno>
#include <cstring>

class pingA{
	private:
		int socketPing(
		std::string ipAddr, 
		int attempts, 
		bool chkEth = false, 
		int ethPort = 0);
	
	public:
		int sysPing(std::string ipAddr, int attempts);

};

#endif
