#include <math.h>
#include "Instruction.h"
#include "FunctionType.h"
#include "Functions.h"

Instruction::Instruction(int operation, Operand operand) :operation(operation), operand(operand) {
}

Operand::Operand(int type, double value) :type(type), value(value) {
}

Operand::Operand(int type, std::string name) :type(type), name(name) {
}

Operand::Operand(int type, char operatorSymbol) :type(type), operatorSymbol(operatorSymbol) {
}

double Operand::getValue() const {
    return value;
}

std::string Operand::getName() const {
    return name;
}

char Operand::getOperatorSymbol() const {
    return operatorSymbol;
}

std::string Operand::toString() const {
    std::string str = "";

    switch(type) {
        case Operand::TYPE_NUMBER:
            str += std::to_string(value);
            break;
        case Operand::TYPE_VARIABLE:
            str += name;
            break;
        case Operand::TYPE_FUNCTION:
            str += name;
            break;
        case Operand::TYPE_OPERATOR:
            str += operatorSymbol;
            break;
    }

    return str;
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

void Instruction::executeOperator(std::stack<double>& stack) {
    double b = stack.top();
    stack.pop();
    double a = stack.top();
    stack.pop();
    switch(operand.getOperatorSymbol()) {
        case '+':
            stack.push(a + b);
            break;
        case '-':
            stack.push(a - b);
            break;
        case '*':
            stack.push(a * b);
            break;
        case '/':
            stack.push(a / b);
            break;
        case '^':
            stack.push(pow(a, b));
            break;
    }
}

void Instruction::executeFunctionCall(std::stack<double>& stack) {
    auto func = Functions::get(operand.getName());
    ParameterList_t params;
    for(int i = 0; i < func.second; i++) {
        params.push_back(stack.top());
        stack.pop();
    }
    stack.push(func.first(params));
}

void Instruction::execute(std::stack<double>& stack) {
    switch(operation) {
        case Instruction::OP_PUSH:
            stack.push(operand.getValue());
            break;
        case Instruction::OP_OPERATOR:
            executeOperator(stack);
            break;
        case Instruction::OP_CALL:
            executeFunctionCall(stack);
            break;
    }
}