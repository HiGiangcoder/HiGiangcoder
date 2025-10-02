/* Medium-Codeforces tempalte*/
#include <bits/stdc++.h>

#define              fi  first
#define              se  second
#define          BIT(x)  (1 << (x))
#define           SZ(x)  (int)((x).size())
#define          ALL(x)  (x).begin(), (x).end()
#define       MEM(f, x)  memset(f, x, sizeof(f))
#define  sort_unique(x)  sort(ALL(x)), (x).resize(unique(ALL(x)) - x.begin())
#define GETBIT(mask, n)  (((mask) >> (n)) & 1)
#define       REP(i, n)  for (int i = 0, _n = (n); i < _n; i ++)
#define    FOR(i, l, r)  for (int i = (l), _r = (r); i <= _r; i ++)
#define   FORD(i, r, l)  for (int i = (r), _l = (l); i >= _l; i --)

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef long double ld;
template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

void prepare();
void process();

#define TASK "" 

bool _multi_test = true;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    prepare();
    int t = 1; 
    if (_multi_test) cin >> t;
    while (t --)
        process();

    return 0;
}

/* ---------------------------------------------------------------------------*/
/* ----------------------- author: Nguyen Truong Giang -----------------------*/
/* ---------------------------------------------------------------------------*/

const int MOD = 1e9 + 7;
// const int MOD = 998244353
const int inf = 0x3f3f3f3f;
const int MAX = 2e5 + 7;

int Pow(int k, int n) {
    int res(1);
    while (n > 0) {
        if (n & 1) res = 1LL * res * k % MOD;
        k = 1LL * k * k % MOD;
        n >>= 1;
    }
    return res;
}

int fact[MAX], frac[MAX];
void prepare() {_multi_test = false;
    fact[0] = 1;
    for (int i = 1; i <= 2e5; i ++) fact[i] = 1LL * fact[i - 1] * i % MOD;
    frac[int(2e5)] = Pow(fact[int(2e5)], MOD - 2);
    for (int i = 2e5; i >= 1; i --) frac[i - 1] = 1LL * frac[i] * i % MOD;
}

int C(int k, int n) {
    if (k > n) return 0;
    return 1LL * fact[n] * frac[n - k] % MOD * frac[k] % MOD;
}

int n, numk;
vector<int> adj[MAX];

void add(int &x, const int &y) {
    x += y;
    if (x >= MOD) x -= MOD;
    if (x < 0) x += MOD;
}

int sz[MAX];
void predfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) if (v != p) {
        predfs(v, u);
        sz[u] += sz[v];
    }
}

int ans(0);
void dfs(int u, int p) {
    int sumv(0);
    for (int v : adj[u]) add(sumv, C(numk, sz[v]));

    int tmpway = C(numk, n);
    add(tmpway, -sumv);

    add(ans, 1LL * tmpway * n % MOD);

    for (int v : adj[u]) {
        add(sumv, -C(numk, sz[v]));

        int numway = C(numk, n - sz[v]);
        add(numway, -sumv);

        add(ans, 1LL * numway * sz[v] % MOD * (n - sz[v]) % MOD);

        add(sumv, C(numk, sz[v]));
    }


    for (int v : adj[u]) if (v != p) {
        sz[u] -= sz[v];
        sz[v] += sz[u];

        dfs(v, u);

        sz[v] -= sz[u];
        sz[u] += sz[v];
    }
}

void process() {
    cin >> n >> numk;
    for (int i = 1; i < n; i ++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    predfs(1, 1);
    dfs(1, 1);

    cout << ans;
}

