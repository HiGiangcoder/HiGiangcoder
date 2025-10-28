#include <bits/stdc++.h>
using namespace std;

void process() {
  int n, k;
  string s;

  cin >> n >> k;
  cin >> s;

  int ans(0);
  int cnt(0);

  for (int i = 0; i < n; i++) {
    if (i >= k && s[i - k] == '1')
      cnt--;

    if (cnt == 0 && s[i] == '1')
      ans++;

    if (s[i] == '1')
      cnt++;
  }
  cout << ans << '\n';
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    process();
  }

  return 0;
}
