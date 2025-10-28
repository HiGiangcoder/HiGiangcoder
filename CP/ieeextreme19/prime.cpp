#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<ll, ll>;

void process(ll num) {
    vector<ii> p;

    cout << "---------" << num << "---------\n";
    for (ll i = 2; i * i < num; i ++) if (num % i == 0) {
        ll u = i;
        int cnt(0);
        while (num % u == 0) {
            cnt ++;
            num /= u;
        }

        if (cnt > 0) p.emplace_back(i, cnt);
        
        u = num / u;
        cnt = 0;
        while (num % u == 0) {
            cnt ++;
            num /= u;
        }

        if (cnt > 0) p.emplace_back(i, cnt);
    }
    if (num > 0) p.emplace_back(num, 1);

    sort(p.begin(), p.end());

    for (auto x : p) {
        cout << x.first << ' ' << x.second << '\n';
    }
    cout << "-----------------------";
}

int main() {
    ll num;
    while (true) {
        cin >> num;
        process(num);
    }
}