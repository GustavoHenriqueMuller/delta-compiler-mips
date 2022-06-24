#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Type.h"

#include <string>

class Expression {
public:
    Expression(Type type): type(type) {}

    Type type;
};

#endif // EXPRESSION_H
