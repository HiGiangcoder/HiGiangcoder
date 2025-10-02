#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 3e5 + 5;


#define TASK ""

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    int n; cin >> n;

    set<int> s;
    while (n--) {
        int x; cin >> x;
        s.insert(x);
    }

    cout << s.size() << endl;
    for (int x : s) {
        cout << x << " ";
    }
    
    return 0;
}