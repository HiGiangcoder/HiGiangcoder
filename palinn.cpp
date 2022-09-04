// dynamic programming digit

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int MAX = 47;
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
ll numk;

void init() {
	cin >> n >> m;
	cin >> numk;
}

#define M 111

ll dp[MAX][10][M];
ll Pow[MAX];
vector<int> mods[MAX];

void process() {
	if (n % 2) {
		for (int i = 0; i <= 9; i ++) dp[0][i][i % m] = 1;
	}
	else dp[0][0][0] = 1;

	Pow[0] = 1 % m;
	for (int i = 1; i <= n; i ++) Pow[i] = Pow[i - 1] * 10 % m;

	for (int i = 1; i <= n / 2; i ++) {
		ll tmp[M];
		memset(tmp, 0, sizeof(tmp));

		for (int modun = 0; modun < m; modun ++) {
			for (int k = 0; k <= 9; k ++) {
				tmp[modun] += dp[i - 1][k][modun];
			}
		}

		for (int k = 0; k <= 9; k ++) {
			for (int modun = 0; modun < m; modun ++) {
				ll u = (k + k * Pow[n % 2 + (i - 1) * 2 + 1] % m) % m;
				dp[i][k][(modun * 10 + u) % m] += tmp[modun];
			}
		}
	}

	ll res = 0;
	for (int k = 1; k <= 9; k ++) {
		res += dp[n / 2][k][0];
	}

	cout << res << endl;

	string s = "";
	ll mod = 0, kmain = 0;

	for (int k = 1; k <= 9; k ++) {
		if (dp[n / 2][k][mod] >= numk) {
			kmain = k;
			break;
		}
		numk -= dp[n / 2][k][mod];
	}

	mods[n / 2].push_back(mod);

	for (int i = n / 2; i >= 1; i --) {
		s += kmain + '0';

		for (auto &x : mods[i]) {
			x -= (kmain + kmain * Pow[n % 2 + (i - 1) * 2 + 1] % m) % m;
			if (x < 0) x += m;
		}

		for (int k = 0; k <= 9; k ++) {
			ll tmp = 0;

			for (int modun = 0; modun < m; modun ++) {
				for (auto &x : mods[i]) {
					if (modun * 10 % m == x) {
						tmp += dp[i - 1][k][modun];
					}
				}
			}

			if (tmp >= numk) {
				for (int modun = 0; modun < m; modun ++) {
					bool check = false;
					for (auto &x : mods[i]) {
						if (modun * 10 % m == x) {
							check = true;
							break;
						}
					}

					if (check) {
						mods[i - 1].push_back(modun);
					}
				}
				kmain = k;

				break;
			}
			else {
				numk -= tmp;
			}
		}
	}

	string rs = s;
	reverse(rs.begin(), rs.end());
	if (n % 2) s += kmain + '0';

	cout << s + rs;
}

int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen("palinn.inp", "r")) {
        freopen("palinn.inp", "r", stdin);
        freopen("palinn.out", "w", stdout);
    }

    init();
    process();

    return 0;
}
