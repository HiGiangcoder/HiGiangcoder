#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

void printGraph(int n, const vector<pair<int,int>>& edges) {
    cout << n << " " << edges.size() << "\n";
    for (auto [u, v] : edges)
        cout << u << " " << v << "\n";
}

void genNormalCase() {
    int n = rnd.next(4, MAXN);
    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (rnd.next(0, rnd.next(1, 3)) == 0) edges.push_back({i, j});
    printGraph(n, edges);
}

void genSpecialCase() {
    int n = MAXN;
    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            edges.push_back({i, j});
    printGraph(n, edges);
}

void genEdgeCase() {
    int n = rnd.next(1, 2);
    vector<pair<int,int>> edges;
    if (n == 2 && rnd.next(0, 1)) edges.push_back({1, 2});
    printGraph(n, edges);
}

void genStressCase() {
    int n = MAXN;
    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (rnd.next(0, 4) != 0) edges.push_back({i, j}); // 75% có cạnh
    printGraph(n, edges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    if (argc < 3) {
        cerr << "Usage: gen <type:1..4> <seed>\n";
        return 1;
    }
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);

    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase();
    else if (type == 3) genEdgeCase();
    else genStressCase();
}
