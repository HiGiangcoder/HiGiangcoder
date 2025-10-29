#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const int MAXM = 200000;
const int INF = 1e9;

int label_map[MAXN + 9];

void genPermutation(int l, int r) {
    for (int i=1;i<=MAXN;i++) label_map[i] = i;
    for (int i=l;i<=r;i++) {
        int j = rnd.next(i, r);
        swap(label_map[i], label_map[j]);
    }
}

void genGraph(int n, int m, int lim_w_l, int lim_w_r, bool special = false) {
    cout << n << " " << m << "\n";
    if(special) genPermutation(2, n-1);
    else genPermutation(1, n);
    vector<pair<pair<int,int>,int>> edges;
    for(int i = 1;i < n;i++) {
        int w = rnd.next(lim_w_l, lim_w_r);
        if(edges.size()<m) edges.push_back({{i, i+1}, w});
    }
    if(n+2<=m){
        edges.push_back({{n, 1}, 1});
        edges.push_back({{1, 2}, lim_w_r}); 
    }
    for(int i = n+2;i <= m;i++) {
        int u = rnd.next(1, n);
        int v = rnd.next(u, n);
        int w = rnd.next(lim_w_l, lim_w_r);
        edges.push_back({{u, v}, w});
    }
    int l = 1, r = n;
    if (!special) {
        l = 2, r = n-1;
    }

    for(auto [uv, w] : edges) {
        int u = uv.first, v = uv.second;
        if(l<=u && u<=r) u = label_map[u];
        if(l<=v && v<=r) v = label_map[v];
        cout << label_map[u] << " " << label_map[v] << " " << w << "\n";
    }
}

void genNormalCase() {
    int n = rnd.next(100, MAXN);
    genGraph(n, rnd.next(n+2, MAXM), 1, INF, false);
}

void genSpecialCase() {
    int n = rnd.next(100, MAXN);
    genGraph(n, rnd.next(n+2, MAXM), 1, INF, true);
}

void genEdgeCase() {
    genGraph(MAXN, MAXM, INF/2, INF, false);
}

void genStressCase() {
    int n = MAXN;
    genGraph(n, MAXM, 1, INF, false);
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
