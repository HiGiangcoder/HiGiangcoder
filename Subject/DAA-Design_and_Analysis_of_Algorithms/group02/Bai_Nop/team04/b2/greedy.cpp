#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }

    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<bool> visited(n + 1, false);
    vector<long long> dist(n + 1, (1LL << 62));
    dist[1] = 0;

    using State = pair<long long, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        if (u == n) break;

        // Greedy choice: relax edges in increasing weight order only once
        sort(adj[u].begin(), adj[u].end(), [](const auto& a, const auto& b) {
            if (a.second == b.second) return a.first < b.first;
            return a.second < b.second;
        });
        for (auto [v, w] : adj[u]) {
            if (visited[v]) continue;
            long long nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    if (dist[n] == (1LL << 62)) cout << -1 << '\n';
    else cout << dist[n] << '\n';
    return 0;
}

