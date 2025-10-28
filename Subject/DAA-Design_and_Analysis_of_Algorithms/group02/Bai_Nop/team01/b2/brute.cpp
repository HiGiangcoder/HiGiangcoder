#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n, m;
vector<pair<int, int>> adj[MAXN + 36];

long long Dfs(int u, vector<bool>& visited) {
    if (u == n) return 0;
    visited[u] = true;
    long long ret = 1e16;
    for (auto [v, w] : adj[u]) {
        if (!visited[v]) {
            ret = min(ret, Dfs(v, visited) + w);
        }
    }
    visited[u] = false;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for(int i = 1; i <= m;i ++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    vector<bool> visited(n + 1, false);
    long long res = Dfs(1, visited);
    cout << (res == 1e16 ? -1 : res) << '\n';

    return 0;
}
