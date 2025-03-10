// #include "testlib.h"
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef long double ld;
 
string NAME; /// NAME PROBLEM
int NTEST = 100;
 
mt19937_64 rngll(chrono :: steady_clock :: now().time_since_epoch().count());
ll random(ll l, ll r) {
    // return rnd.next(l, r);
    return uniform_int_distribution<ll>(l, r)(rngll);
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
    if (_iTest < testMax) {
        ll d = __lg(r - l + 1) + 1;
        d = d * (_iTest - numtest_L + 1) / (min(numtest_R, testMax - 1) - numtest_L + 1);
        return random(l, l + min(r - l, 1LL << d));
    }
    else return r;
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
    string NAME_Dir = NAME + "_dir";
    system(("rm -rf " + NAME_Dir).c_str()); /// restore directory 
    system(("mkdir " + NAME_Dir).c_str()); /// make directory
 
    for (int iTest = 1; iTest <= NTEST; iTest ++) {
        _iTest = iTest;
        cerr << "--------------------------------------------\n\n\n";
        cerr << "TESTCASE: " << iTest << endl;
 
        FILE *fp = freopen((NAME + ".inp").c_str(), "w", stdout);
        make_test(iTest);
        fclose(fp);
 
        if (system(("./" + NAME).c_str()) != 0) {
            cerr << "Run file " + NAME + " error" << endl;
            return 0;
        }
        cerr << "Run file " + NAME + " successfull" << endl;
 
        /// copy file inp&out to folder NAME
        string strNumTest = to_string(iTest);
        while (strNumTest.length() < to_string(NTEST).length()) strNumTest = "0" + strNumTest;
        string folderTest = NAME_Dir + '/' + NAME + strNumTest;
        system(("mkdir " + folderTest).c_str());
        system(("cp " + NAME + ".inp " + folderTest + "/" + NAME + ".inp").c_str());
        system(("cp " + NAME + ".out " + folderTest + + "/" + NAME + ".out").c_str());
    }
    return 0;
}
 

bool Sub(int persentLeft, int persentRight) {
    double res = double(_iTest) / double(NTEST) * 100;
    if (persentLeft <= res && res <= persentRight) return true;
    return false;
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
