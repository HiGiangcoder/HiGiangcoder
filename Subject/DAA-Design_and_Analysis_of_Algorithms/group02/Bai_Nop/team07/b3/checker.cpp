#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int n;
bool adj[MAXN + 5][MAXN + 5];
int degCnt[MAXN + 5];

bool isHamiltonPath(const vector<int>& path) {
    for (int i = 1; i < (int)path.size(); ++i) {
        if (!adj[path[i - 1]][path[i]]) return false;
    }
    for (int v = 1; v <= n; ++v) {
        if (degCnt[v] != 1) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    int m = inf.readInt();

    vector<pair<int,int>> edges(m + 10);
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges[i] = {u, v};
        adj[u][v] = adj[v][u] = true;
    }

    vector<int> path;
    int contestantFirst = ouf.readInt();
    int referenceFirst  = ans.readInt();

    if (referenceFirst == -1) {
        if (contestantFirst != -1) {
            quitf(_wa, "Answer: expected -1, found %d", contestantFirst);
        }
        ouf.seekEof();
        quitf(_ok, "Answer correct (-1)");
    } else {
        if (contestantFirst == -1) {
            quitf(_wa, "Answer: Hamilton path exists but contestant printed -1");
        }

        path.push_back(contestantFirst);
        if (contestantFirst < 1 || contestantFirst > n)
            quitf(_wa, "Vertex out of range: %d", contestantFirst);
        degCnt[contestantFirst]++;

        while ((int)path.size() != n) {
            int v = ouf.readInt();
            path.push_back(v);
            if (v < 1 || v > n)
                quitf(_wa, "Vertex out of range: %d", v);
            degCnt[v]++;
        }

        ouf.seekEof();

        if (!isHamiltonPath(path)) {
            quitf(_wa, "Path is not Hamiltonian");
        }
        quitf(_ok, "Answer correct (Hamiltonian path)");
    }
}
