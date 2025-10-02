#include<bits/stdc++.h>
using namespace std;

int main() {
    while (true) {
        string s; cin >> s;
        int num = 0;
        if (s.length() == 1) {
            num = (s[0] - '0');
            num = 3 * (num - 1) + 2;
        }
        else if (s[0] == '-') {
            num = (s[1] - '0');
            num = 3 * (num - 1) + 1;
        }
        else {
            num = (s[0] - '0');
            num = 3 * (num - 1) + 3;
        }

        cout << char(num + 'A' - 1) << '\n'; cout << endl;
    }
}
