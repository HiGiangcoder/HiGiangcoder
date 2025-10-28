#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 12, "n");
    inf.readSpace();
    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(0, maxEdges, "m");
    inf.readEoln();

    set<pair<int, int>> used;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        if (u == v) {
            quitf(_fail, "Self-loop at vertex %d is not allowed", u);
        }
        if (u > v) swap(u, v);
        if (!used.insert({u, v}).second) {
            quitf(_fail, "Multiple edges between %d and %d", u, v);
        }
    }

    inf.readEof();
}

