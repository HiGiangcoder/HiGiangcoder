// brute.cpp
// Lời giải brute-force cho bài "Tổng dãy số"
// Đọc n, đọc n số nguyên, in ra tổng (dùng long long để tránh tràn)

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    cin >> n;
    long long sum = 0;
    for (long long i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        sum += x;
    }
    cout << sum << '\n';
    return 0;
}
