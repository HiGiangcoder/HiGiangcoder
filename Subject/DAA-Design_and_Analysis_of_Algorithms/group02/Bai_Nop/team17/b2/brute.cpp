#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const long long INF = 1e18; // Dùng số lớn cho vô cực, phải là long long

struct Edge {
    int u, v, w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<long long> dist(n + 1, INF);
    dist[1] = 0;

    // Lặp lại N-1 lần
    for (int i = 0; i < n - 1; ++i) {
        // Duyệt qua tất cả M cạnh để tối ưu (relax)
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.w;
            }
        }
    }

    // Kết quả
    if (dist[n] == INF) {
        cout << -1 << endl;
    } else {
        cout << dist[n] << endl;
    }

    return 0;
}