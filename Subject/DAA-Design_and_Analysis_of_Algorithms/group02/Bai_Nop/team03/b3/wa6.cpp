// bug_bad_index_usage.cpp
#include <bits/stdc++.h>
using namespace std;
// Declares arrays of size n but uses indexes 1..n inclusive incorrectly
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<int> deg(n); // should be n+1
    vector<vector<int>> g(n, vector<int>(n,0)); // should be n+1
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        if(u< (int)g.size() && v < (int)g.size()) {
            g[u][v]=g[v][u]=1;
            if(u < (int)deg.size()) deg[u]++; // may skip last
            if(v < (int)deg.size()) deg[v]++;
        }
    }
    // naive: if all deg>0 print 1..n
    for(int i=1;i<=n;i++){
        if(i>1) cout<<' ';
        cout<<i;
    }
    // cout<<"\n";
    return 0;
}
