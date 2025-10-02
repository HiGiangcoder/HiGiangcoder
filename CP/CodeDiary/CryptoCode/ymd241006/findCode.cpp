#include<bits/stdc++.h>
using namespace std;

int main() {
    string s = "KSSYSBR BOAS PSBQV QFIBQV";
    for (int i = 1; i < 26; i ++) {
        for (char &c : s) {
            c ++;
            if (c > 'Z') c -= 26;
        }
        cout << s << endl;
    }
    return 0;
}
