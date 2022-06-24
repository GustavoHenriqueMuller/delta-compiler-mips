#ifndef JSON_BUILDER_H
#define JSON_BUILDER_H

#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

class JsonBuilder {

private:
    std::stringstream payload;

public:
    JsonBuilder() { }

    std::string build() {
        this->payload << "]";
        std::string temp = this->replace(this->payload.str(), ",}", "}");
        return "[" + this->replace(temp, ",]", "]");
    }

    void open() {
        this->payload << "{";
    }

    void close() {
        this->payload << "},";
    }

    template<class T>
    void set(std::string key, T value) {
        this->payload << this->attribute(key) << this->quotes(value) << ",";
    }

private:
    template<class T>
    std::string quotes(T key) {
        return "\"" + std::to_string(key) + "\"";
    }

    std::string quotes(bool key) {
        return "\"" + std::to_string(int(key)) + "\"";
    }

    std::string quotes(std::string key) {
        return "\"" + key + "\"";
    }

    std::string quotes(const char *key) {
        return "\"" + std::string(key) + "\"";
    }

    std::string quotes(char key) {
        return "\"" + std::string(1, key) + "\"";
    }

    std::string attribute(std::string key) {
        return this->quotes(key) + ":";
    }

    std::string replace(std::string text, const std::string& target, const std::string& newString) {
        std::size_t startPos = 0;
        while((startPos = text.find(target, startPos)) != std::string::npos) {
            text.replace(startPos, target.length(), newString);
            startPos += newString.length();
        }
        return text;
    }

};

#endif // JSON_BUILDER_H
