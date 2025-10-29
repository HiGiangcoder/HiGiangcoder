#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fi first
#define se second

using ll = long long;
using il = pair<ll, int>;
using li = pair<int, ll>;

#include <bits/stdc++.h>
using namespace std;

struct MinHeap {
    il *heap;
    int size;

    MinHeap(int n) {
        heap = new il[n + 5];
        size = 0;
    }

    inline bool empty() const { return size == 0; }

    inline void push(long long dist, int node) {
        int i = ++size;
        heap[i].fi = dist;
        heap[i].se = node;

        // bubble-up
        while (i > 1) {
            int p = i >> 1;
            if (heap[p].fi <= heap[i].fi) break;
            swap(heap[p], heap[i]);
            i = p;
        }
    }

    inline il top() const { return heap[1]; }

    inline void pop() {
        heap[1] = heap[size--];
        int i = 1;
        while (true) {
            int l = i << 1, r = l | 1, smallest = i;
            if (l <= size && heap[l].fi < heap[smallest].fi) smallest = l;
            if (r <= size && heap[r].fi < heap[smallest].fi) smallest = r;
            if (smallest == i) break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

    ~MinHeap() {
        delete[] heap;
    }
};


struct Edge {
    int u, v;
    ll w, r;
};

const ll INF = 1e18;

ll dijkstra(int n, const vector<vector<li>>& adj) {
    vector<ll> dist(n + 1, INF);
    MinHeap pq(n);
    
    dist[1] = 0;
    pq.push(0, 1);
    
    while (!pq.empty()) {
        auto [du, u] = pq.top();
        pq.pop();
        
        if (du > dist[u]) continue;
        if (u == n) return du;
        
        for (auto [v, w] : adj[u]) {
            ll newDist = dist[u] + w;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                pq.push(newDist, v);
            }
        }
    }
    
    return dist[n];
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    vector<ll> caps;
    caps.reserve(m);
    
    for (auto& e : edges) {
        cin >> e.u >> e.v >> e.w >> e.r;
        caps.push_back(e.r);
    }
    
    sort(caps.begin(), caps.end());
    caps.erase(unique(caps.begin(), caps.end()), caps.end());
    
    auto buildGraph = [&](ll cap) {
        vector<vector<li>> adj(n + 1);
        for (const auto& e : edges) {
            if (e.r <= cap) {
                adj[e.u].emplace_back(e.v, e.w);
                adj[e.v].emplace_back(e.u, e.w);
            }
        }
        return adj;
    };
    
    // Binary search for minimum capacity
    int lo = 0, hi = caps.size() - 1, bestPos = -1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        auto adj = buildGraph(caps[mid]);
        ll dist = dijkstra(n, adj);
        
        if (dist < INF) {
            bestPos = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    if (bestPos == -1) {
        cout << "-1\n";
    } else {
        auto adj = buildGraph(caps[bestPos]);
        ll minDist = dijkstra(n, adj);
        cout << caps[bestPos] << ' ' << minDist << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}