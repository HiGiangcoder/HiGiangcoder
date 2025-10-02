/* sort template*/
#include <bits/stdc++.h>
using namespace std;

#define fi  first
#define se  second
typedef long long ll;
#define int ll
typedef pair<int, int> ii;


template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 7; 

int n, q;
int a[MAX];
ll f[MAX];

ll Sum(int l, int r) {
    return f[r] - f[l - 1];
}

int nextId[MAX];

void process() {
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) cin >> a[i];

    for (int i = 1; i <= n; i ++) {
        f[i] = f[i - 1] + a[i];
    }

    while (q --) {
        ll numX; cin >> numX;
        ll ans(0);

        nextId[0] = n;
        for (int i = 1; i <= n; i ++) {
            nextId[i] = nextId[i - 1];
            while (nextId[i] > 0 && a[i] + a[nextId[i]] > numX) {
                nextId[i] --;
            }
        }

//        for (int i = 1; i <= n; i ++) cout << nextId[i] << ' '; cout << endl; cout << endl;

        int l = 1, r = 1;

        deque<int> numNext;
        for (; l <= n; l ++) {
            if (maximize(r, l)) {
                numNext.clear();
//                cout << "******************" << endl;
            }
            else if (l > 1 && numNext.front() < l) numNext.pop_front();

            while (r <= n) {
                ll val = nextId[r] + r;
                while (!numNext.empty()) {
                    int u = numNext.back();
                    if (val <= nextId[u] + u) numNext.pop_back();
                    else break;
                }
                numNext.push_back(r);

//                cout << "* " << r << ' ' << nextId[r] + r << endl;
//                if (l == 7) {
//                    cout << "* * *" << endl;
//                    cout << l << ' ' << r << "    " << *numNext.begin() - l << endl;

//                    cout << "* * *" << endl;
//                }
                int u = numNext.front();
                val = nextId[u] + u;

                if ((r - l + 1) * 2 <= (val - l) - l + 1) r ++;
                else break;
            }
            int u = numNext.front();
            ll val = nextId[u] + u;
            if (r < l) continue;
            if ((r - l) * 2 > (val - l) - l + 1) continue;

            int lastR = (r - 1) + (r - l);
            if (lastR < n && a[lastR + 1] <= numX) lastR ++;

            int cnt = lastR - l + 1;
//            cout << l << ' ' << r << "  " << lastR << ' ' << cnt << endl;

            ans += Sum(l, lastR) - 1LL * a[l] * cnt;

//            cout << "   " << ans << endl;
//            cout << endl;
        }

        cout << ans << '\n';
//        cout << endl;
    }
}


int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    process();

    return 0;
}

