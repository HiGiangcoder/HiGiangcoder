#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1); // adj[u] = {v, w}

    for (int i = 0; i < m; ++i) {
        int u, v;
        int w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [du, u] = pq.top();
        pq.pop();
        if (du != dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > du + w) {
                dist[v] = du + w;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[n] == INF)
        cout << -1;
    else
        cout << dist[n];

    return 0;
}
