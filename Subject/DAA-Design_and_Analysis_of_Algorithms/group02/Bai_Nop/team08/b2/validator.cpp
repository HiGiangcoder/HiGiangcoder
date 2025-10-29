#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        long long w = inf.readLong(1LL, 1000000000LL, "w");
        inf.readEoln();
    }

    inf.readEof();
}
