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

int n, m, q;
int s[MAX];
int a[MAX];

int fw[MAX];
void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx) fw[idx] += val;
}
int get(int idx) {
    int res(0);
    for (; idx >= 1; idx -= idx & -idx) res += fw[idx];
    return res;
}

void process() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i ++) {
        char c; cin >> c;
        s[i] = c - '0';
    }

    set<int> numSet;
    for (int i = 1; i <= n; i ++) {
        numSet.insert(i);
        a[i] = n + 1;
    }

    while (m --) {
        int l, r; cin >> l >> r;
        while (true) {
            set<int> :: iterator x = numSet.lower_bound(l);
            if (x == numSet.end() || *x > r) break;
            int num = *x;
            numSet.erase(x);
            a[num] = n - numSet.size();
        }
    }

    int len(0);
    for (int i = 1; i <= n; i ++) {
        if (s[i] == 0) update(a[i], 1);
        else len ++;
    }

    while (q --) {
        int x; cin >> x;

        if (s[x] == 0) {
            s[x] = 1;
            len ++;
            update(a[x], -1);
        }
        else {
            s[x] = 0;
            len --;
            update(a[x], 1);
        }

        cout << get(len) << '\n';
    }
}

