// bug_connectivity_only.cpp
#include <bits/stdc++.h>
using namespace std;
// Only checks connectivity; assumes connected => Hamilton exists
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        g[u].push_back(v); g[v].push_back(u);
    }
    vector<int> vis(n+1,0);
    function<void(int)> dfs = [&](int u){
        vis[u]=1; for(int v: g[u]) if(!vis[v]) dfs(v);
    };
    dfs(1);
    for(int i=1;i<=n;i++){
        if(!vis[i]){ cout<<-1<<"\n"; return 0; }
    }
    for(int i=1;i<=n;i++){
        if(i>1) cout<<' ';
        cout<<i;
    }
    cout<<"\n";
    return 0;
}
