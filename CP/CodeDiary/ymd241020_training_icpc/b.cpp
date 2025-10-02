/* sort template*/
#include <bits/stdc++.h>
using namespace std;

#define fi  first
#define se  second
typedef long long ll;
typedef pair<int, int> ii;

template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 100 + 7; 

int n;
int a[MAX][MAX];

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

bool Checkinside(int r, int c) {
    return 1 <= min(r, c) && max(r, c) <= n && a[r][c] == 0;
}

bool dfs(int u, int v, int len = 1) {
    a[u][v] = len;
    if (len == n * n) return true;

    for (int k = 0; k < 4; k ++) {
        int r = dr[k] + u;
        int c = dc[k] + v;

        if (Checkinside(r, c)) {
            int cnt(0);
            for (int l = 0; l < 4; l ++) {
                int x = r + dr[l];
                int y = c + dc[l];
                cnt += Checkinside(x, y) == 0;
            }

            if (cnt == 3) {
                bool tmp = dfs(r, c, len + 1);
                if (tmp) return true;
                a[u][v] = 0;
                return false;
            }
        }
    }

    for (int k = 0; k < 4; k ++) {
        int r = dr[k] + u;
        int c = dc[k] + v;

        if (Checkinside(r, c)) if (dfs(r, c, len + 1)) return true;
    }

    a[u][v] = 0;
    return false;
}

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) for (int j = 1; j <= n; j ++) a[i][j] = 0;
    int r, c; cin >> r >> c;

    if (!dfs(r, c)) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) cout << a[i][j] << ' ';
        cout << '\n';
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t --) 
        process();

    return 0;
}


