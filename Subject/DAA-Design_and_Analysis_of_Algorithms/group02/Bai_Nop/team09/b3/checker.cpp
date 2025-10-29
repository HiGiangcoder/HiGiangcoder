#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(1, 12, "n");
    inf.readSpace();
    int m = inf.readInt(0, n*(n-1)/2, "m");
    inf.readEoln();

    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    set<pair<int,int>> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();
        ensuref(u != v, "Loop (%d, %d) not allowed", u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Duplicate edge (%d, %d)", a, b);
        edges.insert({a, b});
        adj[u][v] = adj[v][u] = 1;
    }

    // --- đọc toàn bộ output dưới dạng string ---
    string outContestant = ouf.readString();
    string outAnswer = ans.readString();

    // --- TH1: contestant in "-1" ---
    if (outContestant == "-1") {
        if (outAnswer != "-1")
            quitf(_wa, "Contestant printed -1 but answer has Hamiltonian path");
        quitf(_ok, "Correct: no Hamiltonian path");
    }

    // --- TH2: parse dãy số ---
    stringstream ss(outContestant);
    vector<int> path;
    int x;
    while (ss >> x) path.push_back(x);

    if ((int)path.size() != n)
        quitf(_wa, "Expected %d vertices, got %d", n, (int)path.size());

    vector<int> seen(n + 1, 0);
    for (int v : path) {
        if (v < 1 || v > n)
            quitf(_wa, "Vertex %d out of range [1, %d]", v, n);
        if (seen[v])
            quitf(_wa, "Vertex %d appears multiple times", v);
        seen[v] = 1;
    }

    for (int i = 0; i + 1 < n; i++) {
        int u = path[i], v = path[i + 1];
        if (!adj[u][v])
            quitf(_wa, "Edge (%d, %d) does not exist", u, v);
    }

    if (outAnswer == "-1")
        quitf(_fail, "Contestant found Hamiltonian path but jury did not");

    quitf(_ok, "Valid Hamiltonian path");
}
