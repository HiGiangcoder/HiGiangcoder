#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long sum = 0;
    while (n--) {
        int x;
        cin >> x;
        sum+=x;
    }
    cout << sum;
    return 0;
}
