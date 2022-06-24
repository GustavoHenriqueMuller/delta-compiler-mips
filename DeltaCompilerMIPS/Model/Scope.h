#ifndef SCOPE_H
#define SCOPE_H

#include "Symbol.h"

#include <vector>

class Scope {
public:
    Scope(int id): id(id) {}

    int id;
    std::vector<Symbol> symbolList;
    bool hasReturned = false;
    Type returnType = Type(PRIMITIVE_VOID);
};

#endif // SCOPE_H
