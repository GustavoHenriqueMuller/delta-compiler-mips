#include "Generator.h"

#include <fstream>

std::string Generator::getCode() {
    std::string result;

    result += ".data\n";
    result += dataSection;
    result += "\n";
    result += ".text\n";
    result += textSection;
    result += "\tli $v0, 10\n";
    result += "\tsyscall\n";

    return result;
}

void Generator::addImmediate(const int &immediate) {
    addInstruction("subi", "$sp", "$sp", 4);
    addInstruction("addi", "$t0", "$zero", immediate);
    addInstruction("sw", "$t0", "0($sp)");
}

void Generator::addIdentifier(const Symbol &symbol) {
    addInstruction("subi", "$sp", "$sp", 4);
    addInstruction("lw", "$t0", getFullIdentifier(symbol));
    addInstruction("sw", "$t0", "0($sp)");
}

void Generator::addArrayIdentifier(const Symbol &symbol) {
    //addInstruction("LD", stackTop());
    //addInstruction("STO", "$indr");
    //addInstruction("LDV", getFullIdentifier(symbol));
    //addInstruction("STO", stackTop());
}

void Generator::duplicateStackTop() {
    addInstruction("lw", "$t0", "0($sp)");
    addInstruction("subi", "$sp", "$sp", 4);
    addInstruction("sw", "$t0", "0($sp)");
}

void Generator::popStack() { // TODO: Cuidar de tamanhos diferentes!
    addInstruction("addi", "$sp", "$sp", 4);
}

// TODO: Criar função pra dar push na stack arbitrariamente

void Generator::addBinaryOperation(const OperationType &operationType) {
    switch (getOperationCategory(operationType)) {
        case CATEGORY_ARIT_HIGH:
        case CATEGORY_ARIT_LOW:
        case CATEGORY_BIT: {
            std::string operationInstructionName = getInstructionNameFromOperation(operationType);

            addInstruction("lw", "$t0", "4($sp)");
            addInstruction("lw", "$t1", "0($sp)");
            addInstruction(operationInstructionName, "$t2", "$t0", "$t1");

            addInstruction("addi", "$sp", "$sp", 8);
            addInstruction("subi", "$sp", "$sp", 4);
            addInstruction("sw", "$t2", "0($sp)");
            break;
        }

        case CATEGORY_RELATIONAL: {
            if (operationType == OP_OR || operationType == OP_AND) {
                std::string operationInstructionName = getInstructionNameFromOperation(operationType);

                addInstruction("lw", "$t0", "4($sp)");
                addInstruction("xori", "$t0", "$t0", 1);

                addInstruction("lw", "$t1", "0($sp)");
                addInstruction("xori", "$t1", "$t1", 1);
                addInstruction(operationInstructionName, "$t2", "$t0", "$t1");

                addInstruction("addi", "$sp", "$sp", 8);
                addInstruction("subi", "$sp", "$sp", 4);
                addInstruction("sw", "$t2", "0($sp)");
            } else {
                addInstruction("lw", "$t0", "4($sp)");
                addInstruction("lw", "$t1", "0($sp)");
                addInstruction("sub", "$t2", "$t0", "$t1");

                addInstruction("addi", "$sp", "$sp", 8);
                addInstruction("subi", "$sp", "$sp", 4);

                switch (operationType) {
                    case OP_GREATER:
                        addInstruction("sgt", "$t0", "$t2", "$zero");
                        addInstruction("sw", "$t0", "0($sp)");
                        break;
                    case OP_SMALLER:
                        addInstruction("slt", "$t0", "$t2", "$zero");
                        addInstruction("sw", "$t0", "0($sp)");
                        break;
                    case OP_GREATER_EQ:
                        addInstruction("sge", "$t0", "$t2", "$zero");
                        addInstruction("sw", "$t0", "0($sp)");
                        break;
                    case OP_SMALLER_EQ:
                        addInstruction("sle", "$t0", "$t2", "$zero");
                        addInstruction("sw", "$t0", "0($sp)");
                        break;
                    case OP_EQUAL:
                        addInstruction("seq", "$t0", "$t2", "$zero");
                        addInstruction("sw", "$t0", "0($sp)");
                        break;
                    case OP_DIFFERENT:
                        addInstruction("sne", "$t0", "$t2", "$zero");
                        addInstruction("sw", "$t0", "0($sp)");
                        break;
                    }
            }
            break;
        }
    }
}

void Generator::addUnaryOperation(const OperationType &operationType) {
    switch (operationType) {
        case OP_MINUS_INVERSION:
            addInstruction("lw", "$t0", "0($sp)");
            addInstruction("mul", "$t0", "$t0", "-1");
            addInstruction("sw", "$t0", "0($sp)");
            break;
        case OP_BIT_NOT:
            addInstruction("lw", "$t0", "0($sp)");
            addInstruction("not", "$t0", "$t0");
            addInstruction("sw", "$t0", "0($sp)");
            break;
        case OP_NOT:
            addInstruction("lw", "$t0", "0($sp)");
            addInstruction("seq", "$t0", "$zero");
            addInstruction("sw", "$t0", "0($sp)");
            break;
    }
}

void Generator::addMutableUnaryOperation(const OperationType &operationType, const Symbol &symbol) {
    switch (operationType) {
        case OP_INCREMENT_RIGHT:
            addInstruction("lw", "$t0", getFullIdentifier(symbol));
            addInstruction("subi", "$sp", "$sp", 4);
            addInstruction("sw", "$t0", "0($sp)");

            addInstruction("addi", "$t0", "$t0", 1);
            addInstruction("sw", "$t0", getFullIdentifier(symbol));
            break;
        case OP_DECREMENT_RIGHT:
            addInstruction("lw", "$t0", getFullIdentifier(symbol));
            addInstruction("subi", "$sp", "$sp", 4);
            addInstruction("sw", "$t0", "0($sp)");

            addInstruction("subi", "$t0", "$t0", 1);
            addInstruction("sw", "$t0", getFullIdentifier(symbol));
            break;
        case OP_INCREMENT_LEFT:
            addInstruction("lw", "$t0", getFullIdentifier(symbol));
            addInstruction("addi", "$t0", "$t0", 1);
            addInstruction("sw", "$t0", getFullIdentifier(symbol));

            addInstruction("subi", "$sp", "$sp", 4);
            addInstruction("sw", "$t0", "0($sp)");
            break;
        case OP_DECREMENT_LEFT:
            addInstruction("lw", "$t0", getFullIdentifier(symbol));
            addInstruction("subi", "$t0", "$t0", 1);
            addInstruction("sw", "$t0", getFullIdentifier(symbol));

            addInstruction("subi", "$sp", "$sp", 4);
            addInstruction("sw", "$t0", "0($sp)");
            break;
    }
}

void Generator::addMutableUnaryOperationOnArray(const OperationType &operationType, const Symbol &symbol) {
    /*addInstruction("LD", stackTop());
    addInstruction("STO", "$indr");

    switch (operationType) {
        case OP_INCREMENT_RIGHT:
            addInstruction("LDV", getFullIdentifier(symbol));
            addInstruction("STO", stackTop());
            addInstruction("ADDI", 1);
            addInstruction("STOV", getFullIdentifier(symbol));
            break;
        case OP_DECREMENT_RIGHT:
            addInstruction("LDV", getFullIdentifier(symbol));
            addInstruction("STO", stackTop());
            addInstruction("SUBI", 1);
            addInstruction("STOV", getFullIdentifier(symbol));
            break;
        case OP_INCREMENT_LEFT:
            addInstruction("LDV", getFullIdentifier(symbol));
            addInstruction("ADDI", 1);
            addInstruction("STO", stackTop());
            addInstruction("STOV", getFullIdentifier(symbol));
            break;
        case OP_DECREMENT_LEFT:
            addInstruction("LDV", getFullIdentifier(symbol));
            addInstruction("SUBI", 1);
            addInstruction("STO", stackTop());
            addInstruction("STOV", getFullIdentifier(symbol));
            break;
    }*/
}

void Generator::addLabel(const std::string &label) {
    textSection += label + ":\n";
}

void Generator::addJump(const std::string &label) {
    addInstruction("j", label);
}

void Generator::addBranchIfFalse(const std::string &label) {
    addInstruction("lw", "$t0", "0($sp)");
    addInstruction("beq", "$t0", "$zero", label);
    addInstruction("addi", "$sp", "$sp", 4);
}

void Generator::addBranchIfTrue(const std::string &label) {
    addInstruction("lw", "$t0", "0($sp)");
    addInstruction("bne", "$t0", "$zero", label);
    addInstruction("addi", "$sp", "$sp", 4);
}

void Generator::assignTo(const Symbol &symbol, const OperationType &assignmentOperation) {
    if (assignmentOperation != OP_ASSIGNMENT) {
        duplicateStackTop();
        addInstruction("lw", "$t0", getFullIdentifier(symbol));
        addInstruction("sw", "$t0", "4($sp)");

        addBinaryOperation(getBinaryOperationFromAssignmentType(assignmentOperation).type);
    }

    addInstruction("lw", "$t0", "0($sp)");
    addInstruction("sw", "$t0", getFullIdentifier(symbol));
    addInstruction("addi", "$sp", "$sp", 4);
}

void Generator::assignToArray(const Symbol &symbol, const OperationType &assignmentOperation) {
    /*if (assignmentOperation != OP_ASSIGNMENT) {
        addInstruction("LD", stackTop());
        stackSize += 1;
        addInstruction("STO", stackTop());

        addInstruction("LD ", stackTop() - 2);
        addInstruction("STO", "$indr");
        addInstruction("LDV", getFullIdentifier(symbol));
        addInstruction("STO", stackTop() - 1);

        addBinaryOperation(getBinaryOperationFromAssignmentType(assignmentOperation).type);
    }

    addInstruction("LD", stackTop() - 1);
    addInstruction("STO", "$indr");

    addInstruction("LD", stackTop());
    addInstruction("STOV", getFullIdentifier(symbol));
    stackSize -= 2;*/
}

void Generator::addIdentifierDeclaration(const Symbol &symbol) {
    addToDataSection(getFullIdentifier(symbol) + ": .word 0");
}

void Generator::addArrayIdentifierDeclaration(const Symbol &symbol) {
    std::string value;

    for (int i = 0; i < symbol.type.arraySize; i++) {
        value += "0";

        if (i < symbol.type.arraySize - 1) {
            value += ", ";
        }
    }

    addToDataSection(getFullIdentifier(symbol) + ": .word " + value);
}

void Generator::addPrint() {
    addInstruction("li", "$v0", 1); // TODO: Mudar dependendo se o topo é caractere ou inteiro
    addInstruction("lw", "$a0", "0($sp)");
    addInstruction("syscall");
    addInstruction("addi", "$sp", "$sp", 4);

    addInstruction("li", "$v0", 11);
    addInstruction("li", "$a0", 10);
    addInstruction("syscall");
}

void Generator::addInput() {
    addInstruction("li", "$v0", 5); // TODO: Criar funções de input para outros tipos
    addInstruction("syscall");
    addInstruction("sw", "$v0", "0($sp)");
}

std::string Generator::getInstructionNameFromOperation(const OperationType &operationType) {
    switch (operationType) {
        case OP_ADDITION:
            return "add";
        case OP_SUBTRACTION:
            return "sub";
        case OP_MULTIPLICATION:
            return "mul";
        case OP_DIVISION:
            break;
        case OP_MOD:
            break;
        case OP_OR:
        case OP_BIT_OR:
            return "or";
        case OP_BIT_XOR:
            return "xor";
        case OP_AND:
        case OP_BIT_AND:
            return "and";
        case OP_BIT_LS:
            return "sll";
        case OP_BIT_RS:
            return "srl";
    }
}

std::string Generator::getFullIdentifier(const Symbol &symbol) {
    return symbol.name + "_" + std::to_string(symbol.scopeId);
}

void Generator::addToDataSection(const std::string &string) {
    dataSection += "\t" + string + "\n";
}

void Generator::addInstruction(const std::string &instruction) {
    textSection += "\t" + instruction + "\n";
}

void Generator::addInstruction(const std::string &instruction, const std::string &p1) {
    textSection += "\t" + instruction + " " + p1 + "\n";
}

void Generator::addInstruction(const std::string &instruction, const std::string &p1, const std::string &p2, const std::string &p3) {
    textSection += "\t" + instruction + " " + p1 + ", " + p2 + ", " + p3 + "\n";
}

void Generator::addInstruction(const std::string &instruction, const std::string &p1, const std::string &p2, const int &p3) {
    textSection += "\t" + instruction + " " + p1 + ", " + p2 + ", " + std::to_string(p3) + "\n";
}

void Generator::addInstruction(const std::string &instruction, const std::string &p1, const std::string &p2) {
    textSection += "\t" + instruction + " " + p1 + ", " + p2 + "\n";
}

void Generator::addInstruction(const std::string &instruction, const std::string &p1, const int &p2) {
    textSection += "\t" + instruction + " " + p1 + ", " + std::to_string(p2) + "\n";
}

