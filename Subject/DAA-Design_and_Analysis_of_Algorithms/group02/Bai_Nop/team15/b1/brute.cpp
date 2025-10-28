#include <bits/stdc++.h>
using namespace std;

// Bài toán mẫu: cho mảng a[] gồm n phần tử, q truy vấn (l, r).
// Mỗi truy vấn in ra tổng các phần tử từ l đến r (1-based).
// -> Code trâu: O(n * q)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long s = 0;

    for(int i=0, x;i<n;++i)
        cin>>x, s+=x;

    cout << s;


    return 0;
}
