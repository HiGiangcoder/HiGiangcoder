#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Wrapper cho rnd
class RandomWrapper {
public:
    using result_type = unsigned int;
    result_type operator()() { return rnd.next(min(), max()); }
    static constexpr result_type min() { return 0u; }
    static constexpr result_type max() { return numeric_limits<result_type>::max(); }
    void setSeed(int s) { rnd.setSeed(s); }
    int next(int l, int r) { return rnd.next(l, r); }
};
RandomWrapper myrnd;

const int MAXN = 12;
const int MAXM = MAXN*(MAXN-1)/2;

void printGraph(int n, const set<pair<int,int>>& edges) {
    int m = edges.size();
    ensure(m <= MAXM);
    // Bỏ qua trường hợp m==0 cho n>1
    ensure(n==1 || m > 0);
    cout << n << " " << m << "\n";
    for (auto &e : edges) {
        cout << e.first << " " << e.second << "\n";
    }
}

void genHamiltonian(int n) {
    vector<int> path(n);
    iota(path.begin(), path.end(), 1);
    shuffle(path.begin(), path.end(), myrnd);

    vector<pair<int,int>> extras;
    extras.reserve(MAXM - (n-1));
    for(int u=1;u<=n;u++)
      for(int v=u+1;v<=n;v++)
        extras.emplace_back(u,v);

    // Giữ lại đường Hamilton
    set<pair<int,int>> edges;
    for(int i=0;i+1<n;i++){
      int u=min(path[i],path[i+1]), v=max(path[i],path[i+1]);
      edges.insert({u,v});
      extras.erase(find(extras.begin(),extras.end(),make_pair(u,v)));
    }
    // Thêm cạnh phụ ngẫu nhiên
    int extra = myrnd.next(0, extras.size());
    shuffle(extras.begin(), extras.end(), myrnd);
    for(int i=0;i<extra;i++)
      edges.insert(extras[i]);

    printGraph(n, edges);
}

void genNonHamiltonian(int n) {
    // Chia thành 2 thành phần, đảm bảo mỗi thành phần có ít nhất 1 cạnh
    int k = myrnd.next(2, n-1); // k>=2 để có cạnh trong thành phần
    vector<int> part(n);
    for(int i=0;i<n;i++) part[i] = (i < k);

    set<pair<int,int>> edges;
    for(int i=1;i<=n;i++)
      for(int j=i+1;j<=n;j++)
        if(part[i-1] == part[j-1])
          edges.insert({i,j});
    // Đảm bảo mỗi thành phần thực sự có cạnh
    ensure(edges.size() > 0);

    printGraph(n, edges);
}

void genGreedyKiller(int n) {
    set<pair<int,int>> edges;
    // đảm bảo n>=3 và m>0
    edges.insert({1,2});
    edges.insert({1,n});
    for(int i=2;i<n-1;i++) edges.insert({i,i+1});
    edges.insert({n-1,n});
    printGraph(n, edges);
}

void genStarWithPendant(int n) {
    set<pair<int,int>> edges;
    // tạo hình sao + pendant
    for(int i=2;i<=n-1;i++) edges.insert({1,i});
    edges.insert({n-1,n});
    edges.insert({1,n});
    printGraph(n, edges);
}

void genNormalCase() {
    int n = myrnd.next(3, MAXN);
    if(myrnd.next(0,1)==0) genHamiltonian(n);
    else genNonHamiltonian(n);
}

void genSpecialCase() {
    int n = myrnd.next(7, MAXN);
    int t = myrnd.next(0,2);
    if(t==0) {
        // clique + pendant
        set<pair<int,int>> edges;
        for(int i=1;i<n;i++)
          for(int j=i+1;j<n;j++)
            edges.insert({i,j});
        int leaf = myrnd.next(1,n-1);
        edges.insert({min(leaf,n), max(leaf,n)});
        printGraph(n, edges);
    } else if(t==1) {
        genGreedyKiller(n);
    } else {
        genStarWithPendant(n);
    }
}

void genEdgeCase() {
    // Chỉ sinh n=2,m=1
    printGraph(2, set<pair<int,int>>{{1,2}});
}

void genStressCase() {
    int n = MAXN;
    int t = myrnd.next(0,3);
    if(t==0) genHamiltonian(n);
    else if(t==1) genNonHamiltonian(n);
    else if(t==2) genGreedyKiller(n);
    else genStarWithPendant(n);
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    myrnd.setSeed(atoi(argv[2]));
    if(type==1) genNormalCase();
    else if(type==2) genSpecialCase();
    else if(type==3) genEdgeCase();
    else genStressCase();
    return 0;
}
