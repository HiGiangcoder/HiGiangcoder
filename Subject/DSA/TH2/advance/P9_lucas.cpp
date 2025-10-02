#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

int MOD;
const ll MAX = 1e5 + 5;

#define TASK ""

int fact[MAX], frac[MAX];
int Pow(int k, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1ll * res * k % MOD;
        k = 1ll * k * k % MOD;
        n >>= 1;
    }
    return res;
}
void prepare() {
    fact[0] = 1;
    for (int i = 1; i < MOD; i ++) {
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    }
    frac[MOD - 1] = Pow(fact[MOD - 1], MOD - 2);

    for (int i = MOD - 1; i >= 1; i --) {
        frac[i - 1] = 1ll * frac[i] * i % MOD;
    } 
}

int _C(int k, int n) {
    if (k > n) return 0;
    return 1ll * fact[n] * frac[k] % MOD * frac[n - k] % MOD;
}
int C(ll k, ll n) {
    ll res = 1;
    while (k > 0 && n > 0) {
        int a = k % MOD, b = n % MOD;
        k /= MOD; n /= MOD;

        (res *= _C(a, b)) %= MOD;
    }
    return res;
}

int K(ll k, ll n) {
    return C(k, n + k - 1);
}

ll n;
void process() {
    cout << K(n, n) << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    int t; cin >> t >> MOD;

    prepare();
    while (t --) {
        cin >> n;
        process();
    }

    
    return 0;
}