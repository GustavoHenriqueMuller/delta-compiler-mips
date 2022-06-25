#include "Gals/AnalysisError.h"
#include "Gals/Constants.h"
#include "Gals/Lexico.h"
#include "Gals/Semantico.h"
#include "Gals/Sintatico.h"
#include "Utils/FileManager.h"
#include "Logger/Logger.h"
#include "Generator/Generator.h"
#include "ConsoleParser/ConsoleParser.h"

#include <iostream>

// TODO: Fazer assigns serem expressões

int main(int argc, char **argv) {
    ConsoleParser consoleParser;

    try {
        consoleParser.parse(argc, argv);
    } catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl << std::endl;
        return 1;
    }

    std::string sourceCode = FileManager::getFileContent(consoleParser.getFilePath());
    std::istringstream stream = std::istringstream(sourceCode);

    Logger logger;
    Generator generator;
	
    try {
        Lexico* lexico = new Lexico(stream);
        Sintatico* sintatico = new Sintatico();
        Semantico* semantico = new Semantico(logger, generator, consoleParser);

        sintatico->parse(lexico, semantico);
        semantico->popScope();

        std::string asmFilePath = FileManager::getAsmFilePath(consoleParser.getFilePath());

        if (consoleParser.isDebug()) {
            Utils::printBar();
            std::cout << sourceCode << std::endl;
            Utils::printBar();
            std::cout << generator.getCode() << std::endl;
            Utils::printBar();
        }

        if (consoleParser.isWatch()) {
            std::cout << "[SCOPES]: " << semantico->getScopesJson() << std::endl;
            std::cout << "[ASM_PATH]: " << asmFilePath << std::endl << std::endl;
        }

        logger.logWarnings();
        FileManager::saveToFile(generator.getCode(), asmFilePath);

        std::cout << std::endl;
        std::cout << "File '" << FileManager::getSimplifiedName(consoleParser.getFilePath()) << "' compiled successfully." << std::endl;
        std::cout << "File '" << FileManager::getSimplifiedName(asmFilePath) << "' created." << std::endl << std::endl;
    } catch (AnalysisError e) {
        std::cout << std::endl;
        logger.logWarnings();

        std::cout << std::endl;
        logger.logError(e);
    }

    return 0;
}
