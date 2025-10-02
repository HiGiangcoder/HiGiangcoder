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

const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int MAX = 1e3 + 7;
const int MAXM = 10 + 7;
const int MAXLEN = 3 + 1;

void prepare() {_multi_test = false;}

int n, m;

/// num_array, max_length, last_number
int dp[MAX][MAXM][MAXM][MAXM];

void Add(int &x, const int &y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

void process() {
    cin >> n >> m;
    dp[0][0][0][0] = 1;

    for (int i = 1; i <= n; i ++) {
        for (int dig = 1; dig <= m; dig ++) {
            Add(dp[i][dig][0][0], dp[i - 1][0][0][0]);

            for (int dig1 = 1; dig1 <= m; dig1 ++) {
                if (dig1 < dig) Add(dp[i][dig1][dig][0], dp[i - 1][dig1][0][0]);
                else Add(dp[i][dig][0][0], dp[i - 1][dig1][0][0]);

                for (int dig2 = dig1 + 1; dig2 <= m; dig2 ++) {
                    if (dig2 < dig) Add(dp[i][dig1][dig2][dig], dp[i - 1][dig1][dig2][0]);
                    else if (dig1 < dig) Add(dp[i][dig1][dig][0], dp[i - 1][dig1][dig2][0]);
                    else Add(dp[i][dig][dig2][0], dp[i - 1][dig1][dig2][0]);

                    for (int dig3 = dig2 + 1; dig3 <= m; dig3 ++) {
                        if (dig3 < dig) continue;
                        else if (dig2 < dig) Add(dp[i][dig1][dig2][dig], dp[i - 1][dig1][dig2][dig3]);
                        else if (dig1 < dig) Add(dp[i][dig1][dig][dig3], dp[i - 1][dig1][dig2][dig3]);
                        else Add(dp[i][dig][dig2][dig3], dp[i - 1][dig1][dig2][dig3]);
                    }
                }
            }
        }
    }

    int ans(0);
    for (int dig1 = 1; dig1 <= m; dig1 ++) {
        for (int dig2 = dig1 + 1; dig2 <= m; dig2 ++) {
            for (int dig3 = dig2 + 1; dig3 <= m; dig3 ++) {
                Add(ans, dp[n][dig1][dig2][dig3]);
            }
        }
    }
    cout << ans;
}

