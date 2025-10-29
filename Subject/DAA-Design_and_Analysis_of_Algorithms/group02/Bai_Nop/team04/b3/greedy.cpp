#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++deg[u];
        ++deg[v];
    }

    vector<int> visited(n + 1, 0);
    vector<int> path;
    int start = 1;
    visited[start] = 1;
    path.push_back(start);

    while ((int)path.size() < n) {
        int u = path.back();
        vector<int> cand;
        for (int v : adj[u]) if (!visited[v]) cand.push_back(v);
        if (cand.empty()) {
            cout << -1 << '\n';
            return 0;
        }
        sort(cand.begin(), cand.end(), [&](int a, int b) {
            if (deg[a] != deg[b]) return deg[a] > deg[b];
            return a < b;
        });
        int v = cand[0];
        visited[v] = 1;
        path.push_back(v);
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
