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

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

int m, n;
char a[MAX][MAX];
void process() {
    cin >> m >> n;
    for (int i = 1; i <= m; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> a[i][j];
        }
    }
    int ans(0);

    for (int r = 1; r <= m; r ++) {
        for (int c = 1; c <= n; c ++) if (a[r][c] == 'C') {
            int ca(0), cm(0);

            for (int k = 0; k < 4; k ++) {
                int x = r + dr[k];
                int y = c + dc[k];
                if (!(1 <= x && x <= m)) continue;
                if (!(1 <= y && y <= n)) continue;
                if (a[x][y] == 'A') ca ++;
                if (a[x][y] == 'M') cm ++;
            }
            ans += ca * cm;
        }
    }

    cout << ans;
}

