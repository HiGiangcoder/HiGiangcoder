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
const int MAX = 2e5 + 7;

void prepare() {_multi_test = true;}

int n;
int a[MAX];
int b[MAX];

bool used[MAX];
int pairOfA[MAX];

bool FindPair(int u) {
    for (int v = u - 1; v <= u + 1; v += 2) if (1 <= v && v <= n && !used[v] && a[v]) {
        bool ok = true;

        if (pairOfA[v] != 0) {
            used[v] = true;
            ok = FindPair(pairOfA[v]);
            used[v] = false;
        }

        if (ok) {
            pairOfA[v] = u;
            return true;
        }
    }
    return false;
}

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        char c; cin >> c; 
        a[i] = c == '1';
    }
    for (int i = 1; i <= n; i ++) {
        char c; cin >> c;
        b[i] = c == '1';
    }

    int ans(0);

    for (int i = 1; i <= n; i ++) if (b[i] > a[i]) {
        b[i] = 0;
        ans ++;
    }

    for (int i = 1; i <= n; i ++) pairOfA[i] = 0;

    for (int i = 1; i <= n; i ++) if (b[i]) FindPair(i);

    for (int i = 1; i <= n; i ++) if (pairOfA[i]) ans ++;
    cout << ans << '\n';
}


