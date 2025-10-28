// bug_bruteforce_tle.cpp
#include <bits/stdc++.h>
using namespace std;
// Bruteforce permutations without pruning -> TLE on n=12 worst-case
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<vector<int>> adj(n+1, vector<int>(n+1,0));
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v; adj[u][v]=adj[v][u]=1;
    }
    vector<int> perm(n);
    for(int i=0;i<n;i++) perm[i]=i+1;
    do {
        bool ok=true;
        for(int i=0;i<n-1;i++){
            if(!adj[perm[i]][perm[i+1]]){ ok=false; break; }
        }
        if(ok){
            for(int i=0;i<n;i++){
                if(i) cout<<' ';
                cout<<perm[i];
            }
            cout<<"\n";
            return 0;
        }
    } while(next_permutation(perm.begin(), perm.end()));
    cout << -1 << "\n";
    return 0;
}
