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

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".INP", "r")) {
        freopen(TASK".INP", "r", stdin);
        freopen(TASK".OUT", "w", stdout);
    }

    process();

    return 0;
}

/* ---------------------------------------------------------------------------*/
/* ----------------------- author: Nguyen Truong Giang -----------------------*/
/* ---------------------------------------------------------------------------*/

const int MOD = 1e9 + 2277;
// const int MOD = 998244353
const int inf = 0x3f3f3f3f;
const int MAX = 2e3 + 7;

int numNode;
int color[MAX];
vector<int> adj[MAX];

void Add(int &a, const int &b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

ii dp[MAX][MAX];
void Upd(int u, int v, int val, int numkey) {
    if (dp[u][v].se != numkey) {
        dp[u][v].fi = 0;
        dp[u][v].se = numkey;
    }
    dp[u][v].fi = val;
}
int &Get(int u, int v, int numkey) {
    if (dp[u][v].se != numkey) {
        dp[u][v].fi = 0;
        dp[u][v].se = numkey;
    }
    return dp[u][v].fi;
}

void AddDp(int u, int v, int val, int numkey) {
    if (dp[u][v].se != numkey) {
        dp[u][v].fi = 0;
        dp[u][v].se = numkey;
    }
    Add(dp[u][v].fi, val);
}

struct NumDp {
    int u, v;
    int val;
    NumDp() {}
    NumDp(int _u, int _v, int _val) : u(_u), v(_v), val(_val) {}
}; vector<NumDp> numdp[MAX];

int ans(0);

int sz[MAX];
void predfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) if (v != p) {
        sz[u] += sz[v];
    }
}

void dfs(int u, int p) {
    vector<ii> tmp;
    for (int v : adj[u]) {
        tmp.push_back({sz[v], v});
    }
    sort(tmp.begin(), tmp.end());


    for (int v : adj[u]) if (v != p) {
        dfs(v, u);
    }

    Upd(color[u] == 0, color[u] == 1, 1, u);
    for (ii _tmp : tmp) {
        int v = _tmp.se;
        for (int i = numNode; i >= 0; i --) {
            for (int j = numNode; j >= 0; j --) if (Get(i, j, u) != 0) {
                for (NumDp val : numdp[v]) {
                    AddDp(i + val.u, j + val.v, 1LL * Get(i, j, u) * val.val % MOD, u);
                }
            }
        }
    }

    for (int i = 0; i <= numNode; i ++) {
        for (int j = 0; j <= numNode; j ++) if (Get(i, j, u) != 0 && i + j != 0) {
            numdp[u].push_back(NumDp(i, j, Get(i, j, u)));

            if (i == j && i + j != 0) Add(ans, Get(i, j, u));
        }
    }
}

void process() {
    cin >> numNode;
    for (int i = 1; i <= numNode; i ++) cin >> color[i];
    for (int i = 1; i <= numNode - 1; i ++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    predfs(1, 1);
    dfs(1, 1);

    cout << ans;
}

