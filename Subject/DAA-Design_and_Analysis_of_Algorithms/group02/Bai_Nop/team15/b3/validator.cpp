#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 12, "n");
    inf.readSpace();
    int m = inf.readInt(0, n*(n-1)/2, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
    }

    inf.readEof();
}
