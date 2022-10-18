#ifndef SEMNUMBER_H
#define SEMNUMBER_H

#include <cmath>
#include <bit>
#include <bitset>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

class SEMNumber{
    public:
        SEMNumber(string sign,string exponent,string mantissa);
        SEMNumber(string numString);
        SEMNumber(double number);
        inline SEMNumber operator*(const SEMNumber& RHS ){
            return SEMNumber(decimalNumber * RHS.decimalNumber);
        }
        inline SEMNumber operator-(const SEMNumber& RHS ){
            return SEMNumber(decimalNumber - RHS.decimalNumber);
        }
        inline SEMNumber operator+(const SEMNumber& RHS ){
            return SEMNumber(decimalNumber + RHS.decimalNumber);
        }
        inline string toString(){
            stringstream ss;
            if(this->isNaN){
                ss << "The input is NaN.";
            }else if(this->isINF){
                ss << "The input is " << (this->bits[0] == 0?"positive ":"negative ") << "infinity";
            }else{
                //Decimal output
                ss << "Decimal: " << this->decimalNumber << endl;
                //HEX output
                ss << "Hexadecimal: " << hex;
                ss << endl;
                ss.clear();

                //SEH output
                ss << "SEH: " << this->signHex << "|" << this->exponentHex << "|" << this->mantissaHex;
                ss << endl;
                //SEM-binary output
                for(int i = 0; i < bits.size(); i++){
                    if(i == 1 || i == 9){
                        ss << "|";
                    }
                    ss << bits[i];
                }
                ss << endl;
                if(!this->isNormal){
                    ss << "--- Float is denormalized! ---" << endl;
                }else{
                    ss << "--- Float is normalized! ---" << endl;
                }
            }
            return ss.str();
        }
        double decimalNumber;
        string signHex;
        string exponentHex;
        string mantissaHex;
        string hex;
        bitset<32> bits;
        bool isNaN = false;
        bool isINF = false;
        bool isNormal = true;
};




#endif