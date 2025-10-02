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

const int MOD = 1e9 + 7;
// const int MOD = 998244353
const int inf = 0x3f3f3f3f;
const int MAX = 1e3 + 7;

void prepare() {_multi_test = false;}

int n, m;
ll capa[MAX][MAX], flow[MAX][MAX];
int dist[MAX];
vector<int> adj[MAX];

bool bfs(int s, int t) {
    memset(dist, 0x3f, sizeof(dist));

    queue<int> q; 
    q.push(s);
    dist[s] = 0;

    while (q.size()) {
        int u = q.front(); q.pop();

        for (int v = 1; v <= n; v ++) if (capa[u][v] - flow[u][v] > 0 && minimize(dist[v], dist[u] + 1)) {
                q.push(v);
            }
    }

    return dist[t] <= n;
}

int curVertexId[MAX];

ll dfs(int u, int t, ll flow_val) {
    if (u == t) return flow_val;

    for (; curVertexId[u] < adj[u].size(); curVertexId[u] ++) {
        int v = adj[u][curVertexId[u]];

        if (capa[u][v] - flow[u][v] > 0 && dist[u] + 1 == dist[v]) {
            ll tmp = dfs(v, t, min(flow_val, capa[u][v] - flow[u][v]));
            if (tmp > 0) {
                flow[u][v] += tmp;
                flow[v][u] -= tmp;
                return tmp;
            }
        }
    }
    
    return 0;
}

ll MaxFlow(int s, int t) {
    ll ans(0);

    while (bfs(s, t)) {
        for (int i = 1; i <= n; i ++) curVertexId[i] = 0;

        while (true) {
            ll tmp = dfs(s, t, inf);
            if (tmp == 0) break;
            ans += tmp;
        }
    }

    return ans;
}

void process() {
    int s, t;

    cin >> n >> m >> s >> t;

    for (int i = 1; i <= m; i ++) {
        int u, v, c; cin >> u >> v >> c;
        capa[u][v] += c;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i ++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].resize(unique(adj[i].begin(), adj[i].end()) - adj[i].begin());
    }

    cout << MaxFlow(s, t);
}

