#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> a(n + 10);
    for (int i = 1; i <= n; i++) cin >> a[i];
    long long sum = 0;
    for (int i = 1; i <= n; i++) sum += a[i];
    cout << sum << "\n";
    return 0;
}
