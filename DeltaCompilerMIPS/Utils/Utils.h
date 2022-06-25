#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>

namespace Utils {
    void printBar();
    int lexemeToInt(const std::string &lexeme);
    bool lexemeToBoolean(const std::string &lexeme);
}

#endif // UTILS_H
