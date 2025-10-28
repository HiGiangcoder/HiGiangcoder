// #include <iostream>
// #include <vector>
// #include <limits>
// using namespace std;

// const long long INF = 1e18;

// // Đây là cách tôi code Dijkstra khi mới học
// // Có thể chưa tối ưu nhưng tôi cố gắng làm đúng

// void dijkstra_moi_hoc() {
//     int n, m;
//     cin >> n >> m;
    
//     // Tạo mảng lưu đồ thị - tôi dùng ma trận kề vì dễ hình dung
//     vector<vector<long long>> graph(n + 1, vector<long long>(n + 1, INF));
    
//     // Khởi tạo đường chéo = 0 (tự thân tới tự thân)
//     for (int i = 1; i <= n; i++) {
//         graph[i][i] = 0;
//     }
    
//     // Đọc các cạnh
//     for (int i = 0; i < m; i++) {
//         int u, v;
//         long long w;
//         cin >> u >> v >> w;
//         graph[u][v] = w;
//         // Tôi không chắc có nên ghi đè nếu có nhiều cạnh cùng u,v
//         // Nhưng tôi cứ ghi đè và hy vọng
//     }
    
//     // Mảng khoảng cách và đánh dấu đã thăm
//     vector<long long> dist(n + 1, INF);
//     vector<bool> visited(n + 1, false);
    
//     // Bắt đầu từ đỉnh 1
//     dist[1] = 0;
    
//     // Tôi nhớ là phải lặp n lần
//     for (int count = 0; count < n; count++) {
//         // Tìm đỉnh chưa thăm có dist nhỏ nhất
//         int u = -1;
//         long long min_dist = INF;
        
//         for (int i = 1; i <= n; i++) {
//             if (!visited[i] && dist[i] < min_dist) {
//                 min_dist = dist[i];
//                 u = i;
//             }
//         }
        
//         // Nếu không tìm thấy đỉnh nào thì dừng
//         if (u == -1 || min_dist == INF) {
//             break;
//         }
        
//         // Đánh dấu đỉnh u đã thăm
//         visited[u] = true;
        
//         // Cập nhật khoảng cách tới các đỉnh kề của u
//         for (int v = 1; v <= n; v++) {
//             // Nếu có đường đi từ u đến v
//             if (graph[u][v] != INF && !visited[v]) {
//                 long long new_dist = dist[u] + graph[u][v];
//                 if (new_dist < dist[v]) {
//                     dist[v] = new_dist;
//                 }
//             }
//         }
        
//         // Tôi thử in ra để debug xem sao
//         // cout << "Sau khi xet dinh " << u << ": ";
//         // for (int i = 1; i <= n; i++) cout << dist[i] << " ";
//         // cout << endl;
//     }
    
//     // In kết quả
//     if (dist[n] == INF) {
//         cout << -1 << endl;
//     } else {
//         cout << dist[n] << endl;
//     }
// }

// int main() {
//     // Tôi tắt cái này vì thấy người ta hay làm
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     dijkstra_moi_hoc();
    
//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;

#define INF 1e18 + 7
#define int long long

struct Edge {
    int to, weight;
};

vector<int> dijkstra(int n, vector<vector<Edge>>& graph, int start) {
    vector<int> dist(n, INF), parent(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        for (auto e : graph[u]) {
            int v = e.to, w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> graph(n + 5);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<int> dist = dijkstra(n + 5, graph, 1);
    cout << (dist[n] == INF ? -1 : dist[n]);
    cout << "\n";
    return 0;
}