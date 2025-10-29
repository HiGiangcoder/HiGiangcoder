#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    
    vector<long long> dist(n + 1, INF);
    using State = pair<long long, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    
    dist[1] = 0;
    pq.emplace(0, 1);
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d != dist[u]) continue;
        if (u == n) break;
        
        for (auto [v, w] : adj[u]) {
            long long new_dist = dist[u] + w;
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                pq.emplace(new_dist, v);
            }
        }
    }
    
    cout << (dist[n] == INF ? -1 : dist[n]) << endl;
    
    return 0;
}