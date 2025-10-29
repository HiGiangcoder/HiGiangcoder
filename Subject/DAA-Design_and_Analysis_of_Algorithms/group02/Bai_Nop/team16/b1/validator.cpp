#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long n; if(!(cin >> n)) { cerr<<"missing n\n"; return 1; }
    if (n < 1 || n > 100000) { cerr<<"n out of range\n"; return 1; }
    for (long long i=0;i<n;i++) {
        long long a; if(!(cin >> a)) { cerr<<"missing ai\n"; return 1; }
        if (a < -100000 || a > 100000) { cerr<<"ai out of range\n"; return 1; }
    }
    string extra; if (cin >> extra) { cerr<<"trailing tokens\n"; return 1; }
    return 0;
}
