#include <Util.h>
std::string solveEquation(std::string equation)
{
    //Solve the equation provided
    //Use regex to pull operators/operands
    std::string output = "";
    Number solution(0.0);
    std::string equ = equation;
    regex regexp("[0-9A-F.]+");
    smatch m;
    regex_search(equation,m,regexp);
    
    std::vector<Number> operands;
    while(regex_search(equation,m,regexp)){
        operands.push_back(Number(m[0].str()));
        equation = m.suffix();
    }
    regexp = "[\\/,*,-,+]";
    
    while(regex_search(equ,m,regexp)){
        std::string opt = m[0].str();
        if(opt.compare("/") == 0){
            if(operands[1].data.decimalNumber == 0.0f){
                return "ERROR: NaN";
            }else{
                solution = (operands[0] / operands[1]);
            }
        }else if(opt.compare("*") == 0){
            solution =  (operands[0] * operands[1]);
        }else if(opt.compare("-") == 0){
            solution = (operands[0] - operands[1]);
        }else if(opt.compare("+") == 0){
            solution = (operands[0] + operands[1]);
        }
        equ = m.suffix();
    }

    return "=" + solution.to_string();
    
}
bool isValidEquation(std::string equation){
    std::cout << "Checking equation!" << std::endl;
    std::string equ = equation;
    int8_t operandCount = 0;
    int8_t operatorCount = 0;
    //Regex splits equation into tokens, which are the numbers
    regex regexp("[A-F0-9.]+");
    smatch m;
    while(regex_search(equation,m,regexp)){
        operandCount++;
        equation = m.suffix();

    }
    regexp = "[\\/,*,-,+]+";
    while(regex_search(equ,m,regexp)){
        operatorCount++;
        equ = m.suffix();
    }
    return operatorCount == 1 && operandCount == 2;
}
uint8_t getType(std::string number){
    std::string temp = number;
    std::cout << "Getting type" << std::endl;
    regex regexp("[0-1]+");
    smatch m;
    int count = 0;
    while(regex_search(number,m,regexp)){
        count++;
        number = m.suffix();
    }
    if(count == 1){
        if(mode == "Binary"){
            return type::BINARY;
        }else if(mode == "Signed Exp. Man."){
            return type::SEM;
        }
    }
    number = temp;
    regexp = "[A-F0-9]+";
    while(regex_search(number,m,regexp)){
        count++;
        number = m.suffix();
    }
    if(count == 1) return type::HEX;
    count = 0;
    number = temp;
    regexp = "[0-9.]+";

    while(regex_search(number,m,regexp)){
        count++;
        number = m.suffix();
    }
    if(count == 1) return type::DECIMAL;
    count = 0;

    
    return type::INVALID;
}
