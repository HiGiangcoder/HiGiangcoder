#include<bits/stdc++.h>
using namespace std;

int num_n, num_m;
const int MAX = 1e6 + 7;

int a_n;
int a[MAX];

void Init() {
    string s; cin >> s;
    a_n = s.length();
    for (int i = a_n; i >= 1; i --) {
        a[i] = s[a_n - i] - '0';
    }
    cin >> num_n >> num_m;
}

bool Check() {
    bool ok = true;
    for (int i = 1; i <= a_n; i ++) 
        if (a[i] != a[a_n - i + 1]) ok = false;
    return ok;
}

int tmp_a[MAX];
void Update() {
    // copy to tmp_a
    for (int i = 1; i <= a_n; i ++) tmp_a[i] = a[i];

    // cal new a
    for (int i = 1; i <= a_n; i ++) a[i] = tmp_a[i] + tmp_a[a_n - i + 1];

    // rem
    for (int i = 1; i <= a_n || a[i] > 0; i ++) {
        if (i > a_n) a_n = i;

        a[i + 1] += a[i] / 10;
        a[i] = a[i] % 10;
    }
}

void Process() {
    bool ok = true;
    int num_rep = 0;

    for (int rep = 1; rep <= num_n; rep ++) {
        if (a_n > num_m) break;

        Update();
        num_rep ++;

        if (Check()) {
            ok = false;
            break;
        }
    }

    if (ok) cout << "YES\n"; 
    else cout << "NO\n";

    cout << num_rep << '\n';
    for (int i = a_n; i >= 1; i --) cout << a[i];
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    Init();
    Process();

    return 0;
}
