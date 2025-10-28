#include "testlib.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<bool> > adj(n + 1, vector<bool>(n + 1, false));

    for (int i = 0; i < m; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        adj[u][v] = adj[v][u] = true;
    }

    if (ouf.seekEof()) quitf(_wa, "Output is empty");

    string firstToken = ouf.readToken();
    if (firstToken == "-1") {
        quitf(_ok, "Contestant reports no Hamilton path");
    } else {
        int firstVertex = atoi(firstToken.c_str());
        if (firstVertex < 1 || firstVertex > n)
            quitf(_wa, "Vertex %d out of range", firstVertex);

        vector<int> path;
        path.push_back(firstVertex);
        for (int i = 1; i < n; i++) {
            int v = ouf.readInt(1, n);
            path.push_back(v);
        }

        vector<bool> used(n + 1, false);
        for (int i = 0; i < n; i++) {
            if (used[path[i]]) quitf(_wa, "Vertex %d repeated", path[i]);
            used[path[i]] = true;
            if (i > 0 && !adj[path[i - 1]][path[i]])
                quitf(_wa, "Missing edge between %d and %d", path[i - 1], path[i]);
        }

        quitf(_ok, "Valid Hamilton path");
    }
}
