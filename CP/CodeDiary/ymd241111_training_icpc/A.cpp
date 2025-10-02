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
const int MAX = 1e5 + 7;

void prepare() {_multi_test = true;}

int n;
vector<int> adj[MAX];
int statu[MAX];
int dp[MAX][3];

void dfs(int u) {
    REP(k, 3) {
        if (statu[u] == k || statu[u] == 2) dp[u][k] = 0;
        else dp[u][k] = inf;
    }

    for (int v : adj[u]) {
        dfs(v);

        dp[u][2] += min({dp[v][2], dp[v][0] + 1, dp[v][1] + 1});
        dp[u][1] += min({dp[v][1], dp[v][2], dp[v][0] + 1});
        dp[u][0] += min({dp[v][0], dp[v][2], dp[v][1] + 1});
    }
}

void process() {
    cin >> n;
    for (int i = 2; i <= n; i ++) {
        int p; cin >> p;
        adj[p].push_back(i);
    }

    for (int i = 1; i <= n; i ++) {
        char c; cin >> c;
        if (c == 'P') statu[i] = 0;
        if (c == 'S') statu[i] = 1;
        if (c == 'C') statu[i] = 2;
    }


    dfs(1);

    cout << min({dp[1][0], dp[1][1], dp[1][2]}) << '\n';

    for (int i = 1; i <= n; i ++) adj[i].clear();
}

