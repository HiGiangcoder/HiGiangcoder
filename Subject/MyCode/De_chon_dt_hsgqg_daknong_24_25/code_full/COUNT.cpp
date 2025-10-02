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

#define TASK "COUNT" 

bool _multi_test(0);

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".INP", "r")) {
        freopen(TASK".INP", "r", stdin);
        freopen(TASK".OUT", "w", stdout);
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

const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int MAX = 1e4 + 7;
const int MAXLEN = 8;

int n, k, q;
int style[MAX];
vector<int> adj[MAX];

void prepare() {_multi_test = false;}

int dp[MAX][MAXLEN + 1][BIT(MAXLEN)];
int ans[MAX][MAXLEN + 1][BIT(MAXLEN)];

void Add(int &x, const int &y) {
    x += y;
    if (x >= MOD) x -= MOD;
    if (x < 0) x += MOD;
}

void FastCalc(int u, int v, int sign) {
    for (int len = 0; len <= MAXLEN; len ++) {
        for (int mask = 0; mask < BIT(len); mask ++) if (dp[v][len][mask] != 0) {
            if (len < MAXLEN) {
                int newmask = (mask << 1) | style[u];
                Add(dp[u][len + 1][newmask], sign * dp[v][len][mask]);
            }
            Add(dp[u][len][mask], sign * dp[v][len][mask]);
        }
    }
}

void PreDfs(int u, int p) {
    dp[u][0][0] = dp[u][1][style[u]] = 1;

    for (int v : adj[u]) if (v != p) {
        PreDfs(v, u);
        FastCalc(u, v, 1);
    }
}

void AllRootDfs(int u, int p) {
    if (p != u)  FastCalc(u, p, 1);

    for (int len = 0; len <= 8; len ++) {
        for (int mask = 0; mask < BIT(len); mask ++) {
            ans[u][len][mask] = dp[u][len][mask];
        }
    }

    for (int v : adj[u]) if (v != p) {
        FastCalc(u, v, -1);
        AllRootDfs(v, u);
        FastCalc(u, v, 1);
    }
    if (p != u)  FastCalc(u, p, -1);
}

void process() {
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) {
        char c; cin >> c;
        style[i] = c == 'B';
    }

    REP(rep, n - 1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    PreDfs(1, 1);
    AllRootDfs(1, 1);

    while (q --) {
        int u;
        string s;
        cin >> u >> s;

        int mask = 0;
        int len = s.length();

        for (int i = 0; i < len; i ++) mask = (mask << 1) | (s[i] == 'B');
        cout << ans[u][len][mask] << '\n';
    }
}