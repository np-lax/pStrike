#include "../include/neo_web_functs.hpp"
#include "../include/neo_class.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

/*
	read_curl_data - read in data returned from CURLOPT_WRITEDATA
	
	@param	*contents
	@param	size
	@param nmemb
	@param *userp
	@return size * nmemb - amount of data read:
*/
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
   
    @param   api_key     specific NASA api key to use
    @returns read_buffer string containing downloaded neoWs data
*/
string initial_neo_data_dl(string api_key){
	string neo_ws_chk = "Checking in w/NASA Near Earth Object Web Service..";

	string neo_ws_dl = "Downloading initial NEO dataset...................";
	
	cout << neo_ws_chk << "\r";

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
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_curl_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        //execute curl query
        result = curl_easy_perform(curl);

        //check response
        if (result != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(result));
        }

        //get & check HTTP response code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_resp);
        if (http_resp == 200) {
            cout << neo_ws_chk + "[SUCCESS]\n";
		}

		//attempt to get today's NEO data set
		cout << neo_ws_dl << "\r";

		if (!read_buffer.empty()) {
        	cout << neo_ws_dl + "[SUCCESS]\n";
            return read_buffer;
		} else {
            cout << "[ERROR]Got no data from NASA NeoWS....exiting";
           	exit(0);
        }
    }

    curl_easy_cleanup(curl);
	return "-1";
}

/*
    build_neo_objs: take in data from NeoWs and turn into NEO objects 
   
    @param   initial_data   string returned from initial_neo_data_dl
    @returns neo_arr        vector array of NEO objects
*/

vector<Near_earth_object> build_neo_objs(string initial_data){
//declare/set variables for search functions
    string temp_line;  
    string delimiter = ": ";
    string eol = ",";
    int line_count = -99; //-1 to skip switch at first loop-through
    int token_size = 0;

    //declare/set vars req'd for neo object
    vector<Near_earth_object> neo_arr;
    int el_ct;
    int id; 
    string neo_name;
    double max_d;
    double min_d;
    bool is_haz;
    string app_date;
    double app_vel;
    int miss_dist;

    string tmp_str;

    //read in NEO data from string
    stringstream ss(initial_data);
    
    //process the initial_data string
    if (!initial_data.empty()) {
        while (getline(ss, temp_line, '\n')) {
            if (temp_line.find("neo_reference_id") != string::npos) {
                //perform NEO start tasks
                //set line count for NEO obj
                line_count = 0;

                //increment element counter
                el_ct += 1;

                //clear variables
                neo_name = ""; 
                max_d = 0;
                min_d = 0;
                is_haz = false;
                app_date = ""; 
                app_vel = 0;
                miss_dist = 0;
            }

            //get data based on line number in initial_data string
            switch (line_count) {
                case 0: { 
                    id = atoi(temp_line.substr(temp_line.find("neo_reference_id") + 21, 7).c_str());
                    line_count += 1;
                    break;
                }
                case 1: { 
                    token_size = (temp_line.find(",")) - (temp_line.find(": "));
                    neo_name = temp_line.substr(16, temp_line.length() - 18);
                    line_count += 1;
                    break;
                }
                case 10: { 
                    token_size = (temp_line.find(",") - (temp_line.find(":")));
                    min_d = atof(temp_line.substr(temp_line.find(":") + 2, token_size - 2).c_str());
                    line_count += 1;
                    break;
                }
                case 11: { 
                    token_size = (temp_line.find(",") - (temp_line.find(":")));
                    max_d = atof(temp_line.substr(temp_line.find(":") + 2, token_size - 2).c_str());
                    line_count += 1;
                    break;
                }
                case 22: {
                    token_size = (temp_line.find(",") - (temp_line.find(":")));
                    tmp_str = temp_line.substr(temp_line.find(":") + 2, token_size - 2);
                    if (tmp_str.find("true") != string::npos) {
                        is_haz = true;
                    } else {
                        is_haz = false;
                    }
                    line_count += 1;
                    break;
                }
                case 24: {
                    token_size = (temp_line.find(",") - (temp_line.find(":")));
                    app_date = temp_line.substr(temp_line.find(":") + 3, token_size - 4);
                    line_count += 1;
                    break;
                }
                case 28: { 
                    token_size = (temp_line.find(",") - (temp_line.find(":")));
                    app_vel = atof(temp_line.substr(temp_line.find(":") + 3, token_size - 4).c_str());
                    line_count += 1;
                    break;
                }
                case 34: { 
                    token_size = (temp_line.find(",") - (temp_line.find(":")));
                    miss_dist = atof(temp_line.substr(temp_line.find(":") + 3, token_size - 4).c_str());
                    line_count += 1;
                    break;
                }
                case 37: { 
                    Near_earth_object neo_n (id, neo_name, max_d, min_d, is_haz, app_date, app_vel, miss_dist);
                    neo_arr.push_back(neo_n);
                    line_count += 1;
                    break;
                }
                default: {
                    line_count += 1;
                }
            }

        }
    }
    
    
    cout << "\n**    " << neo_arr.size() << " Near Earth Objects added to local database    **" << endl;

    return neo_arr;
}

