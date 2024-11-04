#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono :: steady_clock :: now().time_since_epoch().count());
int random(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

void Mode1();
void Mode2();

int main() {
    cout <<  "---------- Master Mind ----------" << endl;
    cout << "Please select mode" << endl;
    cout << "1. You is player" << endl;
    cout << "2. Computer is player" << endl;

    int mode; cin >> mode;

    while(true) {
        if (mode == 1) Mode1();
        else if (mode == 2) Mode2();
        else {
            cout << "Please try again!" << endl;
            continue;
        }
        break;
    }

    return 0;
}

void Mode1() {
    int a[4];
    for (int i = 0; i < 4; i ++) a[i] = random(1, 9);

    cout << "You need to enter a string of characters with a length of 4, with each character belonging to the natural numbers from 1 to 9." << endl;

    int inp[4];
    int ans[4];
    int cnttry(0);

    while (true) {
        cout << "tried: " << cnttry << endl;
        cout << "Please write your answer" << endl;
        cnttry ++;

        // input
        while (true) {
            string s;
            cin >> s;
            if (s.length() != 4) {
                cout << "Please try again!" << endl;
                continue;
            }

            bool ok = true;
            for (int i = 0; i < 4; i ++) {
                if ('1' <= s[i] && s[i] <= '9') {
                    inp[i] = s[i] - '0';
                }
                else {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                cout << "Please try again!" << endl;
                continue;
            }

            break;
        }

        int cntcolor[10];
        memset(cntcolor, 0, sizeof(cntcolor));

        for (int i = 0; i < 4; i ++) {
            ans[i] = 0;
            if (inp[i] == a[i]) {
                ans[i] = 2;
            }
            else {
                cntcolor[a[i]] ++;
            }
        }

        for (int i = 0; i < 4; i ++) if (ans[i] == 0) {
            if (cntcolor[inp[i]] > 0) {
                ans[i] = 1;
                cntcolor[inp[i]] --;
            }
        }

        for (int i = 0; i < 4; i ++) {
            cout << i << ". ";
            if (ans[i] == 0) cout << "Wrong";
            if (ans[i] == 1) cout << "Part";
            if (ans[i] == 2) cout << "Ok";
            cout << "    ";
        }
        cout << endl;

        bool ok = true;
        for (int i = 0; i < 4; i ++) if (ans[i]) ok = false;
        if (ok) break;
    }

    cout << "You are win!" << endl;
}

void Mode2() {
    cout << "p: part" << endl;
    cout << "o: ok" << endl;
    cout << "w: wrong" << endl;

    int numcnt[10]; memset(numcnt, 0, sizeof(numcnt));
    int ans[5]; memset(ans, 0, sizeof(ans));
    int valinp[4], valout[4];

    const int inf = 10;
    numcnt[0] = inf;

    while (true) {
        int cnt(0);
        for (int i = 0; i < 4; i ++) if (ans[i] == 0) cnt ++;
        ans[4] = 0;
        for (int i = 3; i >= 0; i --) if (ans[i] / 10 == 0) {
            for (int j = i + 1; j <= 4; j ++) if (ans[j] / 10 == 0) {
                swap(ans[j], ans[i]);
                break;
            }
        }
        for (int i = 0; i < 4; i ++) if (ans[i] / 10 == 0) {
            swap(ans[i], ans[4]);
            break;
        }

        vector<int> num;
        int ptr = 0;
        for (int i = 1; i <= 9; i ++) if (numcnt[i] < numcnt[ptr]) ptr = i;
        while (num.size() < cnt) {
            bool okbreak = true;
            for (int i = 1; i <= 9; i ++) if (numcnt[ptr] < 4) okbreak = false;
            if (okbreak) break;

            if (numcnt[ptr] < 4) {
                numcnt[ptr] ++;
                num.push_back(ptr);
            }
            ptr ++;
        }

        int j(0);
        for (int i = 0; i < 4; i ++) {
            if (ans[i] / 10 == 1) valout[i] = ans[i] % 10;
            else if (ans[i] > 0) valout[i] = ans[i];
            else valout[i] = num[j ++];
        }

        cout << "Computer's question: " << flush;
        for (int i = 0; i < 4; i ++) cout << valout[i] << ' '; cout << endl;

        bool ok;
        string s = "";
        do {
            cout << "answer is: " << flush;
            cin >> s;
            ok = true;
            for (char c : s) {
                if (c != 'p' && c != 'o' && c != 'w') ok = false;
            }
        }while (s.length() != 4 || !ok);

        for (int i = 0; i < 4; i ++) {
            char c = s[i];
            if (c == 'o') ans[i] = 10 + valout[i];
            if (c == 'p') ans[i] = valout[i];
            if (c == 'w') {
                ans[i] = 0;
                numcnt[valout[i]] = 10;
            }
        }

        ok = true;
        for (int i = 0; i < 4; i ++) if (ans[i] / 10 == 0) ok = false;

        if (ok) break;
    }

    cout << "Computer win!" << endl;
}
