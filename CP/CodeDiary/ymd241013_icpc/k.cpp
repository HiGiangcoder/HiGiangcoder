#include<bits/stdc++.h>
using ll = long long;
#define int ll

using namespace std;
const int MAX = 1e4 + 7;
const int MAXM = 1e5 + 7;

int n, p, m;

struct Pacman {
    int r, c, d;
} a[MAX];

struct Query {
    int type, k;
} q[MAXM];

int lastZ = 0;
int lastD = 0;
int fR[4], fC[4];

int dr[] = {0, -1, 0, 1};
int dc[] = {-1, 0, 1, 0};

void prepare() {
    for (int i = 1; i <= m; i ++) {
        if (q[i].type == 2) lastZ = i;
    }

    for (int i = 1; i <= lastZ; i ++) if (q[i].type == 1) {
        (lastD += q[i].k) %= 4;
    }

    // ----------------------------------------------------
    for (int curd = 0; curd < 4; curd ++) {
        int d = curd;
        for (int i = lastZ; i <= m; i ++) if (q[i].type != 2) {
    //        cout << i << ' ' << q[i].type << "    ";
            if (q[i].type == 1) {
                (d += q[i].k) %= 4;
                if (d < 0) d += 4;
            }
            else {
                (fR[curd] += dr[d] * q[i].k) %= n;
                (fC[curd] += dc[d] * q[i].k) %= n;
            }
        }
    }

    // ----------------------------------------------------
    if (lastZ != 0) for (int i = 1; i <= p; i ++) {
        int k = q[lastZ].k;
        a[i].r = k / n;
        a[i].c = k % n;

        (a[i].d += lastD) %= 4;
        if (a[i].d < 0) a[i].d += 4;
    }
}

void process() {
    for (int i = 1; i <= p; i ++) {
        int ansR = a[i].r;
        int ansC = a[i].c;

        ansR += fR[a[i].d];
        ansC += fC[a[i].d];

        (ansR = ansR % n + n) %= n;
        (ansC = ansC % n + n) %= n;
        
        cout << ansR << ' ' << ansC << '\n';
    }
}

#define TASK "pelican"
int32_t main() {
    if (fopen(TASK".in", "r")) {
        freopen(TASK".in", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> p >> m;
    
    for (int i = 1; i <= p; i ++) {
        cin >> a[i].r >> a[i].c >> a[i].d;
        a[i].d %= 4;
    }

    q[0].type = 2;
    for (int i = 1; i <= m; i ++) {
        char c; cin >> c;
        cin >> q[i].k;
        if (c == 'A') q[i].type = 0;
        if (c == 'R') q[i].type = 1;
        if (c == 'Z') q[i].type = 2;
    }

    prepare();
    process();
}
