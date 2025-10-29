#include <bits/stdc++.h>
using namespace std;

// Bài toán mẫu: cho mảng a[] gồm n phần tử, q truy vấn (l, r).
// Mỗi truy vấn in ra tổng các phần tử từ l đến r (1-based).
// -> Code trâu: O(n * q)

int a[1007];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum+=a[i];
    }
    cout << sum;
    return 0;
}
