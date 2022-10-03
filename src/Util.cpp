#include <Util.h>
extern std::string mode;
string binaryCharacters = "01";
set<char> binarySet(binaryCharacters.begin(),binaryCharacters.end());

string decimalCharacters = "0123456789";
set<char> decimalSet(decimalCharacters.begin(),decimalCharacters.end());

string hexadecimalCharacters = "0123456789ABCDEF";
set<char> hexadecimalSet(hexadecimalCharacters.begin(),hexadecimalCharacters.end());

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
int isValidEquation(std::string equation){
    set<int> bases;
    std::cout << "Checking equation!" << std::endl;
    std::string equ = equation;
    int8_t operandCount = 0;
    int8_t operatorCount = 0;
    //Regex splits equation into tokens, which are the numbers
    regex regexp("[A-F0-9.]+");
    smatch m;
    while(regex_search(equation,m,regexp)){
        //Check to see that the input is in correct base
        std::cout << m.str() << std::endl;
        int base = getType(m.str());
        std::cout << base << std::endl;
        bases.insert(base);
        operandCount++;
        equation = m.suffix();

    }
    regexp = "[\\/,*,-,+]";
    while(regex_search(equ,m,regexp)){
        operatorCount++;
        equ = m.suffix();
    }
    
    if(operatorCount > 1){
        return 0;
    }else if(operandCount > 2){
        return -1;
    }else if(bases.size() > 1){
        return -2;
    }
    return 1;
}
uint8_t getType(std::string number){
    //Makes a set of all the characters in number
    // Each entry in numSet is unique

    set<char> numSet(number.begin(),number.end());
    vector<char> differenceSet;
    set_difference(hexadecimalCharacters.begin(),hexadecimalCharacters.end(),decimalSet.begin(),decimalSet.end(),back_inserter(differenceSet));

    //sort(numSet.begin(),numSet.end());

    //Checking to see if it is binary
        //Sort differenceSet
   
    //Check to see if the difference set contains decimal
    if(mode == "Decimal" && includes(decimalSet.begin(),decimalSet.end(),numSet.begin(),numSet.end())){
        return type::DECIMAL;
    }else if(mode == "Hexadecimal" && includes(hexadecimalSet.begin(),hexadecimalSet.end(),numSet.begin(),numSet.end())){
        return type::HEX;

    }else if(includes(binarySet.begin(),binarySet.end(),numSet.begin(),numSet.end())){
        if(mode == "Binary"){
            return type::BINARY;
        }else if(mode == "Signed Exp. Man."){
            return type::SEM;
        }
    }
    
        return type::INVALID;
}
