#pragma once
#include <string>

using namespace std;

class Test {
public:
    virtual void startTest() = 0;
    virtual ~Test() {}
    virtual void evaluate() = 0;
};

// Note: The implementation of the methods should be in a separate .cpp file.