#ifndef WARNINGS_H
#define WARNINGS_H

#include "../Model/Type.h"

#include <string>

class Warning {
public:
    Warning(const std::string &msg, int position)
      : message(msg), position(position) { }

    const char *getMessage() const { return message.c_str(); }
    int getPosition() const { return position; }

private:
    std::string message;
    int position;
};


class ReadingIdentifierWithoutInitializationWarning : public Warning {
public:
    ReadingIdentifierWithoutInitializationWarning(const std::string &identifier)
      : Warning("Reading unitialized identifier '" + identifier + "'", -1) { }
};


class UnusedIdentifierWarning : public Warning {
public:
    UnusedIdentifierWarning(const std::string &identifier)
      : Warning("Unused identifier '" + identifier + "'", -1) { }
};


class PrecisionLossWarning : public Warning {
public:
    PrecisionLossWarning(const std::string &identifier, const Type &typeExpression, const Type &typeIdentifier)
      : Warning("Precision loss while assigning '" + typeExpression.toString() + "' to '" + identifier + "' of type '" + typeIdentifier.toString() + "'", -1) { }
};

#endif // WARNINGS_H
