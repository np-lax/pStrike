/*
    @project    pStrike
    @file       neoAPI.hpp
    @author     Rob Cilla
*/
#ifndef __NETUTILS_HPP_
#define __NETUTILS_HPP_


#include <string>

std::string conv_hex_ip(const char *in);

std::string parse_proc_file();

bool comms_check();

#endif
