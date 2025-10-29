#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long
#define fi first
#define se second
#define fre(A) freopen(A".inp","r",stdin); freopen(A".out","w",stdout);
#define ii pair<ll,ll>
#define int long long
#define mp make_pair
#define vt vector
const int N = 2e5 + 1;
const ll mod = 1e9 + 7;
 
vt<ii> Nodes[N];
ll dist[N];
priority_queue<ii> q;
 
int n, m;
void input(){
    cin >> n >> m;
    int u, v, c;
    while(m--){
        cin >> u >> v >> c;
        Nodes[u].push_back({v, c});
    }
}
 
void dijk(int st){
    q.push({0, st});
    dist[st] = 0;
    int u;
    while(!q.empty()){
        u = q.top().se; q.pop();
        for(ii v : Nodes[u])
            if(dist[v.fi] > dist[u] + v.se){
                dist[v.fi] = dist[u] + v.se;
                q.push({ -dist[v.fi], v.fi });
            }
    }
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //fre("t");
    memset(dist, 0x3f, sizeof dist);
    ll wa = dist[1];
    input();
    dijk(1);

    if(dist[n] >= wa) return cout << -1, 0;
    cout << dist[n];
 
    return 0;
}