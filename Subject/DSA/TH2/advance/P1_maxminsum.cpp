#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""
int Pow(int k, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1ll * res * k % MOD;
        k = 1ll * k * k % MOD;
        n >>= 1;
    }
    return res;
}
int fact[MAX], frac[MAX];
void BuildComb() {
    fact[0] = 1;
    for (int i = 1; i <= 1e5; i ++) {
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    }
    frac[(int)1e5] = Pow(fact[(int)1e5], MOD - 2);
    for (int i = 1e5; i >= 1; i --) {
        frac[i - 1] = 1ll * frac[i] * i % MOD;
    }
}

int C(int k, int n) {
    if (k > n) return 0;
    return 1ll * fact[n] * frac[k] % MOD * frac[n - k] % MOD;    
}

int n, k;

int numdistinct;
ii a[MAX];


void init() {
    cin >> n >> k;

    map<int, int> mp;
    for (int i = 1; i <= n; i ++) {
        int num; cin >> num;
        mp[num] ++;
    }

    for (ii x : mp) {
        a[++ numdistinct] = x;
    }
}

void process() {
    ll ans(0);
    int cntl = 0, cntr = n;
    for (int i = 1; i <= numdistinct; i ++) {
        cntr -= a[i].se;
        
        for (int j = 1; j <= min(a[i].se, k); j ++) {
            (ans -= 1LL * a[i].fi * C(j, a[i].se) % MOD * C(k - j, cntr) % MOD) %= MOD;   
            (ans += 1LL * a[i].fi * C(j, a[i].se) % MOD * C(k - j, cntl) % MOD) %= MOD;   
        }

        cntl += a[i].se;
    }

    if (ans < 0) ans += MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    
    init();
    BuildComb();
    process();

    return 0;
}