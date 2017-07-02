/*
	pStrike - A CLI tool for calculating theoretical asteroid strikes on
	planets in the solar system using data from NASA's Near Earth Object Web 
	Service API
	
	main.cpp

	@author Rob Cilla
	@version 0.0 24 Jun 17
*/

#include "../include/net_utils.hpp" 
#include "../include/neo_web_functs.hpp"
#include "../include/neo_class.hpp"
#include <stdlib.h>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>


using namespace std;


/*
	main - main prgm loop
	
	@param argc		argument count
	@param argv		arguments passed via command line
	@return			exit status

*/
int main(int argc, char* argv[]){
	const char DECORATION[] = "==============================================="
	"============\n";
	const char ROOT_TITLE[] = "\033[1;37;44mplanetStrike - Near Earth "
	"Object Collision Calculator\033[0m     |\n";

	string input = "";	
	
	//clear the screen, display startup information
	cout << "\033[2J\033[1;1H";
	cout << DECORATION << ROOT_TITLE << DECORATION;

    //begin self-check procedures
    string chk_setup = "PERFORMING START-UP TASKS|\n";
    string line_brk =  "--------------------------\n";
    cout << line_brk << chk_setup << line_brk;
	
	//check LAN/inet
	int comm_res = comms_check();

	//test API key & get current NEO data
	string initial_data = initial_neo_data_dl("DEMO_KEY");
    
    //near_earth_object neo1(6, 3214123, "obj1", 400, 200, true, "2017-07-30", 20000, 4000);

    //cout << neo1.get_name() << endl;

    //vector array holds contents of NEO data
    
    //declare/set variables for search functions
    string temp_line;  
    string delimiter = ": ";
    string eol = ",";
    int line_count = -99; //-1 to skip switch at first loop-through
    int token_size = 0;

    //declare/set vars req'd for neo object
    vector<near_earth_object> neo_arr;
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
    
    //neo starts with '"links" : {' and ends with '"orbiting_body"'
    if(!initial_data.empty()){
        while(getline(ss, temp_line, '\n')){
            if(temp_line.find("neo_reference_id") != string::npos){
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
                    
                    //iterate next line
                   // continue;
            }
            
            //get data based on line number in NEO object
            switch(line_count){
                case 0: { id = atoi(temp_line.substr(temp_line.find("neo_reference_id") + 21, 7).c_str());
                        line_count += 1;
                        break;
                }

                case 1: { token_size = (temp_line.find(",")) - (temp_line.find(": "));
                          

                        neo_name = temp_line.substr(temp_line.find(": ") + 3, token_size - 6);
                        line_count += 1;
                        break;
                }
                            
                case 10: { token_size = (temp_line.find(",") - (temp_line.find(":")));
                         min_d = atof(temp_line.substr(temp_line.find(":") + 2, token_size - 2).c_str());
                         line_count += 1;
                         break;
                }
                
                case 11: { token_size = (temp_line.find(",") - (temp_line.find(":")));
                        max_d = atof(temp_line.substr(temp_line.find(":") + 2, token_size - 2).c_str());
                        line_count += 1;
                        break;
                }
                case 22: token_size = (temp_line.find(",") - (temp_line.find(":")));
                        tmp_str = temp_line.substr(temp_line.find(":") + 2, token_size - 2);
                        if(tmp_str.find("true") != string::npos){
                            is_haz = true;                    
                        }else{
                            is_haz = false;
                        }
                        line_count += 1;
                        break;

                case 24: {token_size = (temp_line.find(",") - (temp_line.find(":")));
                        app_date = temp_line.substr(temp_line.find(":") + 3, token_size - 4);
                        line_count += 1;
                        break;
                }
                                
                case 28: { token_size = (temp_line.find(",") - (temp_line.find(":")));
                        app_vel = atof(temp_line.substr(temp_line.find(":") + 3, token_size - 4).c_str());
                        line_count += 1;
                        break;
                }

                case 34: { token_size = (temp_line.find(",") - (temp_line.find(":")));
                        miss_dist = atof(temp_line.substr(temp_line.find(":") + 3, token_size - 4).c_str());
                        line_count += 1;
                        break;
                }
                case 37: { near_earth_object neo_n (id, neo_name, max_d, min_d, is_haz, app_date, app_vel, miss_dist);
                         neo_arr.push_back(neo_n);
                         line_count += 1;
                         break;
                }

                default:{line_count += 1;}
              }

            }

    }

    for(near_earth_object obj : neo_arr){
            cout << "TEST:" << obj.get_name() << endl;
        }
/*
    if(!initial_data.empty()){
        while(getline(ss, temp_line, '\n')){
            //check for header containing element count
            if(temp_line.find("element_count") != string::npos){
                //find number of elements in NEO data
                num_neo_elements = atoi(temp_line.substr(temp_line.find(delimiter) + 2, 1).c_str());            
            //if line contains ref_id, it is the start of a new NEO obj
            }else if(temp_line.find("\"neo_reference_id\" : \"" != string::npos){
                    id = atoi(temo_line.find()),
                    std::string neo_name,
                    double max_d,
                    double min_d,
                    bool is_haz,
                    std::string app_date,
                    double app_vel,
                    int miss_dist                   
            }
        }
    }
    */


	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	

	cout << "Press 'Enter' to continue......";
	getline(cin, input);
	
	//cleanup & exit
	return 0;
}
