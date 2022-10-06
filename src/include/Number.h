#ifndef NUMBER_H
#define NUMBER_H
#include <string>
#include <regex>
#include <Util.h>
#include <Settings.hxx>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bit>
#include <bitset>
extern std::string mode;

class Number{
    public:
        Number(uint32_t number);
        Number(float number);
        Number(std::string number);
        inline Number operator / (Number const &rhs){
            if(mode == "Binary" || mode == "Hexadecimal"){
                return Number((uint32_t)(data.binary/rhs.data.binary));
            }
              return Number(data.decimalNumber / rhs.data.decimalNumber);
        }
        inline Number operator * (Number const &rhs){
            if(mode == "Binary" || mode == "Hexadecimal"){
                return Number((uint32_t)(data.binary*rhs.data.binary));
            }
              return Number(data.decimalNumber * rhs.data.decimalNumber);
        }
        inline Number operator - (Number const &rhs){
            if(mode == "Binary" || mode == "Hexadecimal"){
                return Number((uint32_t)(data.binary-rhs.data.binary));
            }
              return Number(data.decimalNumber - rhs.data.decimalNumber);
        }
        inline Number operator + (Number const &rhs){
            if(mode == "Binary" || mode == "Hexadecimal"){
                return Number((uint32_t)(data.binary+rhs.data.binary));
            }
              return Number(data.decimalNumber + rhs.data.decimalNumber);
        }
    
        inline std::string to_string (){
            if(mode == "Decimal") {
                std::stringstream ss;
                ss.precision(10);
                ss << data.decimalNumber;
                return ss.str();
            }else if(mode == "Binary"){
                std::bitset<32> bits(data.binary);
                return bits.to_string();
            }else if(mode == "Hexadecimal"){
                std::stringstream ss;
                ss << std::uppercase << std::hex;
                for(int i = sizeof(data.hex) -1; i >= 0;i--){
                    ss << +data.hex[i];
                }
                return ss.str();
            }else{
                std::bitset<32> bits(data.signedExponentMantissaNumber);
                return bits.to_string();
            }
        }
        union number_data
        {
            int32_t signedExponentMantissaNumber;
            uint32_t binary;
            float decimalNumber;
            unsigned char hex[sizeof(float)];
                

        }data;
};



#endif