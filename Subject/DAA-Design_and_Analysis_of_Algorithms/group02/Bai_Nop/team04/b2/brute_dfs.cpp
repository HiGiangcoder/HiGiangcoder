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

    vector<int> visited(n + 1, 0);
    const long long INF = (1LL << 62);
    long long bestDist = INF;

    function<void(int,long long)> dfs = [&](int u, long long dist) {
        if (dist >= bestDist) return;
        if (u == n) {
            bestDist = min(bestDist, dist);
            return;
        }
        visited[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (!visited[v]) {
                dfs(v, dist + w);
            }
        }
        visited[u] = 0;
    };

    dfs(1, 0LL);

    if (bestDist == INF) cout << -1 << '\n';
    else cout << bestDist << '\n';
    return 0;
}
