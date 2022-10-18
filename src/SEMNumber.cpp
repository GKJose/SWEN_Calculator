#include <SEMNumber.h>
#include<Util.h>
SEMNumber::SEMNumber(string sign,string exponent,string mantissa){
    
    bits |= bitset<32>(stoul(sign,nullptr,16)) << 32;
    bits |=  bitset<32>(stoul(exponent,nullptr,16)) << 23;
    bits |=  bitset<32>(stoul(mantissa,nullptr,16));
    bits = stoul(bits.to_string(),nullptr,2);
    cout << bits.to_string() << endl;
    this->signHex += "0x";
    this->exponentHex += "0x";
    this->mantissaHex += "0x";
    stringstream ss;
    this->signHex += bits.to_string().at(0);
    ss.clear();
    ss.str("");
    
    uint temp = stoul(bits.to_string().substr(1,8),nullptr,2);
    ss << uppercase << setbase(16);
    ss << temp;
    this->exponentHex += ss.str();
    cout << exponentHex << std::endl;
    ss.str("");
    ss.clear();

    temp = stoul(bits.to_string().substr(9,31),nullptr,2);
    ss << uppercase << setbase(16);
    ss << temp;
    this->mantissaHex += ss.str();

    double mant = 0.0;
    mant += (bits[0] == 1?1:0)/(pow(2,23));
    for(int i = 1; i < 23; i++){
        mant += (bits[0] == 1?1:0)/(pow(2,23-i));
    }

    this->decimalNumber = pow(-1,(bits[31] == 1)?1:0)*(1.0f + mant)*pow(2,stoul(bits.to_string().substr(1,8),nullptr,2)-127);
    this->bits = bitset<32>(reverseBits(stoul(bits.to_string(),nullptr,2)));


    this->isNormal = abs(this->decimalNumber) > std::numeric_limits<float>::min();
    this->isINF = abs(this->decimalNumber) > std::numeric_limits<float>::max();
    this->isNaN = bitset<32>(stoi(exponentHex,nullptr,16)).all() && bitset<32>(stoi(mantissaHex,nullptr,16)).any();
    this->hex = getHexFromBinary(bits);
}
SEMNumber::SEMNumber(string numString){
    this->signHex += "0x";
    this->exponentHex += "0x";
    this->mantissaHex += "0x";
    stringstream ss;
    ss << hex;
    if(getType(numString) == type::HEX){
        bits = stoul(numString,nullptr,0) << 4*(8 - (numString.size() -2));
    }else if(getType(numString) == type::BINARY){
        bits = stoul(numString,nullptr,0) >> (30 - numString.size());

    }
    cout << bits.to_string() << endl;
    this->signHex += bits.to_string().at(0);
    ss.clear();
    ss.str("");
    
    uint temp = stoul(bits.to_string().substr(1,8),nullptr,2);
    ss << uppercase << setbase(16);
    ss << temp;
    this->exponentHex += ss.str();
    cout << exponentHex << std::endl;
    ss.str("");
    ss.clear();

    temp = stoul(bits.to_string().substr(9,31),nullptr,2);
    ss << uppercase << setbase(16);
    ss << temp;
    this->mantissaHex += ss.str();

    double mant = 0.0;
    mant += (bits[0] == 1?1:0)/(pow(2,23));
    for(int i = 1; i < 23; i++){
        mant += (bits[0] == 1?1:0)/(pow(2,23-i));
    }

    
    this->decimalNumber = pow(-1,(bits[31] == 1)?1:0)*(1.0f + mant)*pow(2,stoul(bits.to_string().substr(1,8),nullptr,2)-127);
    bits = reverseBits(stoul(bits.to_string(),nullptr,2));
    this->isNormal = abs(this->decimalNumber) > std::numeric_limits<float>::min();
    this->isINF = abs(this->decimalNumber) > std::numeric_limits<float>::max();
    this->isNaN = bitset<32>(stoi(exponentHex,nullptr,16)).all() && bitset<32>(stoi(mantissaHex,nullptr,16)).any();
    this->hex = getHexFromBinary(bits);
}
SEMNumber::SEMNumber(double number){
    stringstream ss;
    this->decimalNumber = (float)number;
    this->isNormal = abs(number) >= std::numeric_limits<float>::min();
    this->isINF = abs(number) > std::numeric_limits<float>::max();

    union data{
        float_t f;
        uint32_t b;
    }binary;
    binary.f = number;
    bits = bitset<32>(reverseBits(binary.b));
    auto [s,e,m] = getSEMHexFromBinary(bits);
    this->signHex = s;
    this->exponentHex = e;
    this->mantissaHex = m;
    this->isNaN = bitset<32>(stoi(exponentHex,nullptr,16)).all() && bitset<32>(stoi(mantissaHex,nullptr,16)).any();
    this->hex = getHexFromBinary(bits);
}
   