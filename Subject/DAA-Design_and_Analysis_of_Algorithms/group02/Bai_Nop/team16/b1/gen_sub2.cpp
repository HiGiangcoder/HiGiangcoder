#include <bits/stdc++.h>
#define int long long
using namespace std;
struct RNG{ mt19937_64 g; RNG(long long s){g.seed(s);} long long pick(long long L,long long R){uniform_int_distribution<long long>d(L,R);return d(g);} };

int32_t main(int argc,char**argv){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if (argc<3){ cerr<<"Usage: gen_sub1 <type 1..4> <seed>\n"; return 1; }
    int type=atoi(argv[1]); long long seed=atoll(argv[2]); RNG R(seed);

    int n= (type==1? (int)R.pick(1001,100000) :
            type==2? (int)R.pick(100000,100000) :
            type==3? (int)R.pick(90000,100000) :
                     (int)R.pick(100000,100000));
    cout << n << "\n";
    for (int i=0;i<n;i++){
        long long v;
        if (type == 1) v = (int)R.pick(-100000, 100000);
        else if (type == 2) v = (int)R.pick(-100000, -99000);
        else if (type == 3) v = (int)R.pick(99000, 100000);
        else v = (int)R.pick(-100000, 100000);
        cout << v << " ";
    }
    cout << "\n";
    return 0;
}
