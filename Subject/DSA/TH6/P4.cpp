#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;


int n;
int x;
int a[44];

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 0;

    vector<ll> subset1;
    for (int i = 0; i < (1 << (n / 2)); i++) {
        ll sum = 0;
        for (int j = 0; j < n / 2; j++) {
            if (i & (1 << j)) {
                sum += a[j];
            }
        }
        subset1.push_back(sum);
    }

    sort(subset1.begin(), subset1.end());

    for (int i = 0; i < (1 << (n - n / 2)); i++) {
        ll sum = 0;
        for (int j = 0; j < n - n / 2; j++) {
            if (i & (1 << j)) {
                sum += a[j + n / 2];
            }
        }
        ll target = x - sum;
        int u = lower_bound(subset1.begin(), subset1.end(), target) - subset1.begin();
        int v = upper_bound(subset1.begin(), subset1.end(), target) - subset1.begin();
        ans += v - u;
    }

    cout << ans << endl;
    
    return 0;
}