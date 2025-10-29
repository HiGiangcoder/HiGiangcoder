#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXW = 1e9;
const int MAXN = 1000;

void genNormalCase() {
    int n = rnd.next(200, MAXN);
    int m = rnd.next(n, 5*n);
    cout << n << " " << m << "\n";

    vector<pair<int,int>> path;
    for (int i = 1; i < n; i++) path.push_back({i, i+1});
    set<pair<int,int>> edges(path.begin(), path.end());
    while ((int)edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        edges.insert({u,v});
    }
    for (auto [u,v] : edges)
        cout << u << " " << v << " " << rnd.next(1, 10000) << "\n";
}

void genEdgeCase() {
    int type = rnd.next(1, 2);
    if (type == 1) {
        cout << 2 << " " << 1 << "\n1 2 5\n";
    } else {
        int n = MAXN, m = 5*n;
        cout << n << " " << m << "\n";
        for (int i = 0; i < m; i++) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) v = (v % n) + 1;
            cout << u << " " << v << " " << MAXW << "\n";
        }
    }
}

void genSpecialCase() {
    int n = rnd.next(50, 200);
    int m = rnd.next(50, 300);
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int u = rnd.next(2, n);
        int v = rnd.next(2, n);
        cout << u << " " << v << " " << (rnd.next(1, 2) == 2 ? 1000 : 1) << "\n";
    }
}

void genStressCase() {
    int n = MAXN, m = min(5*n, 200000);
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) v = (v % n) + 1;
        cout << u << " " << v << " " << rnd.next(1, MAXW) << "\n";
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    if (argc < 3) {
        cerr << "Usage: ./gen_sub2 <seed> <type(1=Normal,2=Edge,3=Special,4=Stress)>\n";
        return 1;
    }

    int seed = atoi(argv[1]);
    int type = atoi(argv[2]);
    rnd.setSeed(seed);

    if (type == 1) genNormalCase();
    else if (type == 2) genEdgeCase();
    else if (type == 3) genSpecialCase();
    else genStressCase();

    return 0;
}
