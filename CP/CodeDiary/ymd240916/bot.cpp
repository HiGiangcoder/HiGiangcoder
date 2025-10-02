#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX = 1e6 + 7;

int n;
int a[MAX];

ll f[MAX];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];

    for (int i = 1; i <= n; i ++) f[i] = f[i - 1] + a[i];


}
