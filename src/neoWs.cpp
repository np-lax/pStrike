#include "../include/neoWs.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <string>
#include <iostream>
/*
	read_curl_data - read in data returned from CURLOPT_WRITEDATA
	
	@param	*contents
	@param	size
	@param nmemb
	@param *userp
	@return size * nmemb - amount of data read:
*/

using namespace std;

static size_t read_curl_data(void *contents,
                            size_t size,
                            size_t nmemb,
                            void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/*
    get_today_neo_data: test GET using curl/apiKey and
			get today's NEO feed from NeoWs database 
   
    @param   api_key    specific NASA api key to use (default is DEMO_KEY)
    @returns neo_array  vector array of pointers to nearEarthObjects
*/
string initial_neo_data_dl(string api_key){
	string neoWs_chk = "Checking in w/NASA Near Earth Object Web Service..";

	string neoWs_dl = "Downloading initial NEO dataset...................";
	
	cout << neoWs_chk << "\r";

    //set url for today's NEO feed
	string base_url = "https://api.nasa.gov/neo/rest/v1/feed/today?detailed=" 
	"true&api_key=" + api_key;

    //convert to char* as req'd by curl
    const char* url = base_url.c_str();

    //setup curl obj + vars to read data returned
    CURL *curl;
    CURLcode result;
    std::string read_buffer;
    long http_resp;

    //initalize curl
    curl = curl_easy_init();

    //set options
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_curl_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        //execute curl query
        result = curl_easy_perform(curl);

        //check response
        if(result != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(result));
        }

        //get & check HTTP response code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_resp);
        if(http_resp == 200){
			neoWs_chk = neoWs_chk + "[SUCCESS]\n";
        	cout << neoWs_chk;
		}

		//attempt to get today's NEO data set
		cout << neoWs_dl << "\r";

		if(!read_buffer.empty()){
        	cout << neoWs_dl + "[SUCCESS]\n";
            return read_buffer;
		}else{
            cout << "[ERROR]Got no data from NASA NeoWS....exiting";
           	exit(0);
        }
    }

    curl_easy_cleanup(curl);
	return "-1";
}

