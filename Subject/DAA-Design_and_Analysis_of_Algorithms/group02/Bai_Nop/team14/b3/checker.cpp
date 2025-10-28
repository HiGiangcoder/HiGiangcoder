#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(1, 12, "n");
    int m = inf.readInt(0, n*(n-1)/2, "m");

    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        int v = inf.readInt(1, n, "v_i");
        ensuref(u != v, "Self-loop detected: %d-%d", u, v);
        ensuref(!adj[u][v], "Duplicate edge: %d-%d", u, v);
        adj[u][v] = adj[v][u] = 1;
    }
    // inf.readEof();

    if (ouf.seekEof()) {
        quitf(_wa, "Empty output");
    }

    // Try to read first token
    string token = ouf.readToken();

    if (token == "-1") {
        // Thí sinh nói không có đường Hamilton, kiểm tra lại
        // DP bitmask để xem có tồn tại đường Hamilton hay không
        if (!ouf.seekEof())
            quitf(_wa, "Extra output after -1");
        int FULL = (1 << n) - 1;
        vector<vector<char>> dp(1 << n, vector<char>(n, 0));
        for (int i = 0; i < n; i++) dp[1 << i][i] = 1;

        bool exist = false;
        for (int mask = 1; mask <= FULL; ++mask) {
            for (int last = 0; last < n; ++last) {
                if (!dp[mask][last]) continue;
                if (mask == FULL) {
                    exist = true;
                    break;
                }
                for (int nxt = 0; nxt < n; ++nxt) {
                    if (mask & (1 << nxt)) continue;
                    if (adj[last + 1][nxt + 1]) {
                        dp[mask | (1 << nxt)][nxt] = 1;
                    }
                }
            }
            if (exist) break;
        }

        if (exist) {
            quitf(_wa, "Contestant printed -1 but Hamiltonian path exists");
        } else {
            quitf(_ok, "Correct: no Hamiltonian path exists");
        }
    }

    // Otherwise, thí sinh in ra dãy đỉnh
    vector<int> path;
    path.push_back(stoi(token));
    while (!ouf.seekEof()) {
        path.push_back(ouf.readInt());
    }

    if ((int)path.size() != n) {
        quitf(_wa, "Expected %d vertices, found %d", n, (int)path.size());
    }

    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int v = path[i];
        if (v < 1 || v > n)
            quitf(_wa, "Vertex %d out of range [1..%d]", v, n);
        if (seen[v])
            quitf(_wa, "Vertex %d appears more than once", v);
        seen[v] = 1;
    }

    for (int i = 0; i + 1 < n; i++) {
        if (!adj[path[i]][path[i + 1]]) {
            quitf(_wa, "No edge between %d and %d (positions %d-%d)",
                  path[i], path[i + 1], i + 1, i + 2);
        }
    }

    quitf(_ok, "Valid Hamiltonian path");
}
