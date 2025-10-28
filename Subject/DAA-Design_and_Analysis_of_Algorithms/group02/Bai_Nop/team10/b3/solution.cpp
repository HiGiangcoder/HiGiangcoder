#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> path;
vector<bool> visited;

bool dfs(int u, int depth) {
    path[depth] = u;
    if (depth == n - 1) return true;
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfs(v, depth + 1)) return true;
        }
    }
    visited[u] = false;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    adj.assign(n + 1, {});
    path.assign(n, 0);
    visited.assign(n + 1, false);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int start = 1; start <= n; start++) {
        fill(visited.begin(), visited.end(), false);
        if (dfs(start, 0)) {
            for (int i = 0; i < n; i++) {
                cout << path[i] << (i + 1 == n ? '\n' : ' ');
            }
            return 0;
        }
    }
    cout << -1 << '\n';
}
