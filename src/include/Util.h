#ifndef UTIL_H
#define UTIL_H
#include <Settings.hxx>
#include <regex>
#include <string>
#include <SEMNumber.h>
#include <iostream>
#include <bitset>
using namespace std;
    enum type{DECIMAL,BINARY,HEX,SEM,INVALID};

    std::string solveEquation(std::string equation);
    std::tuple<std::vector<SEMNumber>,std::string,int> parseInput(std::string equation);
    uint8_t getType(std::string number);
    bitset<32> getBinaryFromHex(string hexString);
    std::string getHexFromBinary(bitset<32> bits);
    tuple<std::string,std::string,std::string> getSEMHexFromBinary(bitset<32> bits);
    uint32_t reverseBits(uint32_t n);



#endif