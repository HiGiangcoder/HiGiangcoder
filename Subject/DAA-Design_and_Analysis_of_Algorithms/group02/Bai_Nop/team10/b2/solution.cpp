#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define sc second
#define pll pair<ll,ll>
#define pii pair<int,int>
#define all(x) (x).begin(),(x).end()
#define TASK "main"
#define int ll
const int nmax = 2e5 + 76;
int n, m;
vector<pii> adj[nmax];

struct node{
    int u, dist;
};

struct cmp{
    bool operator()(node a,node b){
        return a.dist > b.dist;
    }
};
int d[nmax];
bool vis[nmax];
int trace[nmax];

int dijkstra(int s){
    priority_queue<node, vector<node>, cmp> pq;
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    pq.push({1, 0});
    while(pq.size()){
        auto x = pq.top();
        pq.pop();
        if(vis[x.u]) continue;
        vis[x.u] = 1;
        for(auto e : adj[x.u]){
            if(d[e.fi] > d[x.u] + e.sc){
                d[e.fi] = d[x.u] + e.sc;
                trace[e.fi] = x.u;
                pq.push({e.fi, d[e.fi]});
            }
        }
    }
    if(d[n] >= 1e18) return - 1;
    return d[n];
}






void solve(){
    cin >> n >> m;
    for(int i = 1;i<=m;++i){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        // adj[v].push_back({u,w}); <--- Fix bug
    }
    int d = dijkstra(1);
    cout << d << '\n';
}

main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    
     solve();
}