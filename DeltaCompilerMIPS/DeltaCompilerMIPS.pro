TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ConsoleParser/ConsoleParser.cpp \
    Gals/Constants.cpp \
    Gals/Lexico.cpp \
    Gals/Semantico.cpp \
    Gals/Sintatico.cpp \
    Generator/Generator.cpp \
    Logger/Logger.cpp \
    Main.cpp \
    Model/Operation.cpp \
    Model/OperationManager.cpp \
    Utils/Utils.cpp

HEADERS += \
    ConsoleParser/ConsoleParser.h \
    Gals/AnalysisError.h \
    Gals/Constants.h \
    Gals/LexicalError.h \
    Gals/Lexico.h \
    Gals/SemanticError.h \
    Gals/Semantico.h \
    Gals/Sintatico.h \
    Gals/SyntaticError.h \
    Gals/Token.h \
    Generator/Generator.h \
    Logger/Errors.h \
    Logger/Logger.h \
    Logger/Warnings.h \
    Model/Action.h \
    Model/Expression.h \
    Model/Operation.h \
    Model/OperationManager.h \
    Model/Parameter.h \
    Model/Scope.h \
    Model/Symbol.h \
    Model/Type.h \
    Utils/FileManager.h \
    Utils/JsonBuilder.h \
    Utils/Utils.h
