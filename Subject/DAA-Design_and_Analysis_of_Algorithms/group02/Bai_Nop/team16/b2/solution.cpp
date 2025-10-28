#include <bits/stdc++.h>
#define int long long
using namespace std;
const long long INF = (1LL<<62);

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; if(!(cin >> n >> m)) return 0;
    vector<vector<pair<int,int>>> g(n+1);
    for (int i=0;i<m;i++){
        int u,v; int w; cin >> u >> v >> w;
        g[u].push_back({v,w}); // đa cạnh ok
    }
    vector<long long> dist(n+1, INF);
    using P=pair<long long,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[1]=0; pq.push({0,1});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if (d!=dist[u]) continue;
        if (u==n) break;
        for (auto [v,w]: g[u]){
            long long nd=d+w;
            if (nd<dist[v]){ dist[v]=nd; pq.push({nd,v}); }
        }
    }
    cout << (dist[n]==INF? -1: dist[n]) << "\n";
    return 0;
}
