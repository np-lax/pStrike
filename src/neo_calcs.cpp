/*
    @project    pStrike
    @file       neo_calcs.cpp - perform calculations on selected NEO
    @author     Rob Cilla
*/
#include "../include/neo_calcs.hpp"
#include "../include/neo_class.hpp"
#include <iostream>

using namespace std;

void obj_selected (Near_earth_object neo) {
    cout << "NEAR EARTH OBJECT: " << neo.get_name() << endl;
    
}
