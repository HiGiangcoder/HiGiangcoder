#include <bits/stdc++.h>
using namespace std;

int main() {
    // Tăng tốc độ nhập xuất
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Sử dụng long long để tránh tràn số khi tính tổng
    long long total_sum = 0;
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        total_sum += value;
    }

    cout << total_sum << "\n";

    return 0;
}