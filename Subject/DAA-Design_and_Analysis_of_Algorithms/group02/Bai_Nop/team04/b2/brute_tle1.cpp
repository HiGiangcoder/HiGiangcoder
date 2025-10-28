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
    }

    const long long INF = (1LL << 62);
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;

    // intentionally redo Bellman-Ford from scratch many times to force TLE
    int iterations = max(1, n) * max(1, m);
    for (int outer = 0; outer < iterations; ++outer) {
        for (int iter = 0; iter < n - 1; ++iter) {
            bool updated = false;
            for (int u = 1; u <= n; ++u) {
                if (dist[u] == INF) continue;
                for (auto [v, w] : adj[u]) {
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }
    }

    cout << (dist[n] == INF ? -1 : dist[n]) << '\n';
    return 0;
}

