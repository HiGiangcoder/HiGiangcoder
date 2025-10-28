#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    struct Edge {
        int u;
        int v;
        long long w;
    };
    vector<Edge> edges;
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    const long long INF = (1LL << 62);
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;
    for (int iter = 0; iter < n - 1; ++iter) {
        bool updated = false;
        for (const auto& e : edges) {
            if (dist[e.u] == INF) continue;
            if (dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        if (!updated) break;
    }

    if (dist[n] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dist[n] << '\n';
    }
    return 0;
}

