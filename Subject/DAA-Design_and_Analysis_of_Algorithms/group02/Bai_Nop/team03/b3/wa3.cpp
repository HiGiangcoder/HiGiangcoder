// bug_directed.cpp
#include <bits/stdc++.h>
using namespace std;
// Treats input as directed edges (forgot symmetric assignment)
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<vector<int>> adj(n+1, vector<int>(n+1,0));
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        adj[u][v] = 1; // BUG: should set adj[v][u] = 1 as well
    }
    // simple attempt: try greedy path
    vector<int> used(n+1,0), path;
    int cur = 1; used[cur]=1; path.push_back(cur);
    for(int i=1;i<n;i++){
        int nxt=-1;
        for(int v=1;v<=n;v++){
            if(!used[v] && adj[cur][v]){ nxt=v; break; }
        }
        if(nxt==-1){ cout << -1 << "\n"; return 0; }
        used[nxt]=1; path.push_back(nxt); cur=nxt;
    }
    for(int i=0;i<n;i++){
        if(i) cout<<' ';
        cout<<path[i];
    }
    cout<<"\n";
    return 0;
}
