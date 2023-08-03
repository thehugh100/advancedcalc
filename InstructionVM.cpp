#include "InstructionVM.h"
#include "Instruction.h"

InstructionVM::InstructionVM() {
    stack = new std::stack<Operand>();
}

InstructionVM::~InstructionVM() {
    delete stack;
}

void InstructionVM::reset() {
    variables.clear();
    stack->empty();
    setVar("x", 0.);
}

void InstructionVM::setVar(std::string name, double value) {
    variables[name] = value;
}

double InstructionVM::getVar(std::string name) {
    //TODO: is this wanted behaviour?
    return variables[name]; //Note this will create any variable that doesn't exist with a value of 0
}

double InstructionVM::getResult() {
    return stack->top().getValue(this);
}

void InstructionVM::execute(std::vector<Instruction>& instructions) {
    for(auto &i: instructions) {
        i.execute(*stack, this);
    }
}

std::stack<Operand>* InstructionVM::getStack() {
    return stack;
}