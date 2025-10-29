
#include <bits/stdc++.h>

using namespace std;

// Định nghĩa kiểu dữ liệu
typedef long long ll;

const ll INF = 1e18 + 7;

void solve_brute() {
    int n, m;
    if (!(cin >> n >> m)) return;

    // Danh sách kề: {đỉnh đích, trọng số}
    vector<tuple<int, int, ll>> edges;
    vector<vector<pair<int, ll>>> adj(n + 1);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // Mảng khoảng cách, khởi tạo là INF
    vector<ll> dist(n + 1, INF);
    // Mảng đánh dấu đã thăm
    vector<bool> visited(n + 1, false);

    dist[1] = 0;

    // Thuật toán Dijkstra cơ bản (không dùng Priority Queue)
    for (int count = 1; count <= n; ++count) {
        ll min_dist = INF;
        int u_min = -1;

        // Tìm đỉnh u chưa thăm có khoảng cách nhỏ nhất
        for (int u = 1; u <= n; ++u) {
            if (!visited[u] && dist[u] < min_dist) {
                min_dist = dist[u];
                u_min = u;
            }
        }

        // Nếu không tìm thấy đỉnh nào hoặc đã thăm hết
        if (u_min == -1) break;

        visited[u_min] = true;

        // Cập nhật khoảng cách đến các đỉnh kề
        for (const auto& edge : adj[u_min]) {
            int v = edge.first;
            ll weight = edge.second;

            if (dist[u_min] != INF && dist[u_min] + weight < dist[v]) {
                dist[v] = dist[u_min] + weight;
            }
        }
    }

    // In kết quả
    if (dist[n] == INF) {
        cout << -1 << endl;
    } else {
        cout << dist[n] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve_brute();
    return 0;
}