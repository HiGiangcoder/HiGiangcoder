#include<bits/stdc++.h>
#define fi first
#define se second

using namespace std;
typedef pair<int, int> ii;

const int MOD = 1e9 + 7;
const int MAX = 2e5 + 7;

int n;
ii a[MAX];

void Input() {
    int m;
    map<int, int> mp;
    cin >> m;
    while (m --) {
        int x; cin >> x;
        mp[x] ++;
    }

    for (ii x : mp) a[++n] = x;
}

int Pow(int k, int n) {
    int ans(1);
    while (n > 0) {
        if (n & 1) ans = 1LL * ans * k % MOD;
        k = 1LL * k * k % MOD;
        n >>= 1;
    }
    return ans;
}

int fLeft[MAX];
int fRight[MAX];

void Solve() {
    fLeft[0] = fRight[n + 1] = 1;
    for (int i = 1; i <= n; i ++) {
        fLeft[i] = 1LL * (a[i].se + 1) * fLeft[i - 1] % (MOD - 1);
    }
    for (int i = n; i >= 1; i --) {
        fRight[i] = 1LL * (a[i].se + 1) * fRight[i + 1] % (MOD - 1);
    }

    int ans(1);
    for (int i = 1; i <= n; i ++) {
        int num(1);
        for (int j = 1; j <= a[i].se; j ++) {
            num = 1LL * num * a[i].fi % MOD;
            ans = 1LL * ans * Pow(num, 1LL * fLeft[i - 1] * fRight[i + 1] % (MOD - 1)) % MOD;
        }
    }

    cout << ans;
}

int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);

    freopen("TINHTAYBA.INP", "r", stdin);
    freopen("TINHTAYBA.OUT", "w", stdout);

    Input();
    Solve();
}
