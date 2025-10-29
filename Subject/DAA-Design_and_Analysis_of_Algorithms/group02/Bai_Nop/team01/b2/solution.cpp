#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
#define int long long

vector<pair<int, int>> adj[MAXN + 9];
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m;i ++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<long long> dist(n + 1, 1e16);
    dist[1] = 0;
    pq.push({0, 1});
    while(!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if(d != dist[u]) continue;  
        for(auto [v, w] : adj[u])
        {
            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    cout << (dist[n] == 1e16 ? -1 : dist[n]) << "\n";
}
