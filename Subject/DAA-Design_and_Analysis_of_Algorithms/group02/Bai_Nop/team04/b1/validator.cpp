#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100'000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -100'000, 100'000, "a_i");
    inf.readEoln();

    inf.readEof();
}

