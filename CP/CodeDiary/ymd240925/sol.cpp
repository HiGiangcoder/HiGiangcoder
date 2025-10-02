#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define BUFF() ios::sync_with_stdio(0);cin.tie();cout.tie();
#define forr(i,a,b) for(int _a=(a),_b=(b),i=_a;i<=_b;i++)
#define fi first
#define se second
#define get(x,i) ((x>>(i-1))&1)
#define endl '\n'
#define left __left
#define right __right
#define Task(name) \
    freopen(name".inp","r",stdin);\
//    freopen(name".out","w",stdout);
#define mp make_pairusing namespace std;
const int N = 22;
const int M = 16;
const int D = 10;
int vis[M][D] = {0};
int tmp[M];
int A[N][M] = {
        {2, 3, 2, 1, 3, 8, 6, 1, 0, 4, 3, 0, 3, 8, 4, 5},
        {3, 8, 4, 7, 4, 3, 9, 6, 4, 7, 2, 9, 3, 0, 4, 7},
        {3, 1, 7, 4, 2, 4, 8, 4, 3, 9, 4, 6, 5, 8, 5, 8},
        {8, 1, 5, 7, 3, 5, 6, 3, 4, 4, 1, 1, 8, 4, 8, 3},
        {6, 3, 7, 5, 7, 1, 1, 9, 1, 5, 0, 7, 7, 0, 5, 0},
        {6, 9, 1, 3, 8, 5, 9, 1, 7, 3, 1, 2, 1, 3, 6, 0},
        {4, 8, 9, 5, 7, 2, 2, 6, 5, 2, 1, 9, 0, 3, 0, 6},
        {5, 6, 1, 6, 1, 8, 5, 6, 5, 0, 5, 1, 8, 2, 9, 3},
        {4, 5, 1, 3, 5, 5, 9, 0, 9, 4, 1, 4, 6, 1, 1, 7},
        {2, 6, 1, 5, 2, 5, 0, 7, 4, 4, 3, 8, 6, 8, 9, 9},
        {6, 4, 4, 2, 8, 8, 9, 0, 5, 5, 0, 4, 2, 7, 6, 8},
        {2, 3, 2, 6, 5, 0, 9, 4, 7, 1, 2, 7, 1, 4, 4, 8},
        {5, 2, 5, 1, 5, 8, 3, 3, 7, 9, 6, 4, 4, 3, 2, 2},
        {2, 6, 5, 9, 8, 6, 2, 6, 3, 7, 3, 1, 6, 8, 6, 7},
        {5, 8, 5, 5, 4, 6, 2, 9, 4, 0, 8, 1, 0, 5, 8, 7},
        {9, 7, 4, 2, 8, 5, 5, 5, 0, 7, 0, 6, 8, 3, 5, 3},
        {4, 2, 9, 6, 8, 4, 9, 6, 4, 3, 6, 0, 7, 5, 4, 3},
        {7, 8, 9, 0, 9, 7, 1, 5, 4, 8, 9, 0, 8, 0, 6, 7},
        {8, 6, 9, 0, 0, 9, 5, 8, 5, 1, 5, 2, 6, 2, 5, 4},
        {1, 7, 4, 8, 2, 7, 0, 4, 7, 6, 7, 5, 8, 2, 7, 6},
        {3, 0, 4, 1, 6, 3, 1, 1, 1, 7, 2, 2, 4, 6, 3, 5},
        {1, 8, 4, 1, 2, 3, 6, 4, 5, 4, 3, 2, 4, 5, 8, 9}
};
int B[N] = {0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3};
bool dfs1(int, int);
bool dfs2(int f, int fi, int f1, int cnt, int st, char *ne) {
    if (f1 == cnt) {
        for (int i = 0; i < M; i++)
            vis[i][A[f][i]]++;
        if (dfs1(f + 1, fi + cnt)) return true;
        for (int i = 0; i < M; i++)
            vis[i][A[f][i]]--;
        return false;
    }
    for (int i = st; i < M; i++) {
        if (ne[i]) continue;
        tmp[i] = A[f][i];
        if (dfs2(f, fi, f1 + 1, cnt, i + 1, ne)) return true;
        tmp[i] = -1;
    }
    return false;
}
bool dfs1(int f, int fi) {
    if (f == N) {
        for (int i = 0; i < M; i++) {
            if (tmp[i] == -1) {
                for (int j = 0; j < D; j++) {
                    if (vis[i][j] == 0)
                        tmp[i] = j;
                }
            }
        }
        return true;
    }
    int cnt = B[f];
    for (int i = 0; i < M; i++)
        cnt -= (A[f][i] == tmp[i]);
    if (cnt < 0)return false;
    char ne[M] = {0};
    for (int i = 0; i < M; i++)
        if (tmp[i] != -1 || vis[i][A[f][i]]) ne[i] = 1;
    if (dfs2(f, fi, 0, cnt, 0, ne)) return true;
    return false;
}

int main() {
    memset(tmp,-1,sizeof(tmp));
    dfs1(0, 0);
    string ans;
    for (int i = 0; i < M; i++)
        ans += char('0' + tmp[i]);
    cout << ans << endl;
    return 0;
}
