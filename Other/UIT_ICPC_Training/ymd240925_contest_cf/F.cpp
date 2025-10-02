/* sort template*/
#include <bits/stdc++.h>
using namespace std;

#define fi  first
#define se  second
typedef long long ll;
typedef pair<int, int> ii;

template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 7; 

void process();

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t --) 
        process();

    return 0;
}

int n, m;
int a[MAX];

int fLeft[MAX], fRight[MAX];

void process() {
    cin >> n >> m;
    for (int i = 1; i <= m + 1; i ++) a[i] = fLeft[i] = fRight[i] = 0;

    int cntLeft(0), cntRight(0);
    for (int i = 1; i <= n; i ++) {
        int x; cin >> x;
        if (x == -1) cntLeft ++;
        else if (x == -2) cntRight ++;
        else a[x] = 1;
    }

    for (int i = 1; i <= m; i ++) {
        fLeft[i] = fLeft[i - 1] + a[i];
    }
    for (int i = m; i >= 1; i --) {
        fRight[i] = fRight[i + 1] + a[i];
    }

    int ans(0);
    for (int i = 0; i <= m; i ++) if (a[i] || i == 0 || i == m) {
        int res(0);
        res += min(i, fLeft[i] + cntLeft);
        res += min(m - i, fRight[i + 1] + cntRight);
        maximize(ans, res);
    }

    cout << ans << '\n';
}
