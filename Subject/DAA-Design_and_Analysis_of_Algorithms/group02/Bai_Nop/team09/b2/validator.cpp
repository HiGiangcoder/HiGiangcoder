#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();
    for (int i = 1; i <= m; i++) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readSpace();
        int w = inf.readInt(1, 1000000000, "w");
        inf.readEoln();
    }
    inf.readEof();
}
