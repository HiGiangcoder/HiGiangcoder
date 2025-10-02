#include<bits/stdc++.h>
#define fi first
#define se second

using namespace std;
using ii = pair<int, int>;
using ll = long long;

template<class T> bool minimize(T &a, const T &b) {
    if (a > b) {a = b; return true;}
    return false;
}

void process();
int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);

    process();

    return 0;
}

const int MAX = 1e4 + 7;
int n;

struct Target {
    int posX;
    int radius;
    int id;

    Target() {}
    Target(int p, int r, int i) : posX(p), radius(r), id(i) {}

    bool operator < (const Target &x) const {
        return posX < x.posX;
    }
} a[MAX];

int ans[MAX];

bool check(int id, int posX, int posY) {
    if (id < 1 || n < id) return false;
    ll dx = (posX - a[id].posX);
    ll dy = posY;
    ll d = a[id].radius;
    return d * d >= dx * dx + dy * dy;
}

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i].posX >> a[i].radius;
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n, [&](const Target &x, const Target &y){
        return x.posX < y.posX;
    });

    memset(ans, 0x3f, sizeof(ans));

    int m; cin >> m;
    for (int id = 1; id <= m; id ++) {
        int x, y; cin >> x >> y;
        int u = lower_bound(a + 1, a + 1 + n, Target(x, 0, 0)) - a;

        if (check(u - 1, x, y)) minimize(ans[a[u - 1].id], id);
        if (check(u, x, y)) minimize(ans[a[u].id], id);
        if (check(u + 1, x, y)) minimize(ans[a[u + 1].id], id);
    }

    int num(0);
    for (int i = 1; i <= n; i ++) {
        if (ans[i] <= m) num ++;
        else ans[i] = -1;
    }

    cout << num << '\n';
    for (int i = 1; i <= n; i ++) cout << ans[i] << " \n"[i == n];
}
