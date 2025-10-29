#include <bits/stdc++.h>
#define int long long
using namespace std;
struct RNG{ mt19937_64 g; RNG(long long s){g.seed(s);} long long pick(long long L,long long R){uniform_int_distribution<long long>d(L,R);return d(g);} };

int32_t main(int argc,char**argv){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    if(argc<3){ cerr<<"Usage: gen_sub1 <type 1..4> <seed>\n"; return 1; }
    int type=atoi(argv[1]); long long seed=atoll(argv[2]); RNG R(seed);

    int n = (int)(type==1?  (R.pick(2,10)):
                  type==2?  (R.pick(2,10)):
                  type==3?  (R.pick(800,1000)):
                            (R.pick(800,1000)));
    int m;
    if (type==1) m=(int)R.pick(0,5);
    else if (type==2) m=(int)R.pick(18,20);
    else if (type==3) m=(int)R.pick(0,20);
    else m=(int)R.pick(180000, 200000);

    cout << n << " " << m << "\n";
    // đôi khi đảm bảo có đường 1->n
    bool forcePath = (type==2 && n>=2);
    vector<tuple<int,int,int>> E;
    if (forcePath){
        for (int i=1;i<n;i++){
            int w=(int)R.pick(10000000,1000000000);
            E.emplace_back(i,i+1,w);
        }
        int extra = max(0LL, m-(long long)E.size());
        for(int i=0;i<extra;i++){
            int u=(int)R.pick(1,n), v=(int)R.pick(1,n), w=(int)R.pick(10000000,1000000000);
            E.emplace_back(u,v,w);
        }
    } else {
        for (int i=0;i<m;i++){
            int u=(int)R.pick(1,n), v=(int)R.pick(1,n), w=(int)R.pick(10000000,1000000000);
            E.emplace_back(u,v,w);
        }
    }
    for (auto &e:E){ int u,v,w; tie(u,v,w)=e; cout<<u<<" "<<v<<" "<<w<<"\n"; }
    return 0;
}
