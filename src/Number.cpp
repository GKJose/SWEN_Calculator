#include <Number.h>
Number::Number(uint32_t n){
    this->data.binary = n;
}
Number::Number(float n){
    this->data.decimalNumber = n;
    
}
Number::Number(std::string number){
    int type = getType(number);
    std::cout << "type is:" << std::to_string(type) << std::endl;
    if(type == type::DECIMAL){
        this->data.decimalNumber = std::stof(number);    
    }else if(type == type::BINARY){
        this->data.binary = (uint32_t)std::stoul(number,nullptr,2);
    }else if(type == type::HEX){
        this->data.binary = (uint32_t)std::stoul(number,nullptr,16);
    }else if(type == type::SEM){
       bitset<32> bits(0);
       for(int i = 31; i >= 0; i--){
           if(number.size() < (32-i)) continue;
           else bits.set(i,(number.at(31-i) == '1'));
       }
       std::string bitstring = bits.to_string();
       std::cout << bitstring << std::endl;
       int sign = std::stoi(bitstring.substr(0,1),nullptr,2);
       int exponent = std::stoi(bitstring.substr(1,8),nullptr,2);
       float mantissa = 0.0f;
       for(int i = 9; i < bitstring.size(); i++){
           if(std::stoi(bitstring.substr(i,1)) == 1){
               mantissa += 1/(2*(i-8));
           }
       }
       this->data.decimalNumber = pow(-1,sign) * (1 + mantissa) * pow(2,(exponent-127));
       std::cout << this->data.decimalNumber << std::endl;
    }
}