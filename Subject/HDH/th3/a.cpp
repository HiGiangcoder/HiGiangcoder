#include <bits/stdc++.h>
using namespace std;

void process() {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    printf("%d", sum);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    process();
    cout << "Hello world";

    return 0;
}
