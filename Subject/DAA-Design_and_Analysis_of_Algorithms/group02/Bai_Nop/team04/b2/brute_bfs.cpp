#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        // adj[v].push_back({u, w});
    }

    const long long INF = (1LL << 62);
    vector<long long> dist(n + 1, INF);
    queue<int> q;
    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : adj[u]) {
            long long nd = dist[u] + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                q.push(v);
            }
        }
    }

    if (dist[n] == INF) cout << -1 << '\n';
    else cout << dist[n] << '\n';
    return 0;
}
