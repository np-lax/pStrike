/*
    @project    pStrike
    @file       neoAPI.hpp
    @author     Rob Cilla
*/
#ifndef __NETUTILS_HPP_
#define __NETUTILS_HPP_

#include <string>

void getNEOData(int numDays, std::string apiKey);

std::string hex2DecIP(const char *in);

std::string parseProc();

void netCheck();

#endif
