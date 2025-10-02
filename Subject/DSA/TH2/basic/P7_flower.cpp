#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 7;

#define TASK ""

int n, k;

struct Flowers {
    int flowers[MAX];

    void Add(int val, int &len) {
        flowers[++len] = val;
        int i = len;
        while (i > 1) {
            if (flowers[i] > flowers[i / 2]) {
                swap(flowers[i], flowers[i / 2]);
                i /= 2;
            } else break;
        }
    }

    int Get(int &len) {
        int res = flowers[1];
        flowers[1] = flowers[len --];
        int i = 1;
        while (i * 2 <= len) {
            int j = i * 2;
            if (j < len && flowers[j] < flowers[j + 1]) j ++;
            if (flowers[i] < flowers[j]) {
                swap(flowers[i], flowers[j]);
                i = j;
            } else break;
        }
        return res;
    }

    void Sort() {
        int m = 0;
        for (int i = 1; i <= n; i ++) {
            Add(flowers[i], m);
        }

        for (int i = n; i >= 1; i --) {
            flowers[i] = Get(m);
        }
    }

    void Solve() {
        for (int i = 1; i <= n; i ++) if (flowers[i - 1] != flowers[i]) {
            if (k > 0) {
                k --; 
                cout << flowers[i] << ' ';
            }
        }
        for (int i = 1; i <= n; i ++) if (flowers[i - 1] == flowers[i]) {
            if (k > 0) {
                k --; 
                cout << flowers[i] << ' ';
            }
        }
    }
} problem;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        problem.flowers[i] = x;
    }

    problem.Sort();

    problem.Solve();

    return 0;
}