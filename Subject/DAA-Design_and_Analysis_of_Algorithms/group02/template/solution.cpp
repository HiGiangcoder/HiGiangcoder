#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 7;

int a[MAXN];
int st[20][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // Sparse Table
    int K = 20;
    for (int i = 1; i <= n; ++i) st[0][i] = a[i];
    for (int k = 1; (1 << k) <= n; ++k)
        for (int i = 1; i + (1 << k) - 1 <= n; ++i)
            st[k][i] = max(st[k-1][i], st[k-1][i + (1 << (k-1))]);

    auto query = [&](int l, int r) {
        int k = __lg(r - l + 1);
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    };

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << "\n";
    }
}
