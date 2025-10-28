#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 12, "n");
    inf.readSpace();
    int m = inf.readInt(0, n * (n - 1) / 2, "m");
    inf.readEoln();

    set<pair<int,int>> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "Edge (%d, %d) is a self-loop", u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Duplicate edge (%d, %d)", u, v);
        edges.insert({a, b});
    }

    inf.readEof();
}
