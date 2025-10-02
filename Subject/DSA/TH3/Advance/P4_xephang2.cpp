#include<bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 7;

int n, m;

int val[MAX];
map<int, int> mp;

int main() {
    ios_base ::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }

    cin >> n >> m;

    for (int i = n; i >= 1; i --) {
        val[i] = -i + 1;
        mp[val[i]] = i;
    }

    for (int i = 1; i <= m; i ++) {
        int student; cin >> student;        

        mp.erase(val[student]);
        mp[i] = student;
        val[student] = i;

        map<int, int>::iterator it = mp.begin();
        cout << it -> second << " "; // Print the last element in the map
    }


    return 0;
}