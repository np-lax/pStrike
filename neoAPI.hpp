#ifndef ___NEOAPI_HPP_
#define __NEOAPI_HPP_

#include <string>

class NEOAPI{
	public:
		std::string accessNEO(std::string url, std::string apiKey);
		bool testAPIConn();
		
};


#endif

