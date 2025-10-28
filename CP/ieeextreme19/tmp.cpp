#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num;
    cin >> num;
    const unsigned long long K = (1ULL << 63) | 13ULL;

    while (num--) {
        long long s, n;
        cin >> s >> n;

        vector<int> v[2];
        double f = 0, na = 0, ng = 0;
        double a = -19;
        long long r = -19;

        while (a < 1.0 * s * s) {
            na += 1.0 / 19.0;
            double f1 = f;

            for (int i2 = 0; i2 < 2; ++i2) {
                long long m = 19;
                while (m) {
                    m = n;
                    v[i2].clear();
                    while (m > 0) {
                        int bit = (r & 1LL) ? 1 : 0;
                        v[i2].push_back(bit);
                        long long rb = (r >> 1);
                        unsigned long long next = (unsigned long long)rb ^ (bit ? K : 0ULL);
                        r = (long long)next;
                        m -= 1 + bit;
                    }
                }
            }

            bool e = true;
            size_t L = min(v[0].size(), v[1].size());
            for (size_t i = 0; i < L; ++i) {
                if (v[0][i] != v[1][i]) { e = false; break; }
            }

            if (e) {
                ng += s;
                f = llround(ng / na);
                a = (f == f1) ? (a + 1.0 / 1919.0) : 0;
            }
        }

        cout << (long long)f << "\n";
    }
}
