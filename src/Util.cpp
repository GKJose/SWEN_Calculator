//Util.cpp
//************************************************************
//*                                                          
//* Author: Mendez, Jose - Cyberbits01
//*`Purpose: To provide functions for misc. operations required
//*
//* Contains:                                        |UPDATE
//* parseInput ......................................|
//* getType .........................................|
//* getBinaryFromHex ................................|
//* getSEMHEXFromBinary .............................|
//* reverseBits .....................................|
//* 
//*
//* Date: 16Nov22
//************************************************************


#include <Util.h>
//************************************************************
//* parseInput
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: parseInput(equation)
//*     equation = The mathematical equation to be parsed
//*
//* Returns: tuple containing the vector of SEMNumber operands, the operator as a String, and lastly an error code.
//*
//* Functions called:                   Source:
//*   getType                               Util.cpp
//*   
//* Date: 16Nov22
//************************************************************
tuple<std::vector<SEMNumber>,std::string,int> parseInput(std::string equation){
    
    vector<SEMNumber> operands;
    vector<string> operators;
    string opt = "";
    int code  = 0;
    std::string equ = equation;

    //Regex splits equation into tokens, which are the numbers
    //First condition gets all hex number prefixed with 0x
    //Second condition get all binary numbers sufixed with b
    //Last condition get all decimal numbers in form x.x, x
    regex regexp("(\\[0x[0-9A-F]{1},0x[0-9A-F]{1,2},0x[0-9A-F]{1,23}\\])|(0x[0-9A-F]{1,8})|(0b[01]+)|(((-?[0|1-9]*\\.\\d+)|(-?\\d+(\\.\\d*)?)))");
    smatch m;
    while(regex_search(equation,m,regexp)){
        int base = getType(m.str());
        cout << m.str() << endl;
        if(base == type::BINARY || base == type::HEX){
            operands.push_back(SEMNumber(m.str()));
        }else if(base == type::DECIMAL){
            //Patch for now, if equ is 2-2, then the two numbers parsed are
            // 2 and -2, so the resulting equation is actually 2+2
            //To fix this, we will take the abs of the second number.
            double parsedNum = stod(m.str());
            if(operands.size() == 1) parsedNum = abs(parsedNum);
            operands.push_back(SEMNumber(parsedNum));
        }else{
            string SEH = m.str();
            string delimiter = ",";
            vector<string> tokens;
            size_t pos = 0;
            SEH.erase(0,1);
            SEH.erase(SEH.size() - 1,SEH.size());
            while((pos=SEH.find(delimiter)) != std::string::npos){
                tokens.push_back(SEH.substr(0,pos));
                SEH.erase(0,pos+delimiter.length());
            }
            tokens.push_back(SEH);
            operands.push_back(SEMNumber(tokens.at(0),tokens.at(1),tokens.at(2)));
            
        }
        equation = m.suffix();

    }
    if(operands.size() == 2){
        regexp = "[*+-]";
        while(regex_search(equ,m,regexp)){
            operators.push_back(m.str());
            equ = m.suffix();
        }
    }
    if(operators.size() > 1){
        code = -2;
    }else if(operators.size() >= operands.size()){
        code = -1;
    }
    // If only one valid input and no operators, then we want to return code 1, to 
    // indicte that we want information on that input.
    else if(operands.size() == 1){
        code = 1;
    }
    //If two operands, one operator, then sovle the equation.
    else if(operands.size() == 2 && operators.size() == 1){
        code = 2;
        opt = operators.at(0);
    }
    return tuple(operands,opt,code);
}
//************************************************************
//* getType
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: getType(number)
//*     number = The number as a string
//*
//* Returns: A uint8_t number representing the base of the number
//*
//* Functions called:                   Source:
//*     
//* Date: 16Nov22
//************************************************************
uint8_t getType(std::string number){

    if(number.find("b") == 1 ){
        return type::BINARY;
    }else if(number.find("x") == 1){
        return type::HEX;
    }else if(number.find("[") == 0){
        return type::SEM;
    }else{
        return type::DECIMAL;
    }
}
//************************************************************
//* getBinaryFromHex
//*
//* Author: Smith, Michael - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: getBinaryFromHex(hexString)
//*     hexString = The hexadecimal string to be parsed into a bitset.
//*
//* Returns: 
//*
//* Functions called:                   Source:
//*     
//* Date: 16Nov22
//************************************************************
bitset<32> getBinaryFromHex(string hexString){
    bitset<32> bits;
    int byteOffset = 0;
    for(int i = hexString.size() - 1; i > 2; i--){
        bits |= bitset<32>(stoul(hexString.substr(i,1),nullptr,16)) << (4*byteOffset++) ;
    }
    return bits;

}
//************************************************************
//* getHexFromBinary
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: getHexFromBinary(bits)
//*     bits = The bitset to be converted.
//*
//* Returns: 
//*
//* Functions called:                   Source:
//*   reverseBits                         Util.cpp
//* Date: 16Nov22
//************************************************************
std::string getHexFromBinary(bitset<32> bits){
    stringstream ss;
    ss << "0x" << setbase(16) << uppercase;
    bits = reverseBits(stoul(bits.to_string(),nullptr,2));
    for(int i = 0; i <= 31; i+= 4){
       ss << stoul(bits.to_string().substr(i,4),nullptr,2);
       
    }
    return ss.str();
}
//************************************************************
//* getSEMHEXFromBinary
//*
//* Author: Smith, Michael - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: getSEMHEXFromBinary(bits)
//*     bits = The bitset to be converted.
//*
//* Returns: 
//*
//* Functions called:                   Source:
//*   reverseBits                          Util.cpp
//* Date: 16Nov22
//************************************************************
tuple<std::string,std::string,std::string> getSEMHexFromBinary(bitset<32> bits){
    std::string sign,exponent,mantissa;
    stringstream ss;

    ss << "0x" << uppercase << setbase(16);
    ss << stoi(bits.to_string().substr(31,1),nullptr,2);
    sign = ss.str();

    ss.str("");
    ss << "0x" << reverseBits(stoi(bits.to_string().substr(23,8),nullptr,2));
    exponent = ss.str().substr(0,4);

    ss.str("");
    ss << "0x" << reverseBits(stoi(bits.to_string().substr(0,23),nullptr,2));
    mantissa = ss.str().substr(0,8);

    return tuple(sign,exponent,mantissa);

}
//************************************************************
//* reverseBits
//*
//* Author: Smith, Michael - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: reverseBits(n)
//*     n = The uint32_t number to be reversed.
//*
//* Returns: 
//*
//* Functions called:                   Source:
//*     
//* Date: 16Nov22
//************************************************************
uint32_t reverseBits(uint32_t n){
    uint32_t ans = 0;
    for(int i = 31; i >= 0; i--){
        ans |= (n & 1) << i;
        n >>= 1;
    }
    return ans;
}
//************************************************************
//* lv_event_send_recursively
//*
//* Author: Mendez,Jose - Cyberbits01
//* 
//* Purpose: 
//*
//* Usage: lv_event_send_recursively(obj,e,data)
//*     obj =  The lv_obj parent.
//*     e   =  The lv_event to be pased to the children of obj.
//*     data = The user data to be passed to the children of obj.
//*
//* Returns: 
//*
//* Functions called:                   Source:
//*     lv_event_send                       lvgl.a
//*     lv_obj_get_child_cnt                lvgl.a
//* Date: 16Nov22
//************************************************************
void lv_event_send_recursive(lv_obj_t* obj,lv_event_code_t e,void* data){
    lv_event_send(obj,e,data);
    cout << data << endl;
    uint32_t childCnt = lv_obj_get_child_cnt(obj);
    if(childCnt == 0) return;
    for(int idx = 0; idx < childCnt;idx++){
        lv_event_send_recursive(lv_obj_get_child(obj,idx),e,data);
    }
}