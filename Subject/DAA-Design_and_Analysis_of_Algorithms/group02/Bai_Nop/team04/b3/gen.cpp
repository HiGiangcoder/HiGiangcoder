#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using Edge = pair<int,int>;

void addEdge(int u, int v, set<Edge>& used, vector<Edge>& edges) {
    if (u == v) return;
    if (u > v) swap(u, v);
    if (used.insert({u, v}).second) edges.push_back({u, v});
}

bool hasHamilton(int n, const vector<Edge>& edges) {
    vector<vector<int>> adj(n);
    vector<vector<bool>> has(n, vector<bool>(n, false));
    for (auto [U, V] : edges) {
        int u = U - 1;
        int v = V - 1;
        if (!has[u][v]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            has[u][v] = has[v][u] = true;
        }
    }

    int full = (1 << n) - 1;
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) parent[1 << i][i] = -2;
    for (int mask = 1; mask <= full; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (parent[mask][last] == -1) continue;
            for (int to : adj[last]) {
                if (mask & (1 << to)) continue;
                int nextMask = mask | (1 << to);
                if (parent[nextMask][to] == -1)
                    parent[nextMask][to] = last;
            }
        }
    }
    for (int v = 0; v < n; ++v) if (parent[full][v] != -1) return true;
    return false;
}

void printGraph(int n, const vector<Edge>& edges) {
    cout << n << " " << edges.size() << "\n";
    for (auto [u, v] : edges) cout << u << " " << v << "\n";
}

void shuffleVec(vector<int>& a) {
    for (int i = (int)a.size() - 1; i > 0; --i) {
        int j = rnd.next(0, i);
        swap(a[i], a[j]);
    }
}

void genRandomHamilton() {
    int n = rnd.next(6, 12);
    set<Edge> used;
    vector<Edge> edges;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffleVec(perm);
    for (int i = 0; i < n - 1; ++i) addEdge(perm[i], perm[i + 1], used, edges);
    int extra = rnd.next(n, min(n * (n - 1) / 2, n + 10));
    while ((int)edges.size() < extra) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        addEdge(u, v, used, edges);
    }
    printGraph(n, edges);
}

void genDisconnected() {
    int n = rnd.next(6, 12);
    int left = rnd.next(2, n - 2);
    set<Edge> used;
    vector<Edge> edges;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffleVec(perm);
    for (int i = 1; i < left; ++i) addEdge(perm[i - 1], perm[i], used, edges);
    for (int i = left + 1; i < n; ++i) addEdge(perm[i - 1], perm[i], used, edges);
    int extra = rnd.next(0, n);
    while (extra--) {
        int side = rnd.next(0, 1);
        if (side == 0) {
            int u = perm[rnd.next(0, left - 1)];
            int v = perm[rnd.next(0, left - 1)];
            addEdge(u, v, used, edges);
        } else {
            int u = perm[rnd.next(left, n - 1)];
            int v = perm[rnd.next(left, n - 1)];
            addEdge(u, v, used, edges);
        }
    }
    printGraph(n, edges);
}

void genClique() {
    int n = rnd.next(5, 12);
    set<Edge> used;
    vector<Edge> edges;
    for (int u = 1; u <= n; ++u)
        for (int v = u + 1; v <= n; ++v)
            addEdge(u, v, used, edges);
    printGraph(n, edges);
}

void genGreedyTrap() {
    int n = 6;
    set<Edge> used;
    vector<Edge> edges;
    for (int i = 1; i < n; ++i) addEdge(i, i + 1, used, edges);
    addEdge(1, 3, used, edges);
    addEdge(1, 4, used, edges);
    addEdge(1, 5, used, edges);
    addEdge(3, 5, used, edges);
    printGraph(n, edges);
}

void genStarNoHamilton() {
    int n = rnd.next(5, 12);
    set<Edge> used;
    vector<Edge> edges;
    for (int v = 2; v <= n; ++v) addEdge(1, v, used, edges);
    printGraph(n, edges);
}

void genSmallEdgecases() {
    int pick = rnd.next(0, 2);
    set<Edge> used;
    vector<Edge> edges;
    if (pick == 0) {
        printGraph(1, edges);
    } else if (pick == 1) {
        addEdge(1, 2, used, edges);
        printGraph(2, edges);
    } else {
        addEdge(1, 2, used, edges);
        addEdge(2, 3, used, edges);
        printGraph(3, edges);
    }
}

void genBfsTrap() {
    int n = rnd.next(8, 12);
    set<Edge> used;
    vector<Edge> edges;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffleVec(perm);
    for (int i = 0; i < n - 1; ++i) addEdge(perm[i], perm[i + 1], used, edges);
    for (int i = 0; i < n && (int)edges.size() < n * (n - 1) / 2; ++i) {
        for (int j = 0; j < i && (int)edges.size() < n * (n - 1) / 2; ++j) {
            if (rnd.next(0, 1) && abs(perm[i] - perm[j]) > 1) {
                addEdge(perm[i], perm[j], used, edges);
            }
        }
    }
    printGraph(n, edges);
}

void genBfsTrapHeavy() {
    int n = rnd.next(10, 12);
    set<Edge> used;
    vector<Edge> edges;
    for (int i = 1; i < n; ++i) addEdge(i, i + 1, used, edges);
    for (int i = 3; i <= n; ++i) addEdge(i, rnd.next(1, i - 1), used, edges);
    for (int i = 1; i + 5 <= n; ++i) addEdge(i, i + 5, used, edges);
    printGraph(n, edges);
}

void genBfsRandomTrap() {
    int n = rnd.next(8, 12);
    set<Edge> used;
    vector<Edge> edges;
    edges.reserve(6 * n);
    for (int i = 1; i < n; ++i) addEdge(i, i + 1, used, edges);
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 2; v <= n; ++v) {
            if (rnd.next(0, 2) == 0) addEdge(u, v, used, edges);
        }
    }
    printGraph(n, edges);
}

void genDenseNoHamilton() {
    int n = 12;
    set<Edge> used;
    vector<Edge> edges;
    int attempts = 0;
    while (true) {
        used.clear();
        edges.clear();
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 1)) addEdge(u, v, used, edges);
            }
        }
        if ((int)edges.size() < n) continue;
        if (!hasHamilton(n, edges)) {
            printGraph(n, edges);
            return;
        }
        if (++attempts > 1000) {
            // fallback: construct known no-Hamilton structure
            used.clear();
            edges.clear();
            vector<int> group = {1,2,3,4,5,6,7,8,9,10,11,12};
            for (int i = 0; i < 4; ++i) {
                for (int a = 0; a < 3; ++a)
                    for (int b = a + 1; b < 3; ++b)
                        addEdge(group[3*i + a], group[3*i + b], used, edges);
            }
            addEdge(3,4,used,edges);
            addEdge(6,7,used,edges);
            // intentionally missing bridges to force failure
            printGraph(n, edges);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);

    switch (type) {
        case 0: genRandomHamilton(); break;
        case 1: genDisconnected(); break;
        case 2: genClique(); break;
        case 3: genGreedyTrap(); break;
        case 4: genStarNoHamilton(); break;
        case 5: genSmallEdgecases(); break;
        case 6: genBfsTrap(); break;
        case 7: genBfsTrapHeavy(); break;
        case 8: genBfsRandomTrap(); break;
        case 9: genDenseNoHamilton(); break;
        default: genRandomHamilton(); break;
    }
    return 0;
}
