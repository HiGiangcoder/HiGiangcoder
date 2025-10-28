#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXW = 1e9;
const int MAXN = 10;
const int MAXM = 20;

// ✅ NORMAL: random có đường đi 1→n
void genNormalCase() {
    int n = rnd.next(5, MAXN);
    int m = rnd.next(n, MAXM);
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
        cout << u << " " << v << " " << rnd.next(1, 100) << "\n";
}

// ⚙️ EDGE: min/max, 1 cạnh, hoặc trọng số cực trị
void genEdgeCase() {
    int type = rnd.next(1, 3);
    if (type == 1) {
        cout << 2 << " " << 1 << "\n1 2 1\n";
    } else if (type == 2) {
        cout << MAXN << " " << MAXM << "\n";
        for (int i = 1; i <= MAXM; i++) {
            int u = rnd.next(1, MAXN);
            int v = rnd.next(1, MAXN);
            if (u == v) v = (v % MAXN) + 1;
            cout << u << " " << v << " " << rnd.next(1, MAXW) << "\n";
        }
    } else {
        int n = 5, m = 6;
        cout << n << " " << m << "\n";
        for (int i = 0; i < m; i++)
            cout << rnd.next(1, n-1) << " " << rnd.next(2, n)
                 << " " << (rnd.next(0,1) ? 1 : (int)MAXW) << "\n";
    }
}

// 🧩 SPECIAL: không có đường đi, nhiều cạnh trùng, đỉnh cô lập
void genSpecialCase() {
    int n = rnd.next(5, MAXN);
    int m = rnd.next(5, MAXM);
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n-1);
        int v = rnd.next(1, n-1);
        cout << u << " " << v << " " << rnd.next(1, 100) << "\n";
    }
}

// 💥 STRESS: max n, m
void genStressCase() {
    cout << MAXN << " " << MAXM << "\n";
    for (int i = 0; i < MAXM; i++) {
        int u = rnd.next(1, MAXN);
        int v = rnd.next(1, MAXN);
        if (u == v) v = (v % MAXN) + 1;
        cout << u << " " << v << " " << rnd.next(1, MAXW) << "\n";
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    if (argc < 3) {
        cerr << "Usage: ./gen_sub1 <seed> <type(1=Normal,2=Edge,3=Special,4=Stress)>\n";
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
