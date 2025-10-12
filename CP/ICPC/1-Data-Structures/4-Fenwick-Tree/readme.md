### 2.3. Fenwick Tree (BIT) 1D và 2D
**BIT 1D:**
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n, bit[N];

void update(int idx, int delta) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += delta;
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

int range_query(int l, int r) {
    return query(r) - query(l-1);
}
```

**BIT 2D:**
```cpp
int n, m;
int bit[N][N];

void update(int x, int y, int delta) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j)
            bit[i][j] += delta;
}

int query(int x, int y) {
    int sum = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            sum += bit[i][j];
    return sum;
}

int range_query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1-1, y2) - 
           query(x2, y1-1) + query(x1-1, y1-1);
}
```