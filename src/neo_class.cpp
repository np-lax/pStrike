/*
    neo_class - defines near earth object class & methods

    @project    pStrike
    @file       neo_class.cpp
    @author     Rob Cilla
*/

#include "../include/neo_class.hpp"
#include <string>


//near earth object constructor
near_earth_object::near_earth_object(int el_ct,
                                    int id, 
                                    std::string neo_name,
                                    double max_d,
                                    double min_d,
                                    bool is_haz,
                                    std::string app_date,
                                    double app_vel,
                                    int miss_dist){

    element_count = el_ct;
    ref_id = id;
    name = neo_name;
    max_diameter = max_d;
    min_diameter = min_d;
    is_hazardous = is_haz;
    close_approach_date = app_date;
    approach_velocity = app_vel;
    miss_distance = miss_dist;
}


//accessors
std::string near_earth_object::get_name(){
    return name;
}

