#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        adj[u][v] = adj[v][u] = 1;
    }

    string ans_line = ans.readToken();
    string out_line = ouf.readToken();

    if (ans_line == "-1") {
        if (out_line != "-1")
            quitf(_wa, "Expected -1 but contestant found a path");
        quitf(_ok, "Correctly reported no Hamiltonian path");
    }

    // Read full path from answer
    vector<int> correctPath;
    correctPath.push_back(stoi(ans_line));
    while (!ans.seekEof()) correctPath.push_back(ans.readInt());

    // Read contestant path
    vector<int> path;
    path.push_back(stoi(out_line));
    while (!ouf.seekEof()) path.push_back(ouf.readInt());

    if ((int)path.size() != n)
        quitf(_wa, "Path length must be %d but got %d", n, (int)path.size());

    vector<int> seen(n + 1);
    for (int i = 0; i < n; i++) {
        int u = path[i];
        ensuref(1 <= u && u <= n, "Invalid vertex index %d", u);
        ensuref(!seen[u], "Vertex %d repeated", u);
        seen[u] = 1;
        if (i + 1 < n) {
            int v = path[i + 1];
            if (!adj[u][v]) quitf(_wa, "Edge (%d,%d) not present", u, v);
        }
    }

    quitf(_ok, "Valid Hamiltonian path");
}
