#include <bits/stdc++.h>
using namespace std;

int n, m;
bool adj[15][15];
vector<int> path;
bool used[15];
bool found = false;

void dfs(int u, int cnt) {
    if (found) return;
    if (cnt == n) {
        for (int i = 0; i < n; i++) cout << path[i] << " ";
        cout << "\n";
        found = true;
        return;
    }

    for (int v = 1; v <= n; v++) {
        if (!used[v] && adj[u][v]) {
            used[v] = true;
            path.push_back(v);
            dfs(v, cnt + 1);
            path.pop_back();
            used[v] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }

    for (int start = 1; start <= n && !found; start++) {
        path.clear();
        memset(used, false, sizeof(used));
        used[start] = true;
        path.push_back(start);
        dfs(start, 1);
    }

    if (!found) cout << -1 << "\n";
    return 0;
}
