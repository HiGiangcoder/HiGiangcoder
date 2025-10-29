#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int N = 1e5 + 5;
const int mod = 1e9 + 7;

struct Edge{
    int u, v, w;
};
vector<Edge> Nodes;
ll dist[N];
int n, m;

signed main()
{  
    cin >> n >> m;
    int u, v, k;
    for(int i = 1; i <= m; ++i){
        cin >> u >> v >> k;
        Nodes.push_back({u, v, k});
    }
    memset(dist, 0x3f, sizeof dist);
    ll wa = dist[1];
    dist[1] = 0;

    for(int i = 1; i <= n; ++i)
        for(Edge c : Nodes)
            dist[c.v] = min(dist[c.v], dist[c.u] + c.w);
    if(dist[n] >= wa) return cout << -1, 0;
    cout << dist[n];
}
