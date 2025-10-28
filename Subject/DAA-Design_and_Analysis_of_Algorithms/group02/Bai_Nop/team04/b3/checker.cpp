#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<bool>> adj(n, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        --u;
        --v;
        adj[u][v] = adj[v][u] = true;
    }

    auto parseVertex = [&](const string& token) -> int {
        long long val;
        try {
            size_t pos = 0;
            val = stoll(token, &pos);
            if (pos != token.size()) {
                quitf(_pe, "Token \"%s\" is not an integer", token.c_str());
            }
        } catch (...) {
            quitf(_pe, "Token \"%s\" is not an integer", token.c_str());
        }
        if (val < 1 || val > n) {
            quitf(_wa, "Vertex %lld out of range [1, %d]", val, n);
        }
        return static_cast<int>(val - 1);
    };

    string ansToken = ans.readToken();
    bool ansHasPath = (ansToken != "-1");
    if (ansHasPath) {
        parseVertex(ansToken);
        for (int i = 1; i < n; ++i) {
            ans.readInt(1, n);
        }
        if (!ans.eof())
            ans.readEoln();
        // ans.readEof();
    } else {
        if (!ans.eof())
            ans.readEoln();
        // ans.readEof();
    }

    string token = ouf.readToken();
    if (token == "-1") {
        if (ansHasPath) {
            quitf(_wa, "Hamilton path exists but contestant output -1");
        }
        if (!ouf.eof())
            ouf.readEoln();
        // ouf.readEof();
        quitf(_ok, "Correctly reported no Hamilton path");
    }

    if (!ansHasPath) {
        quitf(_wa, "No Hamilton path exists but contestant output a path");
    }

    vector<int> path(n);
    path[0] = parseVertex(token);
    vector<bool> used(n, false);
    used[path[0]] = true;

    for (int i = 1; i < n; ++i) {
        int vertex = ouf.readInt(1, n) - 1;
        if (used[vertex]) {
            quitf(_wa, "Vertex %d appears more than once", vertex + 1);
        }
        if (!adj[path[i - 1]][vertex]) {
            quitf(_wa, "Edge (%d, %d) does not exist", path[i - 1] + 1, vertex + 1);
        }
        used[vertex] = true;
        path[i] = vertex;
    }
    if (!ouf.eof())
        ouf.readEoln();
    // ouf.readEof();

    if (count(used.begin(), used.end(), true) != n) {
        quitf(_wa, "Path does not visit all vertices");
    }

    quitf(_ok, "Valid Hamilton path");
}
