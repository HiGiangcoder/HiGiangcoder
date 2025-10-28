#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int MIN_N = 2;
const int MAX_N = 12;
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(MIN_N, MAX_N, "n");
    inf.readSpace();
    long long max_m = (long long)n * (n - 1) / 2;

    int m = inf.readInt(0, max_m, "m");
    inf.readEoln();

    set<pair<int, int>> edges;

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected on vertex %d", u);

        if (u > v) {
            swap(u, v);
        }

        ensuref(edges.find({u, v}) == edges.end(), "Duplicate edge (%d, %d) found", u, v);

        edges.insert({u, v});
    }

    inf.readEof();
}
