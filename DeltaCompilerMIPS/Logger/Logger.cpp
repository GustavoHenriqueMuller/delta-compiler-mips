#include "Logger.h"

void Logger::addWarning(const Warning &warning) {
    warnings.push_back(warning);
}

void Logger::logWarnings() {
    for (int i = 0; i < warnings.size(); i++) {
        std::cout << "[WARNING]: " << warnings[i].getMessage() << std::endl;
    }
}

void Logger::logError(const AnalysisError &error) {
    std::cout << "[ERROR]: " << error.getMessage() << std::endl;
}
