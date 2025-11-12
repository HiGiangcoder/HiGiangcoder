#pragma once
#include <string>
using namespace std;

class Logger {
public:
    static void info(const string& message);
    static void warn(const string& message);
    static void error(const string& message);
};
