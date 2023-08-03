#include <math.h>
#include <sstream>

#include "Instruction.h"
#include "FunctionType.h"
#include "Functions.h"
#include "InstructionVM.h"

Instruction::Instruction(int operation, Operand operand) :operation(operation), operand(operand) {
}

Operand::Operand(int type, double value) :type(type), value(value) {
}

Operand::Operand(int type, std::string name) :type(type), name(name) {
}

Operand::Operand(int type, char operatorSymbol) :type(type), operatorSymbol(operatorSymbol) {
}

double Operand::getValue(InstructionVM* vm) const {
    if(type == Operand::TYPE_VARIABLE) {
        return vm->getVar(name);
    }
    return value;
}

std::string Operand::getName() const {
    return name;
}

char Operand::getOperatorSymbol() const {
    return operatorSymbol;
}

std::string Operand::toString() const {
    std::ostringstream str;

    switch(type) {
        case Operand::TYPE_NUMBER:
            str << value;
            break;
        case Operand::TYPE_VARIABLE:
            str << name;
            break;
        case Operand::TYPE_FUNCTION:
            str << name;
            break;
        case Operand::TYPE_OPERATOR:
            str << operatorSymbol;
            break;
    }

    return str.str();
}

std::string Instruction::toString() const {
    std::string str = "";

    switch(operation) {
        case Instruction::OP_PUSH:
            str += "PUSH ";
            break;
        case Instruction::OP_OPERATOR:
            str += "OPERATOR ";
            break;
        case Instruction::OP_CALL:
            str += "CALL ";
            break;
    }

    return str + operand.toString();
}

void Instruction::executeOperator(std::stack<Operand>& stack, InstructionVM* vm) {
    auto rParam = stack.top();
    stack.pop();
    auto lParam = stack.top();
    stack.pop();

    double a = lParam.getValue(vm);
    double b = rParam.getValue(vm);

    switch(operand.getOperatorSymbol()) {
        case '+':
            stack.push(Operand(Operand::TYPE_NUMBER, a + b));
            break;
        case '-':
            stack.push(Operand(Operand::TYPE_NUMBER, a - b));
            break;
        case '*':
            stack.push(Operand(Operand::TYPE_NUMBER, a * b));
            break;
        case '/':
            stack.push(Operand(Operand::TYPE_NUMBER, a / b));
            break;
        case '^':
            stack.push(Operand(Operand::TYPE_NUMBER, pow(a, b)));
            break;
        case '%':
            stack.push(Operand(Operand::TYPE_NUMBER, fmod(a, b)));
            break;
        case '=':
            vm->setVar(lParam.getName(), b);
            stack.push(Operand(Operand::TYPE_NUMBER, (double)(b)));
            break;
    }
}

void Instruction::executeFunctionCall(std::stack<Operand>& stack, InstructionVM* vm) {
    auto func = Functions::get(operand.getName());
    ParameterList_t params;
    for(int i = 0; i < func.second; i++) {
        params.push_back(stack.top().getValue(vm));
        stack.pop();
    }
    stack.push(Operand(Operand::TYPE_NUMBER,func.first(params)));
}

void Instruction::execute(std::stack<Operand>& stack, InstructionVM* vm) {
    switch(operation) {
        case Instruction::OP_PUSH:
            stack.push(operand);
            break;
        case Instruction::OP_OPERATOR:
            executeOperator(stack, vm);
            break;
        case Instruction::OP_CALL:
            executeFunctionCall(stack, vm);
            break;
    }
}