```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5, LOG = 17;
int st[N][LOG];
int lg[N];

void build(int n, vector<int>& arr) {
    for (int i = 0; i < n; i++) st[i][0] = arr[i];
    
    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + (1<<j) <= n; i++)
            st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i/2] + 1;
}

int query(int l, int r) {
    int j = lg[r-l+1];
    return min(st[l][j], st[r-(1<<j)+1][j]);
}
```