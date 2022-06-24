#ifndef CONSOLE_PARSER_H
#define CONSOLE_PARSER_H

#include <string>

class ConsoleParser {
public:
    ConsoleParser() {}
    void parse(int argc, char** argv);

    std::string getFilePath();
    bool isWatch();
    bool isDebug();

private:
    std::string filePath = "";
    bool watch = false;
    bool debug = false;
};

#endif // CONSOLE_PARSER_H
