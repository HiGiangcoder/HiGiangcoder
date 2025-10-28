#include <bits/stdc++.h>
#define int long long
using namespace std;
const long long INF = (1LL<<60);

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<tuple<int,int,int>> E; E.reserve(m);
    for (int i=0;i<m;i++){ int u,v; int w; cin>>u>>v>>w; E.emplace_back(u,v,w); }
    vector<long long> dist(n+1, INF); dist[1]=0;
    for (int it=1; it<=n-1; ++it){
        bool ok=false;
        for (auto &e: E){
            int u,v; int w; tie(u,v,w)=e;
            if (dist[u]<INF && dist[u]+w<dist[v]){ dist[v]=dist[u]+w; ok=true; }
        }
        if (!ok) break;
    }
    cout << (dist[n]>=INF? -1: dist[n]) << "\n";
    return 0;
}
