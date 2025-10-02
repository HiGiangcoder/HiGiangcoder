#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int n;
ii a[MAX];

bool marked[MAX];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i].fi;
        a[i].se = i;
    }

    int ans = 0x3f3f3f3f;
    sort(a + 1, a + n + 1);
    memset(marked, 0, sizeof marked);

    int res = 0;
    for (int i = 1; i <= n; i ++) if (!marked[i] && i != a[i].se) {
        int u = i;
        do {
            int v = a[u].se;
            if (a[u].fi != a[v].fi) res ++;

            marked[u] = true;
            u = a[u].se;
        } while (u != i);
        res --;
    }
    ans = res;
    res = 0;

    sort(a + 1, a + n + 1, greater<ii>());
    memset(marked, 0, sizeof marked);

    for (int i = 1; i <= n; i ++) if (!marked[i] && i != a[i].se) {
        int u = i;
        do {
            int v = a[u].se;
            if (a[u].fi != a[v].fi) res ++;

            marked[u] = true;
            u = a[u].se;
        } while (u != i);
        res --;
    }
    ans = min(ans, res);

    cout << ans;

    return 0;
}