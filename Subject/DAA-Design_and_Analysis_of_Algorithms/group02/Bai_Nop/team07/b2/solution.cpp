#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int nMax = 100000;
const ll INF = 1e18;

int n, m;
vector<pair<ll, ll>> adj[nMax + 5];
ll dis[nMax + 5];

ll dijkstra(int s, int t){
    for (int i=1;i<= n;i++ )
        dis[i] = INF;
    priority_queue<pair<ll, ll>> myQ;
    while (!myQ.empty())    myQ.pop();
        
    dis[s] = 0;
    myQ.push({0, s});
    
    while (!myQ.empty()){
        ll u = myQ.top().second;
        ll d = -myQ.top().first;
        myQ.pop();

        if (d > dis[u]) continue;

        for (pair<ll, ll> it : adj[u]){ 
            ll v = it.first;
            ll w = it.second;
            if (dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                myQ.push({-dis[v], v});
            }
        }
    }

    return (dis[t] != INF ? dis[t] : -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i=1;i<= m;i++ ){
        ll u, v, w;    cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    cout << dijkstra(1, n);
}
