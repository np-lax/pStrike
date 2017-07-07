/*
    neo_class - defines near earth object class & methods

    @project    pStrike
    @file       neo_class.cpp
    @author     Rob Cilla
*/

#include "../include/neo_class.hpp"
#include <string>


//near earth object constructor
Near_earth_object::Near_earth_object(   int id, 
                                        std::string neo_name,
                                        double max_d,
                                        double min_d,
                                        bool is_haz,
                                        std::string app_date,
                                        double app_vel,
                                        int miss_dist){

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
std::string Near_earth_object::get_name(){
    return name;
}

