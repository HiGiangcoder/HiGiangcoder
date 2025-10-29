#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
const int INF = 1e9;

bool g[15][15];

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAXN, "n");
    inf.readSpace();
    int m = inf.readInt(0, n*(n-1)/2, "m");
    inf.readEoln();
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        if(g[u][v] || u == v) {
            quitf(_fail, "Edge (%d, %d) is duplicated or invalid", u, v);
        }
        g[u][v] = g[v][u] = true;
    }
    inf.readEof();
}
