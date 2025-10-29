#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 7;

int a[MAXN];
int st[20][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    long long sum = 0;
    for (int i=1;i<= n;i++ )
        sum += a[i];
    cout << sum;

    return 0;
}
