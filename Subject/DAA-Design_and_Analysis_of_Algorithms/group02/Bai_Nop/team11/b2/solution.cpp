#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18; // Sử dụng số lớn cho vô cực

struct Edge {
    int to;
    int weight;
};

struct State {
    long long dist;
    int u;

    // So sánh ngược để priority_queue thành min-heap
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<long long> dist(n + 1, INF);
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        long long d = current.dist;
        int u = current.u;

        // Bỏ qua nếu đã có đường đi tốt hơn
        if (d > dist[u]) {
            continue;
        }

        if (u == n) break; // Tối ưu: dừng sớm nếu đã đến đích

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[n] == INF) {
        cout << -1 << endl;
    } else {
        cout << dist[n] << endl;
    }

    return 0;
}