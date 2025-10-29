// solution.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll, int> > pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [du, u] = pq.top();
        du *= -1;
        pq.pop();
        if (du != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > du + w) {
                dist[v] = du + w;
                pq.push({-dist[v], v});
            }
        }
    }

    cout << (dist[n] == INF ? -1 : dist[n]) << "\n";
    return 0;
}