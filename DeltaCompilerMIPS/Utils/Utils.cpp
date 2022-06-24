#include "Utils.h"

void Utils::printBar() {
    std::cout << std::string(40, '_') << std::endl << std::endl;
}

int Utils::lexemeToInt(const std::string &lexeme) {
    if (lexeme.rfind("0x", 0) == 0) {
        return std::stoi(lexeme.substr(2, lexeme.size()), nullptr, 16);
    } else if (lexeme.rfind("0b") == 0) {
        return std::stoi(lexeme.substr(2, lexeme.size()), nullptr, 2);
    } else {
        return std::stoi(lexeme);
    }
}

bool Utils::lexemeToBoolean(const std::string &lexeme) {
    return lexeme == "true";
}
