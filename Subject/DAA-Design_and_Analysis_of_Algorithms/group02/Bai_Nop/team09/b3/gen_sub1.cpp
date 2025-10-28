#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

long long rd(long long l, long long r) {
    return rnd.next(l, r);
}

void genStressCase() {
    int n = rd(1, 12);
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) edges.push_back({i, j});
    shuffle(edges.begin(), edges.end());
    int m = rd(0, (int)edges.size());
    while (edges.size() > m) edges.pop_back();
    cout << n << " " << m << "\n";
    for (auto x : edges) cout << x.first << " " << x.second << "\n";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    genStressCase();
    return 0;
}
