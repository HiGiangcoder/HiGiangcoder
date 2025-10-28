#include <bits/stdc++.h>
using namespace std;

// Bài toán mẫu: cho mảng a[] gồm n phần tử, q truy vấn (l, r).
// Mỗi truy vấn in ra tổng các phần tử từ l đến r (1-based).
// -> Code trâu: O(n * q)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    while (q--) {
        int l, r;
        cin >> l >> r;
        long long ans = a[l];
        for (int i = l; i <= r; i++) if (a[i] > ans) ans = a[i];
        cout << ans << "\n";
    }
    return 0;
}
