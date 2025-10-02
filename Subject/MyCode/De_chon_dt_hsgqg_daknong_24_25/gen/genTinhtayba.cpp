/*
#include "testlib.h"
#define random_shuffle shuffle
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

string NAME; /// NAME PROBLEM
int NTEST;

mt19937_64 rngll(chrono :: steady_clock :: now().time_since_epoch().count());
ll random(ll l, ll r) {
    // return rnd.next(l, r);
    return uniform_int_distribution<ll>(l, r)(rngll);
}

ll wrandom(ll l, ll r, ll k) {
    if (k == 0) return random(l, r);
    if (k > 0) return max(random(l, r), wrandom(l, r, k - 1));
    if (k < 0) return min(random(l, r), wrandom(l, r, k + 1));
}
ll lograndom(ll l, ll r, ll k) {
    if (k == 0) return random(l, r);
    if (k > 0) return random(lograndom(l, r, k - 1), r);
    if (k < 0) return random(l, lograndom(l, r, k + 1));
}

////                                                                      
#define MOD 1000000007
#define fi first
#define se second
#define BIT(n) (1 << (n))
#define GETBIT(mask, n) (((mask) >> (n)) & 1)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i ++)

const int numinf = 0x3f3f3f3f;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

template<class T> bool minimize(T &a, const T &b) {
    if (a > b) {a = b; return true;}
    return false;
}
template<class T> bool maximize(T &a, const T &b) {
    if (a < b) {a = b; return true;}
    return false;
}

////                                                                      

void make_test(int);

int _iTest;
ll getRandom(ll l, ll r, int numtest_L = 1, int numtest_R = NTEST, int testMax = 999) {
    testMax = numtest_R + testMax;
    if (_iTest < testMax) {
        ll d = __lg(r - l + 1) + 1;
        d = d * (_iTest - numtest_L + 1) / (min(numtest_R, testMax - 1) - numtest_L + 1);
        return random(l, l + min(r - l, 1LL << d));
    }
    else return r;
}

namespace PrepareRand {
    int numtestL;
    int numtestR;
    int testMax;

    void SetUp(int testL, int testR, int testMax = 0) {
        numtestL = testL;
        numtestR = testR;
        testMax = testMax;
    }
}
ll GetRand(ll l, ll r, int testMax = 1) {
    int numtest_L = PrepareRand :: numtestL;
    int numtest_R = PrepareRand :: numtestR;

    if (testMax > 0) testMax = PrepareRand :: testMax;

    return getRandom(l, r, numtest_L, numtest_R, testMax);
}

int Sub(int percent) {
    return NTEST * percent / 100;
}

void Setup();

int main(int argc, char *argv[]) {
    Setup();

/*
    registerGen(argc, argv, 1);
    _iTest = opt<int>(1);
    NTEST = opt<int>(2);
    make_test(_iTest);
    return 0;
*/
    

    if (system(("g++ " + NAME + ".cpp -o " + NAME).c_str()) != 0) {
        cerr << "- Compiler file " + NAME + " failure\n";
        return 0;
    } cerr << "- Compiler file " + NAME + " successfull!\n";

/*  --------------------------------------------------------- */

    system(("rd /s /q " + NAME).c_str()); /// restore directory 
    system(("MD " + NAME).c_str()); /// make directory

    for (int iTest = 1; iTest <= NTEST; iTest ++) {
        _iTest = iTest;
        cerr << "--------------------------------------------\n\n\n";
        cerr << "TESTCASE: " << iTest << endl;

        FILE *fp = freopen((NAME + ".inp").c_str(), "w", stdout);
        make_test(iTest);
        fclose(fp);

        if (system((NAME + ".exe").c_str()) != 0) {
            cerr << "Run file " + NAME + " error" << endl;
            return 0;
        }
        cerr << "Run file " + NAME + " successfull" << endl;

        /// copy file inp&out to folder NAME
        string strNumTest = to_string(iTest);
        while (strNumTest.length() < to_string(NTEST).length()) strNumTest = "0" + strNumTest;
        string folderTest = NAME + '\\' + NAME + strNumTest;

        system(("MD " + folderTest).c_str());
        system(("Copy \"" + NAME + ".inp\" \"" + folderTest + "\" /y").c_str());
        system(("Copy \"" + NAME + ".out\" \"" + folderTest + "\" /y").c_str());
    }
    return 0;
}


/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */

vector<int> prime;
bool freprime[int(2e5 + 7)];

void Setup() {
    for (int i = 2; i <= 2e5; i ++) if (!freprime[i]) {
        prime.push_back(i);
        for (ll j = 1LL * i * i; j <= 2e5; j += i) {
            freprime[j] = true;
        }
    }
    NTEST = 200;
    NAME = "TINHTAYBA";
}
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */

const int MAX = 2e5 + 7;

int m;
int p[MAX];

void make_test(int iTest) {
    if (iTest <= Sub(30)) {
        if (iTest <= 15) {
            int n = getRandom(2, 2e5, -Sub(15), Sub(15), 0);
            vector<int> num;
            for (int i = 2; i <= n; i ++) if (n % i == 0) {
                while (n % i == 0) {
                    n /= i;
                    num.push_back(i);
                }
            }
            random_shuffle(num.begin(), num.end());

            m = num.size();
            for (int i = 1; i <= m; i ++) p[i] = num[i - 1];
        }
        else {
            m = 0;
            int num = 1;
            while (true) {
                int x = prime[random(0, 9)];
                if (num * x <= 2e5) num *= x;
                else break;
                p[++m] = x;
            }
        }
    }
    else {
        m = getRandom(1e3, 1e5, 1, NTEST, - (NTEST - Sub(30)) / 2);
        int numPrime = lograndom(1, prime.size(), iTest % 2 ? 0 : 2);
        vector<int> listPrime = prime;
        random_shuffle(listPrime.begin(), listPrime.end());
        for (int i = 1; i <= m; i ++) {
            p[i] = listPrime[random(0, numPrime - 1)];
        }
    }

    cout << m << '\n';
    for (int i = 1; i <= m; i ++) cout << p[i] << " \n"[i == m];
}