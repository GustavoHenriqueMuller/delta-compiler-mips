#ifndef OPERATION_H
#define OPERATION_H

#include "Type.h"
#include "../Gals/Constants.h"

#include <string>

enum OperationType {
    // Arithmetic
    OP_ADDITION,
    OP_SUBTRACTION,
    OP_MULTIPLICATION,
    OP_DIVISION,
    OP_MOD,

    // Relational
    OP_OR,
    OP_AND,
    OP_GREATER,
    OP_SMALLER,
    OP_GREATER_EQ,
    OP_SMALLER_EQ,
    OP_EQUAL,
    OP_DIFFERENT,

    // Bit
    OP_BIT_OR,
    OP_BIT_XOR,
    OP_BIT_AND,
    OP_BIT_LS,
    OP_BIT_RS,

    // Unary right
    OP_INCREMENT_RIGHT,
    OP_DECREMENT_RIGHT,

    // Unary left
    OP_MINUS_INVERSION,
    OP_BIT_NOT,
    OP_NOT,
    OP_INCREMENT_LEFT,
    OP_DECREMENT_LEFT,

    // Attribution
    OP_ASSIGNMENT,
    OP_INCREMENT_ASSIGNMENT,
    OP_DECREMENT_ASSIGNMENT,
    OP_MULTIPLICATION_ASSIGNMENT,
    OP_DIVISION_ASSIGNMENT,
    OP_MOD_ASSIGNMENT,
    OP_BIT_OR_ASSIGNMENT,
    OP_BIT_XOR_ASSIGNMENT,
    OP_BIT_AND_ASSIGNMENT,
    OP_BIT_LS_ASSIGNMENT,
    OP_BIT_RS_ASSIGNMENT
};

enum OperationCategory {
    CATEGORY_ARIT_LOW,
    CATEGORY_ARIT_HIGH,
    CATEGORY_RELATIONAL,
    CATEGORY_BIT,
    CATEGORY_UNARY_RIGHT_MUTABLE,
    CATEGORY_UNARY_LEFT,
    CATEGORY_UNARY_LEFT_MUTABLE,
    CATEGORY_ASSIGNMENT
};

class Operation {
public:
    Operation() {}
    Operation(OperationType type, std::string lexeme): type(type), lexeme(lexeme) {}

    OperationType type;
    std::string lexeme;
};

OperationType getOperationTypeFromTokenId(const TokenId &tokenId);
OperationType getRightUnaryOperationTypeFromTokenId(const TokenId &tokenId);
OperationType getLeftUnaryOperationTypeFromTokenId(const TokenId &tokenId);
OperationType getAssignmentOperationTypeFromTokenId(const TokenId &tokenId);
Operation getBinaryOperationFromAssignmentType(const OperationType &attributionType);
OperationCategory getOperationCategory(const OperationType &operationType);

#endif // OPERATION_H
