#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int N = 1 << n;
    vector<vector<bool>> dp(N, vector<bool>(n, false));
    vector<vector<int>> parent(N, vector<int>(n, -1));

    // Khởi tạo
    for (int i = 0; i < n; i++) dp[1 << i][i] = true;

    // DP
    for (int mask = 1; mask < N; mask++) {
        for (int u = 0; u < n; u++) {
            if (!dp[mask][u]) continue;
            for (int v : adj[u]) {
                if (mask & (1 << v)) continue; // v đã đi rồi
                int nmask = mask | (1 << v);
                if (!dp[nmask][v]) {
                    dp[nmask][v] = true;
                    parent[nmask][v] = u;
                }
            }
        }
    }

    int full = N - 1;
    int last = -1;
    for (int u = 0; u < n; u++) {
        if (dp[full][u]) {
            last = u;
            break;
        }
    }

    if (last == -1) {
        cout << -1 << "\n";
        return 0;
    }

    // Truy vết
    vector<int> path;
    int mask = full;
    while (last != -1) {
        path.push_back(last);
        int prev = parent[mask][last];
        mask ^= (1 << last);
        last = prev;
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < n; i++) {
        cout << path[i] + 1 << (i + 1 == n ? '\n' : ' ');
    }
}
