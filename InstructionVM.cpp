#include "InstructionVM.h"
#include "Instruction.h"

InstructionVM::InstructionVM() {
}

void InstructionVM::execute(std::vector<Instruction>& instructions) {
    stack.empty();
    for(auto &i: instructions) {
        i.execute(stack);
    }
}

std::stack<double>* InstructionVM::getStack() {
    return &stack;
}