#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;
const ll INF = 1e18;

struct State {
    ll distance;
    int vertex;

    bool operator>(const State& other) const {
        return distance > other.distance;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> adj[n + 1];
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<ll> dist(n + 1, INF);
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int u = current.vertex;
        ll d = current.distance;

        if (d > dist[u]) {
            continue;
        }
        
        if (u == n) {
            break;
        }

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

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