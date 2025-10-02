#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen("tinhtayba.inp", "r", stdin);
//    freopen("tinhtayba.out", "w", stdout);

    ll n(1);
    int m; cin >> m;
    while (m --) {
        int x; cin >> x;
        n *= x;
    }

    ll ans(1);
    for (ll x = 2; x * x <= n; x ++) if (n % x == 0) {
        (ans *= x) %= MOD;
        if (x != n / x) (ans *= n / x) %= MOD;
    }
    cout << ans;
}
