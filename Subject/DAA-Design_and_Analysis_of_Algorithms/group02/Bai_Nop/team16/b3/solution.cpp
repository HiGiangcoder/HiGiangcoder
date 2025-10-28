#include <bits/stdc++.h>
using namespace std;

const int maxn = 12;
int dp[maxn][1 << maxn];
int trace[maxn][1 << maxn];
bool edge[maxn][maxn];
int n, m;

int recur(int i, int mask) {
    if (mask == (1 << n) - 1) return 1;
    if (dp[i][mask] != -1) return dp[i][mask];
    dp[i][mask] = 0;
    for (int j = 0; j < n; ++j) {
        if (mask & (1 << j)) continue;
        if (edge[i][j]) {
            int res = recur(j, mask | (1 << j));
            if (res == 1) {
                dp[i][mask] = 1;
                trace[i][mask] = j;
                break;
            }
        }
    }
    return dp[i][mask];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edge[u - 1][v - 1] = edge[v - 1][u - 1] = 1;
    }

    for (int i = 0; i < n; ++i) {
        if (recur(i, 1 << i) == 1) {
            int cur = i;
            int mask = 1 << cur;
            cout << cur + 1 << ' ';
            while (mask != (1 << n) - 1) {
                int nxt = trace[cur][mask];
                cout << nxt + 1 << ' ';
                mask |= 1 << nxt;
                cur = nxt;
            }
            return 0;
        }
    }
    cout << -1;
    return 0;
}
