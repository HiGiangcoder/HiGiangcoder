#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int arr[N];
int n;

signed main()
{  
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> arr[i];
    ll sum = 0;
    for(int i = 1; i <= n; ++i) sum += arr[i];
    cout << sum;
}
