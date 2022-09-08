#include <bits/stdc++.h>
#define MAX 2022
#define MOD 1000000007
#define endl '\n'
using namespace std;
using ll = long long;

int n, query, mod;
int a[MAX];

void init() {
	cin >> n >> query >> mod;
//	scanf("%d %d %d", &n, &query, &mod);

	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
//		scanf("%d", &a[i]);
	}
}

int l[MAX][MAX];	// l[i][mod]: [i] 1 -> i                     calculator ways
int r[MAX][MAX];	// r[i][mod]: [i] n -> i					 calculator ways
int h[MAX][MAX];    // h[i][mod]: [i] 1 -> i - 1 && i + 1 -> n   calculator ways
int c[MAX][MAX];	// c[k][n]: nCk

int Div[MAX]; // division for k by multiplying

int Pow(int _k, int _n) {
	if (_n == 0) return 1;
	int tmp = Pow(_k, _n / 2);
	if (_n % 2) return 1LL * tmp * tmp % mod * _k % mod;
	else return 1LL * tmp * tmp % mod;
}

int tmpcomb; // nCk = n! / (n - k)! / k! = n! / (n - k - 1)! / (k + 1)! * (n - k) / (k + 1)
/* ---------->  nCk = n! / (n - k)! / k! = n! / (n - (k - 1)) / (k - 1)! * (n - k + 1) / k */

int Comb(int _k, int _n) {
	if (mod == 2018) return c[_k][_n];
	else {
		if (_k == 0) tmpcomb = 1;
		else {
			tmpcomb = 1LL * tmpcomb * (_n - _k + 1) % mod * Div[_k] % mod;
		}
		return tmpcomb;
	}
}

void prepare() {
	if (mod == 2018) {
		c[0][0] = 1;
		for (int i = 1; i < MAX; i ++) {
			c[0][i] = 1;
			for (int j = 1; j <= i; j ++) {
				c[j][i] = (1LL * c[j][i - 1] + c[j - 1][i - 1]) % mod;
			}
		}
	}
	else {
		for (int i = 1; i < MAX; i ++) {
			Div[i] = Pow(i, mod - 2);
		}
	}

	l[0][0] = 1;
	for (int i = 1; i <= n; i ++) {
		for (int sum = 0; sum <= n; sum ++) {
			for (int k = 0; k * i + sum <= n && k <= a[i]; k ++) {
				l[i][sum + k * i] = (l[i][sum + k * i] + 1LL * l[i - 1][sum] * Comb(k, a[i]) % mod) % mod;
			}
		}
	}

	r[n + 1][0] = 1;
	for (int i = n; i >= 1; i --) {
		for (int sum = 0; sum <= n; sum ++) {
			for (int k = 0; k * i + sum <= n && k <= a[i]; k ++) {
				r[i][sum + k * i] = (r[i][sum + k * i] + 1LL * r[i + 1][sum] * Comb(k, a[i]) % mod) % mod;
			}
		}
	}
	memset(h, -1, sizeof(h));
}

int getH(int p, int s) {
	if (h[p][s] >= 0) return h[p][s];
	h[p][s] = 0;
	for (int i = 0; i <= s; i ++) {
		h[p][s] = (1LL * h[p][s] + 1LL * l[p - 1][s - i] * r[p + 1][i] % mod) % mod;
	}
	return h[p][s];
}

void Query(int p, int d, int s) {
	int res = 0;
	for (int k = 0; k * p <= s && k <= a[p] - d; k ++) {
		res = (res + 1LL * getH(p, s - k * p) * Comb(k, a[p] - d) % mod) % mod;
	}
	cout << res << endl;
//	printf("%d\n", res);
}

void process() {
	prepare();

	while (query --) {
		int p, d, s;
		cin >> p >> d >> s;
//		scanf("%d %d %d", &p, &d, &s);
		Query(p, d, s);
	}
}

int main() {
    ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("orangejuice.inp", "r", stdin);
    freopen("orangejuice.out", "w", stdout);

	int t;
	cin >> t;
//	scanf("%d", &t);

	init();
	process();

    return 0;
}
