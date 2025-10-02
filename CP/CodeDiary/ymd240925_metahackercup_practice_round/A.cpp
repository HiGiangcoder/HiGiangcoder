#include<bits/stdc++.h>
using namespace std;

const int MAX = 1000 + 7;

int n, k;
int a[MAX];

bool process() {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) cin >> a[i];

    sort(a + 1, a + 1 + n);
    if (n <= 2) return a[1] <= k;

    long long sum(0);
    for (int i = 1; i <= n - 2; i ++) sum += 1LL * a[i] * 2;
    sum += a[n - 1];

    return sum <= k;
}

int main() {
    int t; cin >> t;

    for (int i = 1; i <= t; i ++) {
        if (process()) cout << "Case #" << i  << ": YES" << endl;
        else cout << "Case #" << i  << ": NO" << endl;
    }

    return 0;
}
