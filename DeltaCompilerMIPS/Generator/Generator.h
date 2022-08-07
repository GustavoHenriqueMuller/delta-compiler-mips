#ifndef GENERATOR_H
#define GENERATOR_H

#include "../Model/Operation.h"
#include "../Model/Symbol.h"

#include <string>

class Generator {
public:
    Generator() {}
    std::string getCode();

    void addImmediate(const int &immediate);
    void addIdentifier(const Symbol &symbol);
    void addArrayIdentifier(const Symbol &symbol);
    void duplicateStackTop();
    void popStack();

    void addBinaryOperation(const OperationType &operationType);
    void addUnaryOperation(const OperationType &operationType);
    void addMutableUnaryOperation(const OperationType &operationType, const Symbol &symbol);
    void addMutableUnaryOperationOnArray(const OperationType &operationType, const Symbol &symbol);

    void addLabel(const std::string &label);
    void addJump(const std::string &label);
    void addBranchIfFalse(const std::string &label);
    void addBranchIfTrue(const std::string &label);

    void assignTo(const Symbol &symbol, const OperationType &assignmentType);
    void assignToArray(const Symbol &symbol, const OperationType &assignmentType);
    void addIdentifierDeclaration(const Symbol &symbol);
    void addArrayIdentifierDeclaration(const Symbol &symbol);
    void addPrint();
    void addInput();

private:
    std::string getInstructionNameFromOperation(const OperationType &operationType);
    std::string getFullIdentifier(const Symbol &symbol);
    void addToDataSection(const std::string &string);

    void addInstruction(const std::string &instruction);
    void addInstruction(const std::string &instruction, const std::string &p1);
    void addInstruction(const std::string &instruction, const std::string &p1, const std::string &p2, const std::string &p3);
    void addInstruction(const std::string &instruction, const std::string &p1, const std::string &p2, const int &p3);
    void addInstruction(const std::string &instruction, const std::string &p1, const std::string &p2);
    void addInstruction(const std::string &instruction, const std::string &p1, const int &p2);

    std::string dataSection;
    std::string textSection;
};

#endif
