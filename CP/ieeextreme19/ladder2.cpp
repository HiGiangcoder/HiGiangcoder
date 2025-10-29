#include <bits/stdc++.h>
using namespace std;
using ll =  long long;

const unsigned long long K = (1ULL << 63) | 13ULL; // 100...001101

int v[2][128];
int len[2];

void generate_bits(ll &r, ll n) {
    ll store_r[2];

    for (int i = 0; i < 2; ++i) {
        store_r[i] = r;

        long long m = 19;
        while (m) {
            m = n;
            len[i] = 0;
            while (m > 0) {
                int bit = (r & 1LL) ? 1 : 0;
                v[i][len[i]++] = bit;
                long long rb = (r >> 1);
                cout << (rb >> 64) << "   ";
                unsigned long long next = (unsigned long long)rb ^ (bit ? K : 0ULL);
                r = (long long)next;
                m -= 1 + bit; // m sẽ đảm bảo rằng độ dài của dãy nhị phân = n - số bit 1, nếu không thì phải gen lại
            }
        }
    }


    // ---------------debug----------------
        bool e = true;
        size_t L = min(len[0], len[1]);
        for (size_t i = 0; i < L; ++i) {
            if (v[0][i] != v[1][i]) { e = false; break; }
        }

        if (e) {
            for (int i = 0; i < 2; i ++) {
                cout << "r " << i << ": " << store_r[i] << "\n";
                for (int i = 0; i < 64; i ++) cout << ((unsigned ll)(store_r[i] >> i) & 1ULL); cout << '\n';
                for (int j = 0; j < len[i]; j ++) cout << v[i][j] << ' '; 
                cout << '\n';
            }
            cout << "---\n";
        }
}

long long process(long long s, long long n) {
    ll f = 0;
    ll na = 0, ng = 0;
    ll a = -19 * 1919;
    long long r = -19;

    while (a < 1919 * s * s) { 
        na += 1;
        ll pre_f = f;

        generate_bits(r, n);

        bool e = true;
        size_t L = min(len[0], len[1]);
        for (size_t i = 0; i < L; ++i) {
            if (v[0][i] != v[1][i]) { e = false; break; }
        }

        if (e) {
            ng += s;
            /*
            hàm tính f = round(ng/na)
            ng: các bội của s*19 - Tăng sau mỗi lần hai dãy bit sinh ra giống nhau
            na: số lần sinh bit - Tăng sau mỗi lần sinh bit
            f: tỷ lệ của tần suất hai dãy bit giống nhau trên số lần sinh bit 
            in ra giá trị f
            */
            f = llround(double(19 * ng) / double(na));
            cout << "na: " << na << ' ' << "ng: " << ng << ' ' << "f: " << f << '\n';
            a = (f == pre_f) ? (a + 1) : 0;

            cout << "Value of a is: " << a << '\n';
            if (f != pre_f) {
                cout << "-------------------- a is zero " << a << "------------------\n";
            }
        }
    }

    return (long long)f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t --) {
        ll s, n; cin >> s >> n;
        ll result = process(s, n);
        cout << result << '\n';
    }
}
