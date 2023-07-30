#pragma once
#include <vector>
#include <stack>

class Instruction;

class InstructionVM {
    public:
    InstructionVM();
    void execute(std::vector<Instruction>& instructions);
    std::stack<double>* getStack();

    private:
    std::stack<double> stack;
};