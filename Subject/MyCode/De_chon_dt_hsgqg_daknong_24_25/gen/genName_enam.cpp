/// generation code

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
    NAME = "NAME_ENAM";
}

int Calc(ll x) {
    int res(0);
    ll val(1);
    for (int i = 0;val * prime[i] <= x; i ++) {
        val *= prime[i];
        res = i;
    }
    return res;
}
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */

const int MAX = 1e6 + 7;

int n;
ll k;
ll a[MAX], b[MAX];

void make_test(int iTest) {
    if (iTest <= Sub(10)) {
        n = getRandom(1, 20, -NTEST, Sub(10), -Sub(5));
        ll gcd(1);
        REP(i, random(1, 3)) if (gcd * prime[i] <= 20) {
            gcd *= prime[i];
            while (random(0, 2) == 0 && gcd * prime[i] <= 20) gcd *= prime[i];
        }

        for (int i = 1; i <= n; i ++) {
            a[i] = gcd;

            REP(rep, 20) {
                int x = prime[random(0, 2)];
                if (a[i] * x <= 20) a[i] *= x;
            }
        }

        k = random(prime[2], prime[2] * 5);
    }
    else if (iTest <= Sub(30)) {
        n = getRandom(1, 1000, -NTEST, Sub(30), -Sub(10));
        ll gcd(1);
        REP(i, random(1, 5)) if (gcd * prime[i] <= 1000) {
            gcd *= prime[i];
            while (random(0, 3) == 0 && gcd * prime[i] <= 1000) gcd *= prime[i];
        }

        for (int i = 1; i <= n; i ++) {
            a[i] = gcd;

            REP(rep, 20) {
                int x = prime[random(0, 4)];
                if (a[i] * x <= 1000) a[i] *= x;
            }
        }
        k = random(prime[4], prime[4] * 5);
    }
    else if (iTest <= Sub(60)) {
        n = getRandom(1e5, 1e6, -NTEST, Sub(60), -Sub(15));
        vector<ll> listPrime;

        k = 2;
        ll gcd(1);
        REP(rep, 30) if (random(0, 2) == 0 && gcd * prime[rep] <= 1e12) {
            ll x = prime[rep];
            gcd *= x;
            maximize(k, x);
        }
        for (int i = 1; i <= n; i ++) {
            a[i] = gcd;

            REP(rep, 30) if (a[i] % prime[rep] != 0) {
                if (a[i] * prime[rep] <= 1e12) a[i] *= prime[rep];
                else break;
            }
        }
    }
    else {
        n = getRandom(1e5, 1e6, -NTEST, NTEST, -Sub(20));
        ll gcd(1);
        REP(i, random(1, 11)) if (gcd * prime[i] <= 1e12) {
            gcd *= prime[i];
            while (random(0, 3) == 0 && gcd * prime[i] <= 1e12) gcd *= prime[i];
        }

        for (int i = 1; i <= n; i ++) {
            a[i] = gcd;

            REP(rep, 30) {
                int x = prime[random(0, 10)];
                if (a[i] * x <= 1e12) a[i] *= x;
            }
        }
        k = random(prime[10], prime[10] * 5);
    }

    for (int i = 1; i <= n; i ++)
        b[i] = getRandom(1, 1e9, -Sub(10), NTEST);
    
    cout << n << ' ' << k << '\n';
    for (int i = 1; i <= n; i ++) cout << a[i] << " \n"[i == n];
    for (int i = 1; i <= n; i ++) cout << b[i] << " \n"[i == n];
}