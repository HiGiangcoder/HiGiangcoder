#include <bits/stdc++.h>
using namespace std;

int a[15][105];
int n, m, k;

void process() {
    memset(a, 0, sizeof(a));
    cin >> n >> m >> k;

    while (k--) {
        int x, y;
        string s;
        cin >> x >> y >> s;
        a[x - 1][y - 1] = 1;
        a[x - 1][y] = 1;
        a[x][y - 1] = 1;
        a[x][y] = 1;
    }

    int cnt(0);
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (a[i][j] == 0)
                cnt++;
        }
    }

    int ans(1);
    int mod = 1e9 + 7;

    for (int i = 1; i <= cnt; i++) {
        ans *= 2;
        ans %= mod;
    }

    cout << ans << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        process();
    }

    return 0;
}
