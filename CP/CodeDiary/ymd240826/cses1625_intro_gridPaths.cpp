#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int, int> ii;
 
string s;
bool fre[9][9];
int ans(0);

//          D       R      U       L         
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int trans[256];

bool checkexist(int x, int y) {
    if (x < 1 || x > 7) return true;
    if (y < 1 || y > 7) return true;
    if (fre[x][y]) return true;
    return false;
}

bool check(int x, int y, int direction) {
    int u = x + dx[direction];
    int v = y + dy[direction];

    if (checkexist(u, v)) {
        bool ok2 = false;
        for (int i = 1, j = 1; i <= 2; i ++, j *= -1) {
            int tmpdirection = direction + j;
            if (tmpdirection < 0) tmpdirection += 4;
            if (tmpdirection > 3) tmpdirection -= 4;

            u = x + dx[tmpdirection];
            v = y + dy[tmpdirection];

            ok2 = ok2 || checkexist(u, v);
        }
        if (!ok2) return false;
    }

    return true;
}

int countAround(int x, int y) {
    int res(0);
    for (int k = 0; k < 4; k ++) {
        int u = x + dx[k];
        int v = y + dy[k];

        if (checkexist(u, v)) res ++;
    }
    
    return res;
}
 
void backtrack(int id, int x, int y, int direc = 0) {
    if (x < 1 || x > 7 || y < 1 || y > 7) return;
    if (fre[x][y]) return;
 
    if (x == 1 && y == 7) {
        if (id == 48) ans ++;
        else return;
    }
    if (id == 48) return;

    if (id > 0) if (!check(x, y, direc)) return;

    fre[x][y] = true;

    int mustgo = -1;
    for (int i = 0; i < 4; i ++) {
        if (s[id] != '?' && trans[s[id]] != i) continue; 
        int u = x + dx[i];
        int v = y + dy[i];
        
        if (checkexist(u, v)) continue;
        if (u == 1 && v == 7) continue;

        if (countAround(u, v) >= 3) {
            mustgo = i;
            break;
        }
    }
 
    for (int i = 0; i < 4; i ++) {
        if (s[id] != '?' && trans[s[id]] != i) continue; 
        if (mustgo != -1 && i != mustgo) continue;

        int u = x + dx[i];
        int v = y + dy[i];
        
        if (checkexist(u, v)) continue;

        backtrack(id + 1, u, v, i);
    }
 
    fre[x][y] = false;
}
 
void process() {
    trans['L'] = 3, trans['R'] = 1;
    trans['U'] = 2, trans['D'] = 0;
 
    cin >> s;
 
    backtrack(0, 1, 1);
    cout << ans;
}
 
int main() {
    #define TASK ""
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
 
    process();
 
    return 0;
}
