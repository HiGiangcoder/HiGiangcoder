/* sort template*/
#include <bits/stdc++.h>
using namespace std;

#define fi  first
#define se  second
typedef long long ll;
typedef pair<int, int> ii;

template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 7; 

int n;
int a[MAX];

ll ans(0);
int f[MAX];
int posVal[MAX];
int numUnique[MAX];

int wayInValUnique[MAX];
void update(int val, int pos, int l, int r) {
    pos -= l - 1;
    for(; pos >= 1; pos -= pos & -pos) wayInValUnique[pos] -= val;
}
int get(int pos, int l, int r) {
    int res(0);
    pos -= l - 1;
    for(; pos <= r - l + 1; pos += pos & -pos) res += wayInValUnique[pos];
    return res;
}


void Calc(int l = 1, int r = n) {
    if (l >= r) return;
    int mid = (l + r) / 2;

    cout << "-- " << l << ' ' << r << endl;

    for (int i = l; i <= mid; i ++) {
        posVal[a[i]] = 0;
        f[i] = 0;
        numUnique[i] = 0;
    }

    for (int i = mid; i >= l; i --) {
        if (posVal[a[i]] == 0) {
            posVal[a[i]] = i;
            numUnique[i] = 1;
        }
        else if (posVal[a[i]] > 0) {
            f[i + 1] ++;
            f[posVal[a[i]]] --; 
            posVal[a[i]] = -1;
        }
    }
    for (int i = l; i <= mid; i ++) if (posVal[a[i]] > 0) {
        f[l] ++;
        f[posVal[a[i]]] --;
        cout << i << ' ' << f[l] << "    " << posVal[a[i]] << ' ' << f[posVal[a[i]]] << endl;

        posVal[a[i]] = -1;
    }

    for (int i = l; i <= r; i ++) {
        posVal[a[i]] = 0;
        wayInValUnique[i - l + 1] = 0;
    }

    for (int i = l; i <= mid; i ++) {
        if (i > l) f[i] += f[i - 1];
//        cout << f[i] << ' ';
        if (f[i] > 0 && numUnique[i]) {
            update(i, 1, l, r);
//            cout << i << ' ';
        }
        posVal[a[i]] = i;
    }
//    cout << endl;


    for (int i = mid + 1; i <= r; i ++) {
        int pre = posVal[a[i]] + 1;
        if (posVal[a[i]] == 0) {
            pre = l;
        }
        else if (posVal[a[i]] <= mid) {
            update(-1, posVal[a[i]], l, r);
        }

        if (l <= mid) ans += get(pre, l, r);

        posVal[a[i]] = i;
    }

    cout << endl;

    Calc(l, mid);
    Calc(mid + 1, r);
}

void process() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];

    Calc();

    cout << ans;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    process();

    return 0;
}

