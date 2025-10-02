// medium template
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

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 10 + 7; 

ll A[MAX][MAX];
void Prepare() {
    for (int i = 0; i <= 10; i ++) {
        A[i][0] = 1;
        for (int j = 1; j <= i; j ++) {
            A[i][j] = A[i][j - 1] * (i - j + 1);
        }
    }
}

ll num;
int a[MAX];
bool fre[MAX];

void SolveQuery1() {
    MEM(fre, true);
    int len = 0;

    for (int l = 1; l <= 10; l ++) {
        for (int i = 1; i <= l; i ++) {
            int digit = 0;
            if (i == 1) digit = 1;

            for (; digit <= 9; digit ++) if (fre[digit]) {
                ll tmp = A[10 - i][l - i];

                if (num > tmp) num -= tmp;
                else {
                    a[i] = digit;
                    len = l;
                    fre[digit] = false;
                    break;
                }
            }
            if (len == 0) break;
        }
        if (len != 0) break;
    }

    cout << 1 << ' ';
    for (int i = 1; i <= len; i ++) cout << a[i]; cout << '\n';
}

void SolveQuery2() {
    string s = to_string(num);
    int len = s.length();
    MEM(fre, true);
    ll result(0);

    for (int i = 1; i <= len; i ++) {
        int digit = 0;
        if (i == 1) digit = 1;

        for (; digit < int(s[i - 1] - '0'); digit ++) if (fre[digit]) {
            result += A[10 - i][len - i];
        }

        fre[s[i - 1] - '0'] = false;
    }
    result ++;

    for (int l = 1; l < len; l ++) {
        result += A[9][l - 1] * 9;
    }

    cout << 2 << ' ' << result << '\n';
}

void process(int type) { 
    cin >> num;
    if (type == 1) SolveQuery1();
    else SolveQuery2();
}


#define TASK "special" 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    
    Prepare();

    int type; 
    while (true) {
        cin >> type;
        if (type == 0) break;
        process(type);
    }

    return 0;
}
