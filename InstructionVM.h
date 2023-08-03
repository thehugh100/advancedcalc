#pragma once
#include <vector>
#include <stack>
#include <map>

class Instruction;
class Operand;
class InstructionVM {
    public:
    InstructionVM();
    ~InstructionVM();
    
    void execute(std::vector<Instruction>& instructions);
    std::stack<Operand>* getStack();

    void setVar(std::string name, double value);
    double getVar(std::string name);

    double getResult();

    void reset();

    private:
    std::map<std::string, double> variables;
    std::stack<Operand>* stack;
};