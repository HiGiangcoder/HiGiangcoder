#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const int MAXM = 2e5;
const int INF = 1e9;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAXN, "n");
    inf.readSpace();
    int m = inf.readInt(1, MAXM, "m");
    inf.readEoln();
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, INF, "w_i");
        inf.readEoln();
    }
    inf.readEof();
}
