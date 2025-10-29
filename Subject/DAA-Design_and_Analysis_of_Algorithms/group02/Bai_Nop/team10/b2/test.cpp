#include <bits/stdc++.h>
using namespace std;
#define pii pair < int , int >
#define INF INT_MAX

int n , m;
vector < vector < pii >> adj;
vector<int> trace;
vector < int > dist;
priority_queue < pii , vector < pii > , greater < pii> > pq;

void dij (int s)
{
    dist.assign(n + 1, INF);
    trace.assign(n + 1, -1);
    dist[s] = 0;
    trace[s] = -1;
    while (!pq.empty()) pq.pop();

    pq.push({0,s});
    while (!pq.empty())
    {
        pii top = pq.top();
        pq.pop();
        int d = top.first;
        int u = top.second;
        if (d > dist[u]) continue;
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                trace[v] = u;
                pq.push({dist[v] , v});
            }
        }
    }
}
void truyvet(int x)
{
    if (dist[x] == INF)
    {
        cout << -1;
        return;
    }
    vector < int > tv;
    int j = x;
    while (j != -1)
    {
        tv.push_back(j);
        j = trace[j];
    }
    reverse(tv.begin(), tv.end());
    for (int o = 0; o < tv.size(); o ++)
        cout << tv[o] << " ";
}

int main()
{
    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 1; i <= m; i++)
    {
        int u , v , w;
        cin >> u >> v >> w;
        adj[u].push_back({v , w});
        adj[v].push_back({u , w});
    }
    dij(1);
    if (dist[n]==INF)
    {
        cout << -1;
        return 0;
    } else
    cout << dist[n] << endl;
    // truyvet(n);

}