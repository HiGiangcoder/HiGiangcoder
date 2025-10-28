#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int maxn =1e9;
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();
    for (int i = 0; i < m; i++) {
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(1, n, "r");
        inf.readEoln();
    }
    inf.readEof();
}
