#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const int MAXW = 1e9;

void genTest(int n, int m, int isStress) {
    vector<pair<int, int>> edges;

    if (rnd.next(1, 100) <= 100) {
        vector<int> p(n + 1);
        iota(p.begin() + 1, p.end(), 1);
        shuffle(p.begin() + 2, p.end() - 1); 

        int u = 1;
        for (int i = 2; i <= n; ++i) {
            int v = (i == n) ? n : p[i];
            if (edges.size() < m) {
                edges.push_back({u, v});
                u = v;
                if (u == n) break;
            } else {
                break;
            }
        }
    }

    while (edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        edges.push_back({u, v});
    }

    shuffle(edges.begin(), edges.end());

    for (const auto& edge : edges) {
        int w = rnd.next(1, MAXW);
        if (isStress) {
            w = rnd.next(MAXW - 1000, MAXW);
        }

        cout << edge.first << " " << edge.second << " " << w << endl;
    }

}

void genTestSpecial(int n, int m, int isStress) {
    vector<pair<int, int>> edges;

    for (int i = 0; i < m; ++i) {
        int u = rnd.next(1, n - 1);
        int v = rnd.next(1, n - 1);
        edges.push_back({u, v});
    }

    shuffle(edges.begin(), edges.end());

    for (const auto& edge : edges) {
        int w = rnd.next(1, MAXW);
        if (isStress) {
            w = rnd.next(MAXW - 1000, MAXW);
        }

        cout << edge.first << " " << edge.second << " " << w << endl;
    }
}

void genNormalCase() {
    int n = rnd.next(2, 1000);
    int m = rnd.next(n, 2 * n);
    cout << n << " " << m << endl;

    int isStress = 0;
    genTest(n, m, isStress);
}

void genSpecialCase() {
    int n = rnd.next(2, 1000);
    int m = rnd.next(n, 2 * n);
    cout << n << " " << m << endl;

    int isStress = 0;
    genTestSpecial(n, m, isStress);
}

void genEdgeCase() {
    int n = rnd.next(1000, 1000);
    int m = rnd.next(n, 2 * n);
    cout << n << " " << m << endl;

    int isStress = 0;
    genTest(n, m, isStress);
}

void genStressCase() {
    int n = rnd.next(1000, 1000);
    int m = rnd.next(n, 2 * n);
    cout << n << " " << m << endl;

    int isStress = 1;
    genTest(n, m, isStress);
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