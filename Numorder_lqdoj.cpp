// problem: https://lqdoj.edu.vn/problem/numorder

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll numrow, numcol, numkth;

ll Sqrt(ll number) { // find res * res <= number; res -> max
	ll sqrt_num = sqrt(number);
	for (ll res = sqrt_num + 3; res >= sqrt_num - 3; res --) {
		if (res * res <= number) return res;
	}
}

bool check(ll binary_answer) {
	ll cnt = 0;	// count i^2 + j^2 <= binary_answer
	for (ll i = 1; i * i <= binary_answer && i <= numrow; i ++) {
		cnt += min(Sqrt(binary_answer - i * i), numcol);
		// count j: j^2 <= binary_answer - i^2    <=>   j <= sqrt(binary_answer - i^2)
	}
	if (cnt < numkth) return false;
	else return true;
}

void process() {
	cin >> numrow >> numcol >> numkth;
	if (numrow > numcol) swap(numrow, numcol);
	ll l = 2, r = numrow * numrow + numcol * numcol;
	ll ans;
	while (l <= r) {
		ll mid = l + r >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}

	cout << ans;
}

int main()
{
	ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
// 	freopen("all.inp", "r", stdin);
// 	freopen("all.out", "w", stdout);

	process();

    return 0;
}
