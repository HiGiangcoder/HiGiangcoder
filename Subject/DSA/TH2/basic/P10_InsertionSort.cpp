#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

int n;
int a[MAX];

void print() {
    for (int i = 1; i <= n; i ++) {
        cout << a[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    for (int i = 2; i <= n; i ++) {
        int x = a[i];
        int j = i - 1;
        while (j >= 1 && a[j] > x) {
            a[j + 1] = a[j];
            j --;
            print();
        }
        a[j + 1] = x;
        print();
    }
    
    return 0;
}