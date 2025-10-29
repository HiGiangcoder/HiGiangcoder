#include <bits/stdc++.h>

#include <algorithm>

using namespace std;
const int MAX = 1e5 + 7;

int n, q;
int a[MAX];

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    while (q--) {
        int x;
        cin >> x;

        int u = lower_bound(a + 1, a + 1 + n, x) - a;
        int v = upper_bound(a + 1, a + 1 + n, x) - a;

        if (u == v)
            cout << "-1 -1\n";
        else
            cout << u << ' ' << v - 1 << '\n';
    }
    return 0;
}
