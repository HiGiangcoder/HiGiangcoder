#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long n,m; if(!(cin>>n>>m)){ cerr<<"missing n m\n"; return 1; }
    if (n<2 || n>100000){ cerr<<"n out of range\n"; return 1; }
    if (m<0 || m>200000){ cerr<<"m out of range\n"; return 1; }
    for (long long i=0;i<m;i++){
        long long u,v,w; if(!(cin>>u>>v>>w)){ cerr<<"missing edge\n"; return 1; }
        if (u<1||u>n||v<1||v>n){ cerr<<"u/v out of range\n"; return 1; }
        if (w<1||w>1000000000LL){ cerr<<"w out of range\n"; return 1; }
    }
    string extra; if (cin>>extra){ cerr<<"trailing tokens\n"; return 1; }
    return 0;
}
