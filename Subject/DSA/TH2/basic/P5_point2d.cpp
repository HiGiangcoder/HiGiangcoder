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
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    bool operator < (const Point &p) const {
        if (x != p.x) return x < p.x;
        return y > p.y;
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
        int x, y; cin >> x >> y;
        points.insert(Point(x, y));
    }

    for (Point point : points) cout << point.x << ' ' << point.y << '\n';
    
    return 0;
}