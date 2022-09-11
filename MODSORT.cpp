#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int MAX = 2e5 + 7;
#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f3f
#define endl '\n'
#define fi first
#define se second
#define BIT(mask, n) (((mask) >> (n)) & (1))
#define MASK(n) (1 << (n))
#define MOD 1000000007
template<class T> bool maximize(T &a, const T &b) {
	if (a < b) {a = b; return true;}
	return false;
}
template<class T> bool minimize(T &a, const T &b) {
	if (a > b) {a = b; return true;};
	return false;
}

struct Segment_Tree {
	vector<set<int>> st;
	int n;

	Segment_Tree(int _n = 0) {
		n = _n;
		st.assign(n * 4 + 7, set<int>());
	}

	void update(int id, int u, int val, int l, int r) {
		if (u < l || r < u) return;
		if (l == r) {
			st[id].insert(val);
			return;
		}
		int mid = l + r >> 1;
		update(id * 2, u, val, l, mid);
		update(id * 2 + 1, u, val, mid + 1, r);

		st[id].insert(val);
	}

	bool check(int id, int u, int v, int val, int l, int r) {
		if (r < u || v < l) return false;
		if (u <= l && r <= v) return st[id].count(val);

		int mid = l + r >> 1;
		return check(id * 2, u, v, val, l, mid) ||
			   check(id * 2 + 1, u, v, val, mid + 1, r);
	}
};

int n, k;
int a[MAX];

void init() {
	cin >> n >> k;
	for (int i = 1; i <= n; i ++) cin >> a[i];
}

void process() {
	vector<int> v;
	for (int i = 1; i <= n; i ++) {
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());

	int m = v.size();
	Segment_Tree st(m);

	for (int i = 1; i <= n; i ++) {
		int u = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
		if (st.check(1, u + 1, m, a[i] % k, 1, m)) {
			cout << "No\n";
			return;
		}
		st.update(1, u, a[i] % k, 1, m);
	}
	cout << "Yes\n";
}

int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen("all.inp", "r")) {
        freopen("all.inp", "r", stdin);
        freopen("all.out", "w", stdout);
    }

	int t; cin >> t;
	while (t --) {
		init();
		process();
	}

    return 0;
}
