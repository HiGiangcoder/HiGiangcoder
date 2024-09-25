#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int MAX = 1e3 + 7;
#define inf 0x3f3f3f3f
#define endl '\n'
#define fi first
#define se second
#define BIT(mask, n) (((mask) >> (n)) & (1))
#define MASK(mask, n) ((mask) << n)
template<class T>
	bool maximize(T &a, const T &b) {
		if (a < b) {a = b; return true;}
		return false;
	}
template<class T>
	bool minimize(T &a, const T &b) {
		if (a > b) {a = b; return true;};
		return false;
	}

int n, m;
bool a[MAX][MAX];

void init() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cin >> a[i][j];
        }
    }
}

struct point {
    int x, y;
    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    }

    bool operator == (const point &u) const {
        return x == u.x && y == u.y;
    }

    bool operator < (const point &u) const {
        if (x == u.x) return y < u.y;
        return x < u.x;
    }
};

int ddx[] = {1, 1, -1, -1};
int ddy[] = {1, -1, 1, -1};

struct houses {
    vector<point> h;
    int id;

    houses() {
        h.clear();
    }

    void push_back(point u) {
        h.push_back(u);
    }

    void rehouse() {
        point valmin(inf, inf);
        for (auto &x : h) {
            minimize(valmin.x, x.x);
            minimize(valmin.y, x.y);
        }
        for (auto &x : h) {
            x.x -= valmin.x;
            x.y -= valmin.y;
        }
        sort(h.begin(), h.end());
    }

    bool operator < (const houses &v) const {
        if (h.size() != v.h.size()) return h.size() < v.h.size();
        for (int k = 0; k < 8; k ++) {
            houses tmp = v;
            bool ok = true;

            for (auto &u : tmp.h) {
                if (k >= 4) swap(u.x, u.y);
                u.x *= ddx[k % 4];
                u.y *= ddy[k % 4];
            }

            tmp.rehouse();

            for (int i = 0; i < h.size(); i ++) {
                if (h[i] == tmp.h[i]) continue;
                ok = false;
                break;
            }
            if (!ok) continue;

            return false;
        }

        return id < v.id;
    }
};

set<houses> houuni;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(point u, houses &h) {
    a[u.x][u.y] = 0;
    h.push_back(u);

    for (int k = 0; k < 4; k ++) {
        int x = u.x + dx[k];
        int y = u.y + dy[k];

        if (x < 1 || x > n) continue;
        if (y < 1 || y > m) continue;
        if (a[x][y] == 0) continue;

        dfs(point(x, y), h);
    }
}

void process() {
    int cnt = 0;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            if (a[i][j]) {
                houses u;
                u.id = ++cnt;

                dfs(point(i, j), u);
                u.rehouse();

                houuni.insert(u);
            }
        }
    }

    cout << houuni.size();
}

int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("houses.inp", "r", stdin);
    freopen("houses.out", "w", stdout);

    init();
    process();

    return 0;
}
