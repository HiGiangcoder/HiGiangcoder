#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin >> n)) return 0;
    long long s = 0, x;
    for (int i = 0; i < n; ++i) { cin >> x; s += x; }
    cout << s << "\n";
    return 0;
}
