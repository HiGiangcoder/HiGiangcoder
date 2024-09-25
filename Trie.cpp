#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int MAX = 5007;
#define M 100005
#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f3f
#define endl '\n'
#define fi first
#define se second
#define BIT(mask, n) (((mask) >> (n)) & (1))
#define MASK(n) (1 << (n))
#define MOD 1000000007
template<class T> bool maximize(T &a, const T &b) {
	if (a < b) {a = b; return true;} return false;
}
template<class T> bool minimize(T &a, const T &b) {
	if (a > b) {a = b; return true;} return false;
}

struct Node {
	int sz = 0;
	Node *v[26];

	Node () {
		sz = 0;
		for (int i = 0; i < 26; i ++) v[i] = nullptr;
	}
};

struct Trie {
	Node *root = new Node;

	void addstr(string s) {
		int c;
		Node *i = root;

		while (!s.empty()) {
			c = s.back() - 'a';
			if (i->v[c] == nullptr) i->v[c] = new Node;
			if (s.length() == 1) i->v[c]->sz ++;
			i = i->v[c];
			s.pop_back();
		}
	}
};

int numlen;
string a;
int numstr;
string b[M];

void init() {
	cin >> a;
	numlen = a.length();
	cin >> numstr;
	for (int i = 1; i <= numstr; i ++) {
		cin >> b[i];
	}
}

Trie trie;
ll dp[MAX];

void process() {
	for (int i = 1; i <= numstr; i ++) {
		trie.addstr(b[i]);
	}

	dp[0] = 1;

	for (int i = 1; i <= numlen; i ++) {
		Node *ptr_i = trie.root;
		int c;
		int pre_size = 0;
		for (int j = i; j >= 1; j --) {
			c = a[j - 1] - 'a';
			ptr_i = ptr_i->v[c];

			if (ptr_i == nullptr) {
				break;
			}
			dp[i] += dp[j - 1] * ptr_i->sz % MOD;
			dp[i] %= MOD;
		}
	}

	cout << dp[numlen];
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
