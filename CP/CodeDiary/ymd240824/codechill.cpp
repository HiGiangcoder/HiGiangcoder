#include<bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 7;

int n;
int a[MAX];
int b[MAX];

int getgcd(int pos) {
    return __gcd(a[pos - 1], a[pos]);
}
bool okLeft[MAX], okRight[MAX];

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];

    a[0] = 1;
    a[n + 1] = 0;

    okLeft[0] = okLeft[1] = okRight[n] = okRight[n + 1] = true;
    for (int i = 2; i <= n; i ++) {
        okLeft[i] = okLeft[i - 1] && getgcd(i) >= getgcd(i - 1);
    }
    for (int i = n - 1; i >= 1; i --) {
        okRight[i] = okRight[i + 1] && getgcd(i + 1) <= getgcd(i + 2);
    }
    
    for (int i = 1; i <= n; i ++) if (okLeft[i - 1] && okRight[i + 1]) {
        int nummid = __gcd(a[i - 1], a[i + 1]);
        if (i > 1 && getgcd(i - 1) > nummid) continue;
        if (i < n && nummid > getgcd(i + 2)) continue;

        cout << "YES" << '\n';
        return;
    }
    cout << "NO\n";
}

int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t --) {
        process();
    }
}
