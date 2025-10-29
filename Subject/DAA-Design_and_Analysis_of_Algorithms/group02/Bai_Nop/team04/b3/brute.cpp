#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }
    vector<vector<int>> adj(n);
    vector<vector<bool>> hasEdge(n, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        if (!hasEdge[u][v]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            hasEdge[u][v] = hasEdge[v][u] = true;
        }
    }

    vector<int> path;
    vector<int> answer;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    bool found = false;

    function<void(int, int)> dfs = [&](int u, int mask) {
        if (found) return;
        if ((int)path.size() == n) {
            answer = path;
            found = true;
            return;
        }
        for (int v : adj[u]) {
            if (mask & (1 << v)) continue;
            path.push_back(v);
            dfs(v, mask | (1 << v));
            path.pop_back();
            if (found) return;
        }
    };

    for (int start : order) {
        path.clear();
        path.push_back(start);
        dfs(start, 1 << start);
        if (found) break;
    }

    if (!found) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << answer[i] + 1;
    }
    cout << '\n';
    return 0;
}

