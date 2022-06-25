#ifndef PARAMETER_H
#define PARAMETER_H

#include "Type.h"

#include <string>

class Parameter {
public:
    Type type;
    std::string name;

    Parameter(Type type, std::string name): type(type), name(name) {}
};

#endif // PARAMETER_H
