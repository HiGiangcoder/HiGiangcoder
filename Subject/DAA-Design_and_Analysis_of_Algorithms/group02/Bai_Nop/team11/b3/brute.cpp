#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.insert({u, v});
        edges.insert({v, u});
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1); // p = {1, 2, ..., n}

    do {
        bool ok = true;
        for (int i = 0; i < n - 1; ++i) {
            if (edges.find({p[i], p[i+1]}) == edges.end()) {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (int i = 0; i < n; ++i) {
                cout << p[i] << (i == n - 1 ? "" : " ");
            }
            cout << endl;
            return 0;
        }
    } while (next_permutation(p.begin(), p.end()));

    cout << -1 << endl;
    return 0;
}