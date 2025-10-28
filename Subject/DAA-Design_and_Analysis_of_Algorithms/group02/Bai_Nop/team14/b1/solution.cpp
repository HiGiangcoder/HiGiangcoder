#include <bits/stdc++.h>
using namespace std;

// Bài toán mẫu: cho mảng a[] gồm n phần tử, q truy vấn (l, r).
// Mỗi truy vấn in ra tổng các phần tử từ l đến r (1-based).
// -> Code trâu: O(n * q)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i ++) 
    {
        int x;
        cin >> x;
        sum += x;
    }
    cout << sum;
    return 0;
}
