/*
    @project    pStrike
    @file       neoAPI.cpp - functions that speak w/NASA's NeoWs
    @author     Rob Cilla
*/

#include "neoAPI.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <iostream>

static size_t WriteCallback(void *contents, 
							size_t size, 
							size_t nmemb, 
							void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool NEOAPI::testAPIConn(){
	//set up URL of NASA demo query
	char demoURLBuff[256] = "https://api.nasa.gov/neo/rest/v1/feed?start_date="
	"2015-09-07&end_date=2015-09-08&api_key=DEMO_KEY";
	char *url = demoURLBuff;
	std::string upTest = "\"self\" : \"https://api.nasa.gov/neo/rest/v1/neo/"
	"3726710?api_key=DEMO_KEY\"";
	
	CURL *curl;
	CURLcode res;
	std::string readBuffer; 
	
	curl = curl_easy_init();

	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		
		if(readBuffer.find(upTest) != std::string::npos){
			curl_easy_cleanup(curl);
			return true;
		}
	}
	
	curl_easy_cleanup(curl);
	return false;	
}
