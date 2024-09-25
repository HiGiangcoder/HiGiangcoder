#include<bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937 rng(chrono :: steady_clock().now().time_since_epoch().count());
int random(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

string s[23];
int correct[23];
map<ll, int> mp;

struct Seed {
    string str;
    int d;

    bool Calculate() {
        ll num(0);
        for (char c : str) num = num * 10 + int(c - '0');
        if (mp.count(num)) {
            d = mp[num];
            return false;
        }
        d = 0;
        for (int i = 1; i <= 22; i ++) {
            int cnt(0);
            for (int j = 0; j < 16; j ++) cnt += str[j] == s[i][j];

            int tmp = abs(correct[i] - cnt);
            d += tmp * tmp;
        }
        mp[num] = d;
        return true;
    }
};

Seed a[16][10][10];
Seed b[int(2e7)];

int main() {
    freopen(".inp", "r", stdin);

    for (int i = 1; i <= 22; i ++) {
        cin >> s[i] >> correct[i];
    }

    for (int i = 0; i < 16; i ++) {
        for (int j = 0; j < 10; j ++) {
            for (int k = 0; k < 10; k ++) {
                string s = "";
                for (int x = 0; x < 16; x ++) s += char(random(0, 9) + '0');
                s[i] = char(j + '0');
                a[i][j][k].str = s;
                a[i][j][k].Calculate();
            }
        }
    }

    int numTrain(0);
    while (true) {
        Seed bestSeed = a[0][0][0];
        for (int i = 0; i < 16; i ++) for (int j = 0; j < 10; j ++) {
            if (bestSeed.d > a[i][j][0].d || (bestSeed.d == a[i][j][0].d && random(0, 1))) {
                bestSeed = a[i][j][0];
            }
        }

        if (bestSeed.d == 0) {
            cout << "Answer is: ";
            cout << bestSeed.str;
            exit(0);
        }
        numTrain ++;

        cout << "Number of training: " << numTrain << '\n';
        cout << "String is: " << bestSeed.str << '\n';
        cout << "distance is: " << bestSeed.d << '\n';
        cout << endl;

        int m = 0;

        for (int i = 0; i < 16; i ++) for (int i2 = 0; i2 < 10; i2 ++) {
            for (int k = 0; k < 10; k ++) {
                b[m ++] = a[i][i2][k];
                for (int j = 0; j < 16; j ++) {
                    for (char c = '0'; c <= '9'; c ++) if (c != a[i][i2][k].str[j]){

                        b[m] = a[i][i2][k];
                        b[m].str[j] = c;
                        if (b[m].Calculate())m ++;

                        while (random(0, random(0, 16)) != 0) {
                            b[m] = b[m - 1];
                            b[m].str[random(0, 15)] = char(random(0, 9) + '0');
                            if (b[m].Calculate())m ++;
                        }
                    }
                }
            }
        }
        random_shuffle(b, b + m);

        for (int i = 0; i < m; i ++) {
            b[i].Calculate();
        }
        
        for (int i = 0; i < 16; i ++) for (int i2 = 0; i2 < 10; i2 ++) {
            for (int k = 0; k < 10; k ++) {
                a[i][i2][k] = b[k];
                a[i][i2][k].d = 1e9;

                int tmp = -1;
                if (k > 0) tmp = a[i][i2][k - 1].d;
                for (int j = k; j < m; j ++) if (b[j].str[i] == i2 + '0') {
                    if(tmp < b[j].d && b[j].d < a[i][i2][k].d) {
                        a[i][i2][k] = b[j];
                        swap(b[k], b[j]);
                    }
                }
            }
        }
    }
}



