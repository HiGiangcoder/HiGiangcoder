// bug_1based.cpp
#include <bits/stdc++.h>
using namespace std;
// Code giả sử nodes 1..n nhưng khai báo vector size n (0..n-1)
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<vector<int>> g(n, vector<int>(n,0)); // BUG: should be n+1
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        // if u==n then g[u][v] out of range
        if(u>=0 && u<n && v>=0 && v<n) g[u][v]=g[v][u]=1;
    }
    // very naive: print vertices 1..n if graph connected
    vector<int> vis(n,0);
    function<void(int)> dfs = [&](int u){
        vis[u]=1;
        for(int v=0; v<n; v++) if(g[u][v] && !vis[v]) dfs(v);
    };
    dfs(0);
    bool ok=true;
    for(int i=0;i<n;i++) if(!vis[i]) ok=false;
    if(ok){
        for(int i=1;i<=n;i++){
            if(i>1) cout << ' ';
            cout << i;
        }
        cout<<"\n";
    } else cout << -1 << "\n";
    return 0;
}
