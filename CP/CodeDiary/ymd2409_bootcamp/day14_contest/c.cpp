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
const int MAX = 300 + 7;

void prepare() {_multi_test = false;}

int n;
ll sInit[MAX], velocity[MAX];

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> sInit[i] >> velocity[i];
    }

    ll ans(min(2, n));

    for (int u = 1; u <= n; u ++) {
        for (int v = u + 1; v <= n; v ++) {
            ll S = sInit[v] - sInit[u];
            ll V = velocity[v] - velocity[u];
            ll distA = v - u;

            map<pll, ll> mp;

            for (int i = v + 1; i <= n; i ++) {
                ll curS = sInit[i] - sInit[u];
                ll curV = velocity[i] - velocity[u];
                ll distB = i - u;

//                (S + V * t) * B = (curS + curV * t) * A
//                (V*B - curV*A)*t = curS * A - S * B
//
                ll x = curS * distA - S * distB;
                ll y = V * distB - curV * distA;
                ll tmpgcd = __gcd(x, y);
                if (tmpgcd != 0) x /= tmpgcd, y /= tmpgcd;
                else {
                    if (x != 0) x = 1;
                    if (y != 0) y = 1;
                }
                mp[make_pair(x, y)] ++;
                ll res = mp[make_pair(x, y)];
                maximize(ans, res + 2);
            }
        }
    }

    cout << ans;
}

