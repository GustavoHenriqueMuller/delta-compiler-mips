#include "ConsoleParser.h"

#include <string>
#include <stdexcept>

void ConsoleParser::parse(int argc, char** argv) {
    if (argc == 1) {
        std::string syntaxString;

        syntaxString += "Syntax: delta [options] [filepath].\n";
        syntaxString += "[options]\n";
        syntaxString += "-watch: Prints Bhaskara (IDE) information in console;\n";
        syntaxString += "-debug: Prints debugging information in console;\n\n";
        syntaxString += "[filepath]: Relative or absolute path of .delta file to be compiled.";

        throw std::runtime_error(syntaxString);
    }

    std::string filePath = argv[argc - 1];
    std::string extension = filePath.substr(filePath.find_last_of('.') + 1, filePath.size());

    if (extension != "delta") {
        std::runtime_error("Error: File extension must be 'delta', got '" + extension + "'.");
    }

    this->filePath = filePath;

    for (int i = 1; i < argc - 1; i++) {
        std::string argument(argv[i]);

        if (argument == "-watch") {
            this->watch = true;
        } else if (argument == "-debug") {
            this->debug = true;
        } else {
            std::runtime_error("Error: Invalid argument '" + argument + "'.");
        }
    }
}

std::string ConsoleParser::getFilePath() {
    return this->filePath;
}

bool ConsoleParser::isWatch() {
    return this->watch;
}

bool ConsoleParser::isDebug() {
    return this->debug;
}
