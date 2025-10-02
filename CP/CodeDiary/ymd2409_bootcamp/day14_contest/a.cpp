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

void prepare() {_multi_test = false;}

ll n, k;
ll a[MAX];

ll SumRange(ll u, ll v) {
    return (u + v) * (v - u + 1) / 2;
}

void process() {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) cin >> a[i];

    sort(a + 1, a + 1 + n);
    
    if (n == 1) {
        minimize(k, a[1]);
        cout << SumRange(a[1] - k + 1, a[1]);
    }
    else {
        ll u = a[n];
        ll v = a[n - 1];
        ll ans(0);

        if (u != v) {
            if (k >= (u - v + 1)) {
                ll cnt = k / (u - v + 1);
                ans += cnt * SumRange(v, u);;
                k -= cnt * (u - v + 1);
            }
            ans += SumRange(u - k + 1, u);
        } else {
            ans = u * k;
        }

        cout << ans;
    }
}

