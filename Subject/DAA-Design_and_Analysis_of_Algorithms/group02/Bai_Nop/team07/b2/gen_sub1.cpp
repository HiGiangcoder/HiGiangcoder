#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 20;
const int MAXW = 1e9;

int label_map[MAXN + 5];
vector<tuple<int,int,int>> edges;

void genGraphEnsurePath(int n, int m, int wL, int wR, bool keepEnds = true, bool dagMode = false) {
    for (int i = 1; i <= MAXN; ++i) label_map[i] = i;
    if (keepEnds && n >= 3) {
        for (int i = 2; i <= n-1; ++i) {
            int j = rnd.next(i, n-1);
            swap(label_map[i], label_map[j]);
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            int j = rnd.next(i, n);
            swap(label_map[i], label_map[j]);
        }
    }

    auto mapNode = [&](int x)->int {
        if (keepEnds && 2 <= x && x <= n-1) return label_map[x];
        if (!keepEnds) return label_map[x];
        return x;
    };

    int backboneEdges = 1;
    if (n >= 3) backboneEdges = rnd.next(1, min(n-1, m));
    vector<int> mids;
    int k = backboneEdges;
    if (k >= 2) {
        vector<int> pool;
        for (int v = 2; v <= n-1; ++v) pool.push_back(v);
        shuffle(pool.begin(), pool.end(), mt19937(rnd.next(0, INT_MAX)));
        mids.assign(pool.begin(), pool.begin() + (k-1));
        sort(mids.begin(), mids.end());
    }
    vector<int> path;
    path.push_back(1);
    for (int x : mids) path.push_back(x);
    path.push_back(n);

    for (int i = 0; i+1 < (int)path.size(); ++i) {
        int u = path[i], v = path[i+1];
        int w = rnd.next(wL, wR);
        edges.emplace_back(mapNode(u), mapNode(v), w);
    }

    while ((int)edges.size() < m) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        int w = rnd.next(wL, wR);
        if (dagMode && v < u) swap(u, v);
        edges.emplace_back(mapNode(u), mapNode(v), w);
    }
}

void genGraphEnsureNoPath(int n, int m, int wL, int wR){
    vector<int> node;
    for (int i=2;i<= n-1;i++ )
        node.push_back(i);
    shuffle(node.begin(), node.end(), mt19937(rnd.next(0, INT_MAX)));
    
    vector<int> list_of_A, list_of_B;
    list_of_A.push_back(1);
    for (int i=0;i< (int)node.size()/2;i++ )
        list_of_A.push_back(node[i]);
    list_of_B.push_back(n);
    for (int i=(int)node.size()/2;i< (int)node.size();i++ )
        list_of_B.push_back(node[i]);

    for (int i = 0; i < m/2; ++i) {
        int u = list_of_A[rnd.next(0, (int)list_of_A.size()-1)];
        int v = list_of_A[rnd.next(0, (int)list_of_A.size()-1)];
        int w = rnd.next(wL, wR);
        edges.emplace_back(u, v, w);
    }
    for (int i = m/2; i < m; ++i) {
        int u = list_of_B[rnd.next(0, (int)list_of_B.size()-1)];
        int v = list_of_B[rnd.next(0, (int)list_of_B.size()-1)];
        int w = rnd.next(wL, wR);
        edges.emplace_back(u, v, w);
    }
}

void genLineGraph(int n, int m, int wL, int wR){
    for (int i=1;i<= min(n-1, m);i++ ){
        int u = i;
        int v = i + 1;
        int w = rnd.next(wL, wR);
        edges.emplace_back(u, v, w);
    }

    while ((int)edges.size() < m){
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        int w = rnd.next(wL, wR);
        edges.emplace_back(u, v, w);
    }
}

void genStarGraph(int n, int m, int wL, int wR){
    int center = rnd.next(2, n);
    edges.emplace_back(1, center, rnd.next(wL, wR));
    
    while ((int)edges.size() < m){
        int v;
        do {
            v = rnd.next(2, n);
        } while (v == center);

        int w = rnd.next(wL, wR);
        edges.emplace_back(center, v, w);
    }
}


void genNormalCase(int s) {
    int n = rnd.next(2, MAXN);
    int m = rnd.next(n - 1, MAXM);
    cout << n << ' ' << m << '\n';
    if (s % 4 == 0)
        genGraphEnsureNoPath(n, m, 1, MAXW);
    else if (s % 4 == 1)
        genGraphEnsurePath(n, m, 1, MAXW);
    else if (s % 4 == 2)
        genGraphEnsurePath(n, m, 1, MAXW, false, false);
    else genGraphEnsurePath(n, m, 1, MAXW, true, true);
}


void genSpecialCase(int s) {
    if (s % 3 == 1){
        int n = rnd.next(2, MAXN);
        int m = n - 1;
        cout << n << ' ' << m << '\n';
        genLineGraph(n, m, MAXW/2, MAXW);
    }
    else if (s % 3 == 2){
        int n = rnd.next(2, MAXN);
        int m = n - 1;
        cout << n << ' ' << m << '\n';
        genStarGraph(n, m, MAXW/2, MAXW);
    }
    else{
        int n = rnd.next(MAXN/4, MAXN/2);
        int m = MAXM;
        cout << n << ' ' << m << '\n';
        genLineGraph(n, m, 1, MAXW);
    }
}

void genEdgeCase(int s) {
    if (s % 3 == 1){
        int n = 2, m = 1;
        cout << n << ' ' << m << '\n';
        edges.emplace_back(n, m, MAXW);
    }
    else if (s % 3 == 2){
        int n = MAXN, m = n - 1;
        cout << n << ' ' << m << '\n';
        genLineGraph(n, m, MAXW - 1, MAXW);
    }
    else{
        int n = MAXN, m = 1;
        cout << n << ' ' << m << '\n';
        edges.emplace_back(rnd.next(1, n), rnd.next(1, n), MAXW);
    }
}

void genStressCase(int s) {
    int n = MAXN, m = MAXM;
    cout << n << ' ' << m << '\n';
    if (s % 4 == 0)
        genGraphEnsurePath(n, m, 1, MAXW);
    else if (s % 4 == 1)
        genGraphEnsureNoPath(n, m, 1, MAXW);
    else if (s % 4 == 2)
        genLineGraph(n, m, 1, MAXW);
    else genStarGraph(n, m, 1, MAXW);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    
    if (type == 1) genNormalCase(seed);
    else if (type == 2) genSpecialCase(seed);
    else if (type == 3) genEdgeCase(seed);
    else genStressCase(seed);

    for (auto [u, v, w]: edges){
        cout << u << ' ' << v << ' ' << w << '\n';
    }

    return 0;
}
