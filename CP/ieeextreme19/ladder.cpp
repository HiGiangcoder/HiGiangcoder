#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
using ll = long long;
typedef unsigned long long ull;

const unsigned long long C = (1ULL << 63) | 13ULL;

int cnt_gen(0);

vector<int> generate_bits(ll& r, int n) {
    vector<int> bits;
    ll m = 19;
    while (m != 0) {
        m = n;
        bits.clear();
        while (m > 0) {
            int bit = (r & 1LL) ? 1 : 0;
            bits.push_back(bit);
            ll rb = (r >> 1);
            ull next_r = (ull)rb ^ (bit ? C : 0ULL);
            r = ll(next_r);
            m -= 1 + bit;
        }
        cnt_gen++;
    }
    return bits;
}


long long simulate(ll s, ll n) {
    vector<vector<int>> v(2);
    ll f = 0, na = 0, ng = 0;
    ll a = -19 * 1919;
    ll r = -19;

    while (a < s * s * 1919) { // vì a được tăng lên 1919 lần nên s*s cũng phải tăng lên 1919 lần
        na++; // na = old_na * 19
        ll pre_f = f;

        for (int i = 0; i < 2; i++) {
            auto res = generate_bits(r, n);
            v[i] = res;
        }

        // Kiểm tra xem 2 xâu có giống nhau (giống tới min của 1 trong 2 xâu) hay không?
        bool equal = true; 
        for (int i = 0; i < min(v[0].size(), v[1].size()); i++) {
            if (v[0][i] != v[1][i]) {
                equal = false;
                break;
            }
        }

        if (equal) {
            ng += s * 19; // vì na được nhân lên 19 lần nên ng cũng phải được nâng lên 19 lần

            /*
            hàm tính f = round(ng/na)
            ng: các bội của s*19 - Tăng sau mỗi lần hai dãy bit sinh ra giống nhau
            na: số lần sinh bit - Tăng sau mỗi lần sinh bit
            f: tỷ lệ của tần suất hai dãy bit giống nhau trên số lần sinh bit 
            in ra giá trị f
            */
            f = llround(double(ng) / (double)na); // vì na = 19 * old_na nên ng = 19 * old_ng
            a = (f == pre_f) ? (a + 1) : 0;
        }
    }
    return f;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // int num_tests;
    // cin >> num_tests;
    // while (num_tests --) {
    //     long long s, n;
    //     cin >> s >> n;
    //     ll result = simulate(s, n);
    //     cout << result << '\n';
    // }

    int cnt0(0);
    for (int s = 1; s < 100; s ++) {
        for (int n = 1; n < 100; n ++) {
            int ans = simulate(s, n);
            cout << s << ' ' << n << ' ' << ans << endl;

            if (ans == 0) cnt0 ++;
            else cnt0 = 0;
            if (cnt0 > 3) break;
        }
    }
    return 0;
}