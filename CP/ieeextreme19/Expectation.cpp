#include<bits/stdc++.h>
using namespace std;
using ld = long double;

const int MAX = 5e5 + 7;
const int MASK = (1 << 10);
int n, k;
int a[MAX];
ld dp[2][MASK];

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    ld numway = 1;
    int p = 0;
    for (int i = 1; i <= n; i ++) {
        numway *= 2;
        p = !p;
        
        for (int mask = 0; mask < MASK; mask ++) dp[p][mask] = 0;
        if (numway > 0) dp[p][a[i]] = a[i] / numway;
        cout << dp[p][a[i]] << endl;
        for (int mask = 0; mask < MASK; mask ++) {
            dp[p][mask] += (dp[!p][mask] + dp[!p][mask ^ a[i]] / (ld)mask * (ld)a[i]) / 2.0;
            // if (dp[p][mask] > 0) cout << mask << ' ' << dp[p][mask] << endl;
            // cout << dp[p][mask];
        }
    }

    ld ans(0);
    for (int i = 0; i < MASK; i ++) ans += pow(dp[p][i], k);
    cout << fixed << setprecision(2) << ans;
}