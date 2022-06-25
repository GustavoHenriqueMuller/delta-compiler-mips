#ifndef LOGGER_H
#define LOGGER_H

#include "Logger.h"
#include "Warnings.h"
#include "../Gals/AnalysisError.h"

#include <vector>
#include <string>
#include <iostream>

class Logger {
public:
    Logger() {}
    void addWarning(const Warning &warning);
    void logWarnings();
    void logError(const AnalysisError &logError);

private:
    std::vector<Warning> warnings;
};

#endif // LOGGER_H
