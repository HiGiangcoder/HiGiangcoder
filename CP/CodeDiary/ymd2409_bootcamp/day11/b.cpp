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

int n;
ii a[MAX];
vector<int> rangeVal;

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i].fi >> a[i].se;
    }

    for (int i = 1; i <= n; i ++) {
        rangeVal.push_back(a[i].fi);
        rangeVal.push_back(a[i].se);
    }
    rangeVal.push_back(0);
    sort(rangeVal.begin(), rangeVal.end());
    rangeVal.resize(unique(rangeVal.begin(), rangeVal.end()) - rangeVal.begin());


    for (int i = 1; i <= n; i ++) {
        a[i].fi = lower_bound(rangeVal.begin(), rangeVal.end(), a[i].fi) - rangeVal.begin();
        a[i].se = lower_bound(rangeVal.begin(), rangeVal.end(), a[i].se) - rangeVal.begin();
    }

    int ans(0);

    for (int mask = 0; mask < BIT(n); mask ++) {
        int res(0);
        int cnt[10 + 7]; memset(cnt, 0, sizeof(cnt));

        for (int i = 1; i <= n; i ++) if (GETBIT(mask, i - 1)) {
            for (int j = a[i].fi; j <= a[i].se; j ++) {
                cnt[j] ++;
            }
        }

        bool ok = true;
        for (int i = 1; i <= 10; i ++) {
            if (cnt[i] >= 10) ok = false;
            if (cnt[i] % 2 == 1) res ++;
        }

        if (ok) maximize(ans, res);
    }
    cout << ans;
}


