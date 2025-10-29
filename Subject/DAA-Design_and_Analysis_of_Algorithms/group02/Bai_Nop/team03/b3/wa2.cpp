// bug_unsigned.cpp
#include <bits/stdc++.h>
using namespace std;
// misuse of unsigned in loops -> infinite loop or wrong mask arithmetic
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<vector<int>> adj(n+1, vector<int>(n+1,0));
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        adj[u][v]=adj[v][u]=1;
    }
    // flawed loop with unsigned
    vector<int> order;
    for(unsigned int i = n; i >= 1; --i){ // BUG: when i is unsigned, loop may not terminate
        order.push_back((int)i);
        if(i==1) break;
    }
    // print order as candidate path if connected
    vector<int> seen(n+1,0);
    int cnt=0;
    for(int x: order){
        if(!seen[x]){ seen[x]=1; cnt++; }
    }
    if(cnt==n){
        for(int i=0;i<n;i++){
            if(i) cout << ' ';
            cout << order[i];
        }
        cout<<"\n";
    } else cout << -1 << "\n";
    return 0;
}
