#ifndef ERRORS_H
#define ERRORS_H

#include "../Model/Type.h"
#include "../Model/Operation.h"
#include "../Gals/SemanticError.h"

class ConstMutationError : public SemanticError {
public:
    ConstMutationError(const std::string &identifier)
      : SemanticError("Trying to mutate const identifier '" + identifier + "'", -1) { }
};


class DuplicateIdentifierError : public SemanticError {
public:
    DuplicateIdentifierError(const std::string &identifier)
      : SemanticError("Identifier '" + identifier + "' already exists", -1) { }
};


class IdentifierIsNotAFunctionError : public SemanticError {
public:
    IdentifierIsNotAFunctionError(const std::string &identifier)
      : SemanticError("Identifier '" + identifier + "' cannot be called, because it is not a function", -1) { }
};


class IdentifierNotFoundError : public SemanticError {
public:
    IdentifierNotFoundError(const std::string &identifier)
      : SemanticError("Identifier '" + identifier + "' not found", -1) { }
};


class IncompatibleAssignmentTypesError : public SemanticError {
public:
    IncompatibleAssignmentTypesError(const std::string &identifier, const Type &expressionType, const Type &identifierType, const Operation &assignment)
      : SemanticError("Cannot attribute value of type '" + expressionType.toString() + "' to identifer '" + identifier + "' of type '" + identifierType.toString() + "' for assignment operator '" + assignment.lexeme + "'", -1) { }
};


class IncompatibleOperationTypesError : public SemanticError {
public:
    IncompatibleOperationTypesError(const Operation &op, const Type &type1, const Type &type2)
      : SemanticError("Incompatible types for '" + op.lexeme + "' operator: '" + type1.toString() + "' and '" + type2.toString() +  "'", -1) { }
};

class IncompatibleUnaryOperationTypeError : public SemanticError {
public:
    IncompatibleUnaryOperationTypeError(const std::string &op, const Type &type)
      : SemanticError("Incompatible type for '" + op + "' unary operator: '" + type.toString() + "'", -1) { }
};


class InvalidArrayIndexError : public SemanticError {
public:
    InvalidArrayIndexError(const std::string &arrayName, const Type &indexType)
      : SemanticError("Invalid index type for array '" + arrayName + "': '" + indexType.toString() + "', expected 'int'", -1) { }
};


class InvalidExpressionForBlockError : public SemanticError {
public:
    InvalidExpressionForBlockError(const Type &type, const std::string &blockName, const Type &expectedType)
      : SemanticError("Invalid expression type '" + type.toString() + "' for '" + blockName + "' block, expected '" + expectedType.toString() + "'", -1) { }
};


class InvalidFunctionParameterError : public SemanticError {
public:
    InvalidFunctionParameterError(const std::string &functionName, int paramPos, const Type &paramType, const Type &givenType)
      : SemanticError("Expected '" + paramType.toString() + "' for function '" + functionName + "' at parameter " + std::to_string(paramPos) + ", got '" + givenType.toString() + "'", -1) { }
};


class InvalidFunctionParameterQuantityError : public SemanticError {
public:
    InvalidFunctionParameterQuantityError(const std::string &functionName, int paramQnt, int givenParamQnt)
      : SemanticError("Expected " + std::to_string(paramQnt) + " parameters for function '" + functionName + "', got " + std::to_string(givenParamQnt), -1) { }
};


class InvalidFunctionReturnTypeError : public SemanticError {
public:
    InvalidFunctionReturnTypeError(const Type &returnType, const Type &givenReturnType)
      : SemanticError("Expected return of type '" + returnType.toString() + "', got '" + givenReturnType.toString() + "'", -1) { }
};


class MissingConstInitializationError : public SemanticError {
public:
    MissingConstInitializationError(const std::string &identifier)
      : SemanticError("Missing initialization for const identifier '" + identifier + "'", -1) { }
};


class MissingReturnStatementError : public SemanticError {
public:
    MissingReturnStatementError(const Type &type)
      : SemanticError("Missing return statement, expected '" + type.toString() + "' return") { }
};


class ReadingNonArrayAsArrayError : public SemanticError {
public:
    ReadingNonArrayAsArrayError(const std::string &identifier)
      : SemanticError("Reading non-array identifier '" + identifier + "' as array", -1) { }
};

#endif // ERRORS_H
