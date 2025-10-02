#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

struct Point {
    int x, y, z;
    Point(int x, int y, int z) : x(x), y(y), z(z) {}

    bool operator < (const Point &p) const {
        if (x != p.x) return x < p.x;
        if (y != p.y) return y > p.y;
        return z < p.z;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    int n;
    multiset<Point> points;

    cin >> n;
    for (int i = 1; i <= n; i ++) {
        int x, y, z; cin >> x >> y >> z;
        points.insert(Point(x, y, z));
    }

    for (Point point : points) cout << point.x << ' ' << point.y << ' ' << point.z << '\n';
    
    return 0;
}