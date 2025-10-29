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
    vector<int> outDegree(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        ++outDegree[u];
    }

    const long long INF = (1LL << 62);
    vector<long long> dist(n + 1, INF);
    vector<bool> processed(n + 1, false);
    dist[1] = 0;

    using State = tuple<long long, int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    auto heuristic = [&](int u) -> int {
        return outDegree[u];
    };

    pq.emplace(dist[1], heuristic(1), 1);

    while (!pq.empty()) {
        auto [du, heur, u] = pq.top();
        pq.pop();
        if (processed[u]) continue;
        processed[u] = true;
        if (u == n) break;

        sort(adj[u].begin(), adj[u].end(), [&](const auto& a, const auto& b) {
            long long gainA = dist[u] + a.second;
            long long gainB = dist[u] + b.second;
            if (gainA != gainB) return gainA < gainB;
            return outDegree[a.first] > outDegree[b.first];
        });

        for (auto [v, w] : adj[u]) {
            if (processed[v]) continue;
            long long nd = dist[u] + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.emplace(dist[v], heuristic(v), v);
            }
        }
    }

    if (dist[n] == INF) cout << -1 << '\n';
    else cout << dist[n] << '\n';
    return 0;
}

