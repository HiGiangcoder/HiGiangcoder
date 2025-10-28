#include "testlib.h"
#include <vector>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 12, "n");
    inf.readSpace();
    long long m_max = (long long)n * (n - 1) / 2;
    int m = inf.readInt(0, m_max, "m");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loops are not allowed.");
        if (u > v) swap(u, v);
        ensuref(edges.find({u, v}) == edges.end(), "Duplicate edges are not allowed.");
        edges.insert({u, v});
    }

    inf.readEof();
    return 0;
}