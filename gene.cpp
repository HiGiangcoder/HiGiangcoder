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

void Setup() {
    NTEST = 20;
    NAME = "";
}
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */

void make_test(int iTest) {
}
