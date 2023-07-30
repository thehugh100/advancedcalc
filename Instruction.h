#pragma once
#include <string>
#include <stack>

class Operand {
    public:
    Operand(int type, double value);
    Operand(int type, std::string name);
    Operand(int type, char operatorSymbol);
    std::string toString() const;

    enum Type {
        TYPE_NUMBER = 0,
        TYPE_VARIABLE,
        TYPE_FUNCTION,
        TYPE_OPERATOR
    };

    double getValue() const;
    std::string getName() const;
    char getOperatorSymbol() const;

    private:
    int type;
    double value;
    std::string name;
    char operatorSymbol;
};

class Instruction {
    public:
    Instruction(int operation, Operand operand);
    void execute(std::stack<double>& stack);
    void executeFunctionCall(std::stack<double>& stack);
    void executeOperator(std::stack<double>& stack);

    std::string toString() const;

    enum Operation {
        OP_PUSH = 0,
        OP_OPERATOR,
        OP_CALL
    };

    private:
    int operation;
    Operand operand;
};