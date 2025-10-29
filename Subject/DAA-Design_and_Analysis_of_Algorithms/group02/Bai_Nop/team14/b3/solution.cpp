#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }

    int FULL = (1 << n) - 1;
    vector<vector<char>> dp(1 << n, vector<char>(n, 0));
    vector<vector<int>> par(1 << n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) dp[1 << i][i] = 1;

    bool exist = false;
    int endv = -1;

    for (int mask = 1; mask <= FULL; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (!dp[mask][last]) continue;
            if (mask == FULL) {
                exist = true;
                endv = last;
                break;
            }
            for (int nxt = 0; nxt < n; ++nxt) {
                if (mask & (1 << nxt)) continue;
                if (adj[last + 1][nxt + 1]) {
                    int nmask = mask | (1 << nxt);
                    if (!dp[nmask][nxt]) {
                        dp[nmask][nxt] = 1;
                        par[nmask][nxt] = last;
                    }
                }
            }
        }
        if (exist) break;
    }

    if (!exist) {
        cout << -1 << "\n";
        return 0;
    }

    // reconstruct path
    vector<int> path;
    int mask = FULL;
    int cur = endv;
    while (cur != -1) {
        path.push_back(cur + 1);
        int prev = par[mask][cur];
        mask ^= (1 << cur);
        cur = prev;
    }

    reverse(path.begin(), path.end());
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
