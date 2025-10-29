#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 7;
#define int long long
int a[MAXN];

main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n ;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // Sparse Table
    int s = 0;
    for(int i = 1;i<=n;++i){
        s += a[i];
    }
    cout << s;
}
