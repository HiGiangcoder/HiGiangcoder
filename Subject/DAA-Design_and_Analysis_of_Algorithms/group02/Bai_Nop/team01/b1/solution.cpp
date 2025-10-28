#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;

int a[MAXN+36];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long sum = 0;
    cin >> n;
    for (int i=0;i<n;i++) {
        cin >> a[i];
        sum += a[i];   
    }
    cout << sum << '\n';
    return 0;
}
