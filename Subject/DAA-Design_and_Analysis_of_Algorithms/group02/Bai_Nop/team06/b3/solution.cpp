#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 3, vector<int>(n + 6));
    for(int i = 0; i < m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u-1][v-1] = 1;
        adj[v-1][u-1] = 1;
    }
    int N = 1 << n;
    vector<vector<int>> parent(N, vector<int>(n, -1));
    vector<vector<bool>> dp(N, vector<bool>(n, false));

    for (int i = 0; i < n; i++)
        dp[1 << i][i] = true;

    for (int mask = 1; mask < N; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            if (!dp[mask][u]) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue; 
                if (!adj[u][v]) continue;      
                dp[mask | (1 << v)][v] = true;
                parent[mask | (1 << v)][v] = u;
            }
        }
    }

    int end = -1;
    int full = N - 1;
    for (int u = 0; u < n; u++) {
        if (dp[full][u]) {
            end = u;
            break;
        }
    }

    if (end == -1) {
        cout << -1;
        return 0;
    }

    vector<int> path;
    int mask = full, u = end;
    while (u != -1) {
        path.push_back(u);
        int pu = parent[mask][u];
        mask ^= (1 << u);
        u = pu;
    }
    reverse(path.begin(), path.end());

    for (int x : path)
        cout << x + 1 << " ";

    return 0;
}
