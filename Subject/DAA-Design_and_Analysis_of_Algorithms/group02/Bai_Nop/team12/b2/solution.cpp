#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const long long INF = 1e18; // Một số rất lớn để biểu diễn vô cực

int main() {
    // Tăng tốc độ nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Biểu diễn đồ thị bằng danh sách kề
    // adj[u] chứa các pair {v, w} là các đỉnh kề và trọng số cạnh
    vector<vector<pair<int, long long>>> adj(n + 1); // <--- bug: sai kieu du lieu: <int, ll> moi dung
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        // Đồ thị vô hướng nên thêm cạnh ở cả hai chiều
        adj[u].push_back({v, w});
        // adj[v].push_back({u, w}); <--- bug: Do thi co huong
    }

    // Mảng lưu khoảng cách ngắn nhất, dùng long long để tránh tràn số
    vector<long long> dist(n + 1, INF);

    // Hàng đợi ưu tiên cho thuật toán Dijkstra
    // Lưu pair {khoảng cách, đỉnh}, sắp xếp theo khoảng cách nhỏ nhất
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    // Bắt đầu từ đỉnh 1
    dist[1] = 0;
    pq.push({0, 1}); // {distance, vertex}

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Tối ưu: nếu đã có đường đi ngắn hơn thì bỏ qua
        if (d > dist[u]) {
            continue;
        }

        // Duyệt các đỉnh kề v của u
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Relaxation step: nếu tìm thấy đường đi tốt hơn thì cập nhật
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // In kết quả
    if (dist[n] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dist[n] << "\n";
    }

    return 0;
}