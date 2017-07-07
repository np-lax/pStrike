/*
	pStrike
    @file       neoWs.hpp
    @author     Rob Cilla
*/
#ifndef __NEO_WEB_FUNCTS_HPP_
#define __NEO_WEB_FUNCTS_HPP_

#include "neo_class.hpp"
#include <string>
#include <vector>

std::string initial_neo_data_dl(std::string api_key);

std::vector<Near_earth_object> build_neo_objs(std::string initial_data);

#endif
