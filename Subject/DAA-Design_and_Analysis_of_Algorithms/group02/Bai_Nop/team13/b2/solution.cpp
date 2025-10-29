#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Edge {
    int to;
    ll weight;
};

// Sử dụng pair thông thường với greater
typedef pair<ll, int> Pair;  // first: distance, second: vertex

const ll INF = numeric_limits<ll>::max();

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<ll> dist(n + 1, INF);
    // Sửa: priority_queue với greater
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Quan trọng: Kiểm tra xem có phải distance hiện tại không
        if (d != dist[u]) {
            continue;
        }
        
        // Có thể bỏ điều kiện này, không cần thiết
        // if (u == n) break;

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            ll weight = edge.weight;

            // Sửa: Loại bỏ điều kiện dist[u] != INF
            // Vì nếu dist[u] = INF, d != dist[u] ở trên đã xử lý rồi
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[n] == INF) {
        cout << -1 << endl;
    } else {
        cout << dist[n] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}