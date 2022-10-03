#ifndef NUMBER_H
#define NUMBER_H
#include <string>
#include <regex>
#include <Util.h>
#include <Settings.hxx>
#include <cmath>
#include <iostream>
#include <sstream>
extern std::string mode;

class Number{
    public:
        Number(float number);
        Number(std::string number);
        inline Number operator / (Number const &m){
              return Number(data.decimalNumber / m.data.decimalNumber);
        }
        inline Number operator * (Number const &m){
              return Number(data.decimalNumber * m.data.decimalNumber);
        }
        inline Number operator - (Number const &m){
              return Number(data.decimalNumber - m.data.decimalNumber);
        }
        inline Number operator + (Number const &m){
              return Number(data.decimalNumber + m.data.decimalNumber);
        }
    
        inline std::string to_string (){
            if(mode == "Decimal") {
                return std::to_string(data.decimalNumber);
            }else if(mode == "Binary"){
                std::bitset<32> bits(data.binary);
                return bits.to_string();
            }else if(mode == "Hexadecimal"){
                data.signedExponentMantissaNumber = (int32_t)data.decimalNumber;
                std::stringstream ss;
                ss << std::uppercase << std::hex;
                for(int i = 0; i < sizeof(data.hex);i++){
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
            char hex[sizeof(float)];
                

        }data;
};



#endif