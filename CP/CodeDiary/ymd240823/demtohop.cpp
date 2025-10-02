#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }

#define TASK "demtohop"
const int MAX = 70 + 7;

ll C[MAX][MAX];

int n, k;
void prepare() {
    cin >> n >> k;
    for (int i = 0; i <= n; i ++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j ++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    cout << C[n][k] << '\n';
}

int a[MAX];

void Query1() {
    for (int i = 1; i <= k; i ++) {
        cin >> a[i];
    }
    
    ll ans(0);

    int nummax(0);
    for (int i = 1; i <= k; i ++) {

        for (int num = nummax + 1; num < a[i]; num ++) {
            ans += C[n - num][k - i];
        }

        maximize(nummax, a[i]);
    }
    ans ++;

    cout << ans << '\n';
}

void Query2() {
    ll p; cin >> p;

    int nummax(0);
    for (int i = 1; i <= k; i ++) {

        for (int num = nummax + 1; num <= n; num ++) {
            ll tmp = C[n - num][k - i];
            if (p > tmp) p -= tmp;
            else {
                a[i] = num;
                maximize(nummax, num);
                break;
            }
        }
    }
    for (int i = 1; i <= k; i ++) cout << a[i] << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    prepare();

    int type; 
    while (cin >> type) {
        if (type == 1) Query1();
        else Query2();
    }

    return 0;
}
