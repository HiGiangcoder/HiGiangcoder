#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    // Redirect input and output
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }

    int n, m;
    cin >> n >> m;

    vector<int> calls(m);
    for (int i = 0; i < m; ++i) {
        cin >> calls[i];
    }

    set<int> called; // To track unique students called
    vector<int> result;

    // Traverse calls in reverse order
    for (int i = m - 1; i >= 0; --i) {
        if (called.find(calls[i]) == called.end()) {
            result.push_back(calls[i]);
            called.insert(calls[i]);
        }
    }

    // Add remaining students in ascending order
    for (int i = 1; i <= n; ++i) {
        if (called.find(i) == called.end()) {
            result.push_back(i);
        }
    }

    // Output the result
    for (int student : result) {
        cout << student << " ";
    }

    return 0;
}
