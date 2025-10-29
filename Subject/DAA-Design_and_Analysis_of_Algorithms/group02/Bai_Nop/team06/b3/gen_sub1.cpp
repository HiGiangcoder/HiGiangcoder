#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
vector<bool> used(MAXN + 36, false);
vector<int> adj[MAXN + 36];

int label_map[MAXN + 9];

void genPermutation(int l, int r) {
    for (int i=1;i<=MAXN;i++) label_map[i] = i;
    for (int i=l;i<=r;i++) {
        int j = rnd.next(i, r);
        swap(label_map[i], label_map[j]);
    }
}

void genNormalCase() {
    int n = rnd.next(3, 6);
    int m = rnd.next(n-1, n * (n - 1) / 2);
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        while (u == v || find(adj[u].begin(), adj[u].end(), v) != adj[u].end()) {
            u = rnd.next(1, n);
            v = rnd.next(1, n);
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << n << " " << m << "\n";
    genPermutation(1, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)adj[i].size(); j++) {
            if(adj[i][j] < i) continue;
            cout << label_map[i] << " " << label_map[adj[i][j]] << "\n";
        }
    }
}

void genSpecialCase() {
    int n = rnd.next(1, MAXN);
    if(n==1)
    {
        cout << 1 << " " << 0 << "\n";
        return;
    }
    int m = rnd.next(n-2, (n-2) * (n - 1) / 2);
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n-1);
        int v = rnd.next(1, n-1);
        while (u == v || find(adj[u].begin(), adj[u].end(), v) != adj[u].end()) {
            u = rnd.next(1, n-1);
            v = rnd.next(1, n-1);
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << n << " " << m << "\n";
    genPermutation(1, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)adj[i].size(); j++) {
            if(adj[i][j] < i) continue;
            cout << label_map[i] << " " << label_map[adj[i][j]] << "\n";
        }
    }
}

void genEdgeCase() {
    int n = MAXN;
    int m = rnd.next(n+n/2, n + n*2);
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n-1);
        int v = rnd.next(1, n-1);
        while (u == v || find(adj[u].begin(), adj[u].end(), v) != adj[u].end()) {
            u = rnd.next(1, n-1);
            v = rnd.next(1, n-1);
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << n << " " << m << "\n";
    genPermutation(1, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)adj[i].size(); j++) {
            if(adj[i][j] < i) continue;
            cout << label_map[i] << " " << label_map[adj[i][j]] << "\n";
        }
    }
}

void genStressCase() {
    int n = MAXN;
    int m = rnd.next(n-1, n + n*2);
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        while (u == v || find(adj[u].begin(), adj[u].end(), v) != adj[u].end()) {
            u = rnd.next(1, n);
            v = rnd.next(1, n);
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << n << " " << m << "\n";
    genPermutation(1, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)adj[i].size(); j++) {
            if(adj[i][j] < i) continue;
            cout << label_map[i] << " " << label_map[adj[i][j]] << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();
    return 0;
}
