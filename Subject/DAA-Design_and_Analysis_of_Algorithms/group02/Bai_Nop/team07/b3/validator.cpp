#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

bool exist[MAXN + 1][MAXN + 1];

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
        if (u == v)
            quitf(_fail, "Self-loop detected: u == v == %d (edge #%d)", u, i + 1);

        if (exist[u][v] || exist[v][u])
            quitf(_fail, "Duplicate edge detected: (%d, %d)", u, v);
        exist[u][v] = exist[v][u] = true;
    }
    inf.readEof();
}