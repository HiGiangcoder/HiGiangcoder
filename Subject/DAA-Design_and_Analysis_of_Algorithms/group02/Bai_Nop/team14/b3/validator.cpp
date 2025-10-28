#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 12;

    // Đọc n và m
    int n = inf.readInt(1, MAXN, "n");
    inf.readSpace();
    int m = inf.readInt(0, n * (n - 1) / 2, "m");
    inf.readEoln();

    set<pair<int,int>> edges;

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, format("u[%d]", i+1));
        inf.readSpace();
        int v = inf.readInt(1, n, format("v[%d]", i+1));
        inf.readEoln();

        ensuref(u != v, "Cạnh %d có hai đỉnh trùng nhau (%d, %d)", i+1, u, v);

        if (u > v) swap(u, v);
        ensuref(!edges.count({u, v}),
                "Cạnh trùng lặp: (%d, %d)", u, v);
        edges.insert({u, v});
    }

    inf.readEof();
}
