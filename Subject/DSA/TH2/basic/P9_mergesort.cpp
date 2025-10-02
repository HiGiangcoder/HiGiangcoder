#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

#define TASK ""

class Mergesort {
private:
    void Merge(vector<int> &a, int l, int mid, int r) {
        vector<int> c;
        int i = l, j = mid + 1;
        while (i <= mid && j <= r) {
            if (a[i] < a[j]) c.push_back(a[i ++]);
            else c.push_back(a[j ++]);
        }
        while (i <= mid) c.push_back(a[i ++]);
        while (j <= r) c.push_back(a[j ++]);
        for (int i = l; i <= r; i ++) a[i] = c[i - l];
    }

    void MergeSort(vector<int> &a, int l, int r) {
        if (l >= r) return;

        int mid = (l + r) / 2;

        MergeSort(a, l, mid);
        MergeSort(a, mid + 1, r);
        Merge(a, l, mid, r);

        for (int i = 0; i < a.size(); i ++) {
            if (i == l) cout << "[ ";
            cout << a[i] << ' ';
            if (i == r) cout << "] ";
        }
        cout << '\n';
    }

public:
    vector<int> operator () (vector<int> a) {
        MergeSort(a, 0, a.size() - 1);
        return a;
    }
};


int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }

    
    int n;
    vector<int> a;
    
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        int x; cin >> x;
        a.push_back(x);
    }

    Mergesort msort;
    a = msort(a);

    return 0;
}