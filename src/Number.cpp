#include <Number.h>

Number::Number(float n){
    this->data.decimalNumber = n;
    
}
Number::Number(std::string number){
    int type = getType(number);
    std::cout << "type is:" << std::to_string(type) << std::endl;
    if(type == type::DECIMAL){
        this->data.decimalNumber = std::stof(number);    
    }else if(type == type::BINARY){
        this->data.decimalNumber = std::stoi(number,nullptr,2);
    }else if(type == type::HEX){
        this->data.decimalNumber = std::stoi(number,nullptr,16);
    }else if(type == type::SEM){
       int sign = std::stoi(number.substr(0,1));
       int exponent = std::stoi(number.substr(1,8),nullptr,2);
       float mantissa = 0.0f;
       for(int i = 9; i < number.size(); i++){
           if(std::stoi(number.substr(i,1)) == 1){
               mantissa += 1/(i-7);
           }
       }
       this->data.decimalNumber = pow(-1,sign) * (1 + mantissa) * pow(2,(exponent-127));
    }
}