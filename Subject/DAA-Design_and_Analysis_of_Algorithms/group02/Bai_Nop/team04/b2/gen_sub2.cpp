#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000;
const int MAX_M = 200000;
using Edge = tuple<int, int, long long>;

template <class T>
void shuffleWithRnd(vector<T>& a) {
    for (int i = (int)a.size() - 1; i > 0; --i) {
        int j = rnd.next(0, i);
        swap(a[i], a[j]);
    }
}

bool addEdge(set<pair<int, int>>& used, vector<Edge>& edges, int u, int v, long long w) {
    if (u == v) return false;
    pair<int, int> key = {u, v};
    if (used.insert(key).second) {
        edges.emplace_back(u, v, w);
        return true;
    }
    return false;
}

void ensurePath(set<pair<int, int>>& used, vector<Edge>& edges, const vector<int>& route, long long minW, long long maxW) {
    for (int i = 0; i + 1 < (int)route.size(); ++i) {
        long long w = rnd.next(minW, maxW);
        addEdge(used, edges, route[i], route[i + 1], w);
    }
}

void printGraph(int n, const vector<Edge>& edges) {
    cout << n << " " << edges.size() << "\n";
    for (auto [u, v, w] : edges) {
        cout << u << " " << v << " " << w << "\n";
    }
}

void genNormal() {
    int n = rnd.next(50, MAX_N);
    int mTarget = min(MAX_M, 3 * n);
    set<pair<int, int>> used;
    vector<Edge> edges;
    edges.reserve(mTarget);

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffleWithRnd(perm);
    ensurePath(used, edges, perm, 1, 1000);

    int fail = 0;
    while ((int)edges.size() < mTarget && fail < 500) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        long long w = rnd.next(1, 2000);
        if (addEdge(used, edges, u, v, w)) fail = 0;
        else ++fail;
    }
    printGraph(n, edges);
}

void genSpecialLayered() {
    int n = rnd.next(200, MAX_N);
    set<pair<int, int>> used;
    vector<Edge> edges;

    int layers = 3;
    vector<vector<int>> layer(layers);
    int idx = 1;
    for (int i = 0; i < layers; ++i) {
        int size = (i == layers - 1) ? n - idx + 1 : rnd.next(1, max(1, (n - idx + 1) / (layers - i)));
        for (int j = 0; j < size && idx <= n; ++j) layer[i].push_back(idx++);
    }
    for (int i = 0; i + 1 < layers && (int)edges.size() < MAX_M; ++i) {
        for (int u : layer[i]) {
            for (int v : layer[i + 1]) {
                if ((int)edges.size() >= MAX_M) break;
                long long w = rnd.next(1, 1000);
                addEdge(used, edges, u, v, w);
            }
            if ((int)edges.size() >= MAX_M) break;
        }
    }
    for (int i = 2; i < layers && (int)edges.size() < MAX_M; ++i) {
        for (int u : layer[i]) {
            for (int v : layer[i - 2]) {
                if ((int)edges.size() >= MAX_M) break;
                addEdge(used, edges, u, v, rnd.next(500, 2000));
            }
            if ((int)edges.size() >= MAX_M) break;
        }
    }
    printGraph(n, edges);
}

void genSpecialHeavy() {
    int n = rnd.next(500, MAX_N);
    set<pair<int, int>> used;
    vector<Edge> edges;

    vector<int> path(n);
    iota(path.begin(), path.end(), 1);
    ensurePath(used, edges, path, 900000000, 1000000000);

    int mTarget = rnd.next((int)edges.size(), MAX_M);
    while ((int)edges.size() < mTarget) {
        bool added = false;
        for (int attempts = 0; attempts < 50 && !added; ++attempts) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) continue;
            long long w = rnd.next(900000000, 1000000000);
            added = addEdge(used, edges, u, v, w);
        }
        if (!added) break;
    }
    printGraph(n, edges);
}

void genSpecialDisconnected() {
    int n = rnd.next(200, MAX_N);
    set<pair<int, int>> used;
    vector<Edge> edges;

    int split = rnd.next(2, n - 2);
    vector<int> left, right;
    for (int i = 1; i <= n; ++i) {
        if (i <= split) left.push_back(i);
        else right.push_back(i);
    }
    ensurePath(used, edges, left, 1, 1000);
    ensurePath(used, edges, right, 1, 1000);

    int extra = min(MAX_M - (int)edges.size(), rnd.next(0, 2 * n));
    int fail = 0;
    while (extra-- > 0 && fail < 500) {
        int u, v;
        if (rnd.next(0, 1)) {
            u = rnd.next(1, split - 1);
            v = rnd.next(u + 1, split);
        }
        else {
            u = rnd.next(split + 1, n - 1);
            v = rnd.next(u + 1, n);
        }
        long long w = rnd.next(1, 2000);
        if (addEdge(used, edges, u, v, w)) fail = 0;
        else ++fail;
    }
    printGraph(n, edges);
}

void genSpecialDuplicateEdges() {
    int n = rnd.next(180, 400);
    vector<pair<int, int>> baseEdges;
    set<pair<int, int>> baseUsed;

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffleWithRnd(perm);

    for (int i = 0; i + 1 < n; ++i) {
        pair<int, int> e = {perm[i], perm[i + 1]};
        baseEdges.push_back(e);
        baseUsed.insert(e);
    }

    int extra = rnd.next(n / 2, n);
    int baseLimit = min(MAX_M / 2, (int)baseEdges.size() + extra);
    while ((int)baseEdges.size() < baseLimit) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v) continue;
        pair<int, int> e = {u, v};
        if (baseUsed.insert(e).second) baseEdges.push_back(e);
    }

    vector<Edge> edges;
    edges.reserve(baseEdges.size() * 3);
    int remain = MAX_M;
    for (size_t i = 0; i < baseEdges.size(); ++i) {
        int left = (int)baseEdges.size() - (int)i;
        int maxCopies = min(3, remain - 2 * (left - 1));
        int copies = rnd.next(2, maxCopies);

        vector<long long> weights(copies);
        weights[0] = rnd.next(1, 500000);
        for (int j = 1; j < copies; ++j) {
            weights[j] = weights[j - 1] + rnd.next(1, 500000);
        }

        for (long long w : weights) {
            edges.emplace_back(baseEdges[i].first, baseEdges[i].second, w);
        }
        remain -= copies;
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        if (get<0>(a) != get<0>(b)) return get<0>(a) < get<0>(b);
        if (get<1>(a) != get<1>(b)) return get<1>(a) < get<1>(b);
        return get<2>(a) < get<2>(b);
    });

    printGraph(n, edges);
}

void genSpecial(int variant) {
    if (variant == 2) genSpecialHeavy();
    else if (variant == 3) genSpecialDisconnected();
    else if (variant == 4) {
        int n = 80;
        set<pair<int, int>> used;
        vector<Edge> edges;
        for (int i = 1; i < n; ++i) addEdge(used, edges, i, i + 1, 1000000 - i);
        for (int i = 1; i + 3 <= n; ++i) addEdge(used, edges, i, i + 3, 1);
        for (int i = 2; i <= n; ++i) addEdge(used, edges, i, i - 1, 400000);
        printGraph(n, edges);
    } else if (variant == 5) {
        int n = rnd.next(600, MAX_N);
        set<pair<int, int>> used;
        vector<Edge> edges;
        for (int i = 1; i < n; ++i) addEdge(used, edges, i, i + 1, 1000000 - i);
        for (int i = 1; i + 2 <= n; ++i) addEdge(used, edges, i, i + 2, 1);
        for (int i = 3; i + 5 <= n; ++i) addEdge(used, edges, i, i + 5, 2);
        for (int i = 2; i <= n; ++i) addEdge(used, edges, i, i - 1, 500000);
        printGraph(n, edges);
    } else if (variant == 6) {
        genSpecialDuplicateEdges();
    } else genSpecialLayered();
}

void genEdge() {
    set<pair<int, int>> used;
    vector<Edge> edges;

    if (rnd.next(0, 1) == 0) {
        int n = 2;
        addEdge(used, edges, 1, 2, 1);
        printGraph(n, edges);
    } else {
        int n = MAX_N;
        int mTarget = min(rnd.next(n - 1, MAX_M), 100);
        set<pair<int, int>> used2;
        vector<Edge> edges2;
        edges2.reserve(mTarget);
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 1);
        ensurePath(used2, edges2, perm, 1, 1);
        int fail = 0;
        while ((int)edges2.size() < mTarget && fail < 1000) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            long long w = rnd.next(1, 1000000000);
            if (addEdge(used2, edges2, u, v, w)) fail = 0;
            else ++fail;
        }
        printGraph(n, edges2);
    }
}

void genStress() {
    int n = MAX_N;
    int mTarget = MAX_M;
    set<pair<int, int>> used;
    vector<Edge> edges;
    edges.reserve(mTarget);

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffleWithRnd(perm);
    ensurePath(used, edges, perm, 1, 100);

    int fail = 0;
    while ((int)edges.size() < mTarget && fail < 1000) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        long long w = rnd.next(1, 1000000000);
        if (addEdge(used, edges, u, v, w)) fail = 0;
        else ++fail;
    }
    printGraph(n, edges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]); // 1-normal,2-special,3-edge,4-stress
    int seed = atoi(argv[2]);
    int variant = (argc >= 4) ? atoi(argv[3]) : 0;
    rnd.setSeed(seed);

    if (type == 1) genNormal();
    else if (type == 2) genSpecial(variant);
    else if (type == 3) genEdge();
    else genStress();
    return 0;
}
