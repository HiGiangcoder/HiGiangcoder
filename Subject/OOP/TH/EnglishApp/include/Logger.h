#pragma once
#include <string>
using namespace std;

class Logger {
public:
    static void info(const string& message);
    static void warn(const string& message);
    static void error(const string& message);
};

void Logger::info(const string& message) {
    printf("[INFO]: %s\n", message.c_str());
}
void Logger::warn(const string& message) {
    printf("[WARN]: %s\n", message.c_str());
}
void Logger::error(const string& message) {
    printf("[ERROR]: %s\n", message.c_str());
}