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

vector<vector<int>> path[MAX];
void PreDfs(int u, int p, vector<int> vec = vector<int>()) {
    vec.push_back(style[u]);
    path[u].push_back(vec);

    for (int v : adj[u]) if (v != p) {
        PreDfs(v, u, vec);
    }
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
    
    for (int i = 1; i <= n; i ++) PreDfs(i, i);

    while (q --) {
        int u;
        string s;
        cin >> u >> s;

        int mask = 0;
        int len = s.length();

        vector<int> pathQuery;
        for (int i = 0; i < len; i ++) pathQuery.push_back(s[i] == 'B');

        int ans(0);
        for (const vector<int> &vec : path[u]) {

            for (int mask = 0; mask < BIT(vec.size()); mask ++) {
                bool ok = true;
                int j(0);
                for (int i = 0; i < vec.size(); i ++) if (GETBIT(mask, i)) {
                    if (j < pathQuery.size() && vec[i] == pathQuery[j]) {
                        j ++;
                    }
                    else {
                        ok = false;
                        break;
                    }
                }
                if (ok && j == pathQuery.size()) ans ++;
            }
        }

        cout << ans << '\n';
    }
}
