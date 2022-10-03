#ifndef UTIL_H
#define UTIL_H
#include <Settings.hxx>
#include <regex>
#include <string>
#include <Number.h>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
    enum type{DECIMAL,BINARY,HEX,SEM,INVALID};

    std::string solveEquation(std::string equation);
    int isValidEquation(std::string equation);
    uint8_t getType(std::string number);

#endif