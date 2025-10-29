#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10;
const int MAX_M = 20;
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
    int n = rnd.next(2, MAX_N);
    int mTarget = rnd.next(n - 1, MAX_M);
    set<pair<int, int>> used;
    vector<Edge> edges;
    edges.reserve(mTarget);

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffleWithRnd(perm);
    ensurePath(used, edges, perm, 1, 50);

    int fail = 0;
    while ((int)edges.size() < mTarget && fail < 200) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        long long w = rnd.next(1, 100);
        if (addEdge(used, edges, u, v, w)) fail = 0;
        else ++fail;
    }
    printGraph(n, edges);
}

void genSpecialTie() {
    int n = rnd.next(5, MAX_N);
    set<pair<int, int>> used;
    vector<Edge> edges;

    // Build a guaranteed long path with near-1e9 weights to expose overflow bugs.
    vector<int> heavy(n);
    iota(heavy.begin(), heavy.end(), 1);
    ensurePath(used, edges, heavy, 900000000, 1000000000);

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffleWithRnd(perm);

    // Create two almost identical paths with a tie in distance
    ensurePath(used, edges, perm, 1, 20);
    vector<int> alt = perm;
    if (n > 3) {
        swap(alt[1], alt[2]);
    }
    ensurePath(used, edges, alt, 1, 20);

    // Add a heavy direct edge to tempt greedy mistakes
    addEdge(used, edges, 1, n, 1000);

    printGraph(n, edges);
}

void genSpecialHeavy() {
    int n = rnd.next(5, MAX_N);
    set<pair<int, int>> used;
    vector<Edge> edges;

    vector<int> path(n);
    iota(path.begin(), path.end(), 1);
    ensurePath(used, edges, path, 900000000, 1000000000);

    int mTarget = rnd.next((int)edges.size(), MAX_M);
    while ((int)edges.size() < mTarget) {
        int attempts = 0;
        bool added = false;
        while (attempts < 20 && !added) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) {
                ++attempts;
                continue;
            }
            long long w = rnd.next(900000000, 1000000000);
            added = addEdge(used, edges, u, v, w);
            ++attempts;
        }
        if (!added) break;
    }
    printGraph(n, edges);
}

void genSpecialDisconnected() {
    int n = rnd.next(4, MAX_N);
    set<pair<int, int>> used;
    vector<Edge> edges;

    int split = rnd.next(2, n - 2);
    vector<int> left, right;
    for (int i = 1; i <= n; ++i) {
        if (i <= split) left.push_back(i);
        else right.push_back(i);
    }
    ensurePath(used, edges, left, 1, 50);
    if (!right.empty()) {
        ensurePath(used, edges, right, 1, 50);
    }
    int extra = rnd.next(0, MAX_M - (int)edges.size());
    int fail = 0;
    while (extra-- > 0 && fail < 200) {
        int u, v;
        if (rnd.next(0, 1)) {
            u = rnd.next(1, split - 1);
            v = rnd.next(u + 1, split);
        }
        else {
            u = rnd.next(split + 1, n - 1);
            v = rnd.next(u + 1, n);
        }
        long long w = rnd.next(1, 1000);
        if (addEdge(used, edges, u, v, w)) fail = 0;
        else ++fail;
    }
    printGraph(n, edges);
}

void genSpecialBfsTrap() {
    int n = 6;
    set<pair<int, int>> used;
    vector<Edge> edges;

    auto add = [&](int u, int v, long long w) {
        addEdge(used, edges, u, v, w);
    };

    add(1, 2, 1000);      // heavy direct arc
    add(2, 6, 1000);

    add(1, 3, 1);         // light path discovered later
    add(3, 4, 1);
    add(4, 5, 1);
    add(5, 6, 1);

    add(2, 3, 1);         // extra cross edges to delay discovery
    add(3, 2, 2000);
    add(4, 2, 2000);
    add(4, 6, 5000);

    printGraph(n, edges);
}

void genSpecialDuplicateEdges() {
    int n = rnd.next(4, 6);
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

    int baseLimit = min(MAX_M / 2, (int)baseEdges.size() + rnd.next(0, 3));
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
        weights[0] = rnd.next(1, 100);
        for (int j = 1; j < copies; ++j) {
            weights[j] = weights[j - 1] + rnd.next(1, 20);
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

void genSpecialBfsKiller() {
    int n = MAX_N;
    set<pair<int, int>> used;
    vector<Edge> edges;

    for (int i = 1; i < n; ++i) {
        long long w = 1000000 - i;
        addEdge(used, edges, i, i + 1, w);
    }
    for (int i = 1; i + 2 <= n; ++i) {
        addEdge(used, edges, i, i + 2, 1);
    }
    for (int i = 2; i <= n; ++i) {
        addEdge(used, edges, i, max(1, i - 1), 500000);
    }
    printGraph(n, edges);
}

void genSpecial(int variant) {
    if (variant == 2) genSpecialHeavy();
    else if (variant == 3) genSpecialDisconnected();
    else if (variant == 4) genSpecialBfsTrap();
    else if (variant == 5) genSpecialBfsKiller();
    else if (variant == 6) genSpecialDuplicateEdges();
    else genSpecialTie();
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
        edges.reserve(mTarget);
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 1);
        ensurePath(used, edges, perm, 1, 10);
        int fail = 0;
        while ((int)edges.size() < mTarget && fail < 300) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            long long w = rnd.next(1, 1000);
            if (addEdge(used, edges, u, v, w)) fail = 0;
            else ++fail;
        }
        printGraph(n, edges);
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
    ensurePath(used, edges, perm, 500000000, 1000000000);

    int fail = 0;
    while ((int)edges.size() < mTarget && fail < 300) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        long long w = rnd.next(500000000, 1000000000);
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
