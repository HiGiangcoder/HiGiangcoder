// - Cho xâu A và xâu B chỉ gồm các chữ cái thường. Xâu B được gọi là xuất hiện tại vị trí i của xâu A nếu: A[i] = B[1], 
// A[i + 1] = b[2], ..., A[i + length(B)] = B[length(B)].
// - Hãy tìm tất cả các vị trí mà B xuất hiện trong A.
// Input:                                                                               Sample Input
//        Dòng 1 chứa xâu A                                                             aaaaa
//        Dòng 2 chứa xâu B                                                             aa
//        * length(A), length(B) <= 10^6
// Output:                                                                              Sample Output
//         Ghi ra các vị trí tìm được trên 1 dòng (thứ tự tăng dần).                    1 2 3 4
//         Nếu B không xuất hiện trong A thì bỏ trắng.
// https://oj.vnoi.info/problem/substr

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int MAX = 1e6 + 7;
#define inf 0x3f3f3f3f
#define endl '\n'
#define fi first
#define se second
#define BIT(mask, n) (((mask) >> (n)) & (1))
#define MASK(mask, n) ((mask) << n)
#define MOD 1000000007
template<class T> bool maximize(T &a, const T &b) {
	if (a < b) {a = b; return true;}
	return false;
}
template<class T> bool minimize(T &a, const T &b) {
	if (a > b) {a = b; return true;};
	return false;
}

string a, b;
int n, m;
void init() {
    cin >> a >> b;
    n = a.length();
    m = b.length();
}

int az[MAX], bz[MAX];

void process() {
	bz[0] = m;
	for (int i = 1, l = 0, r = 0; i < m; i ++) {
		if (i <= r) {
			bz[i] = min(bz[i - l], r - i + 1);
		}
		while (i + bz[i] < m && b[i + bz[i]] == b[bz[i]]) {
			bz[i] ++;
		}
		if (i + bz[i] - 1 > r) {
			r = i + bz[i] - 1;
			l = i;
		}
	}

	for (int i = 0, l = -1, r = -1; i < n; i ++) {
		if (i <= r) {
			az[i] = min(bz[i - l], r - i + 1);
		}
		while (i + az[i] < n && a[i + az[i]] == b[az[i]]) {
			az[i] ++;
		}
		if (i + az[i] - 1 > r) {
			r = i + az[i] - 1;
			l = i;
		}
	}

	for (int i = 0; i < n; i ++) {
		if (az[i] == m) {
			cout << i + 1 << ' ';
		}
	}
}

int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen("all.inp", "r")) {
        freopen("all.inp", "r", stdin);
        freopen("all.out", "w", stdout);
    }

    init();
    process();

    return 0;
}
