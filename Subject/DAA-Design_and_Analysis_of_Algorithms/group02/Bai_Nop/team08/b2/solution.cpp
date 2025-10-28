#include <bits/stdc++.h>
#define int long long // <-- fix bug
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int MAXN = 100000 + 7;

vector < pii > adj[MAXN];
int dist[MAXN];
int pre[MAXN];

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(pre, -1, sizeof(pre));
    dist[s] = 0;
    priority_queue < pii, vector<pii>, greater<pii> > pq;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().se;
        int d = pq.top().fi;
        pq.pop();
        if (d != dist[u]) continue;
        for (auto e : adj[u]) {
            int v = e.fi;
            int w = e.se;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pre[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    // for (int i = 1; i <= n; ++i) <---- bug
    for (int i = 1; i <= m; i ++) 
    {
        int u, v, w;
        cin >> u >> v >> w;
        // pii cc = make_pair(u, v); <---- bug
        pii cc = make_pair(v, w);
        adj[u].emplace_back(cc);
        // cc = make_pair(v, w);
        // adj[v].emplace_back(cc); <--- bug
    }

    dijkstra(1);

    // cout << dist[n] << '\n'; <--- bug
    if (dist[n] >= 1e15) cout << -1;
    else cout << dist[n];
}
