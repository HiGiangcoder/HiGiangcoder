#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

random_device rd;

mt19937 rng(rd());

int Rand(int l, int r){
    return l + rng()%(r-l+1);
}

void have_path(int n, int m){

    if(m == 0) return void();

    //generate a random halminton path
    vector<int> a(n);
    iota(a.begin(), a.end(), 1); // a = [1, 2, ..., n]

    shuffle(a.begin(), a.end(), rng);
    //adding some edge to the halminton path
    if(n-1 <= m){
        bool check[n+1][n+1];
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)
                check[i][j] = 0;
        for(int i=0;i+1<a.size();++i){
            int x = min(a[i], a[i+1]);
            int y = max(a[i], a[i+1]);
            check[x][y] = 1;
    
        }

        m -= n - 1;


        vector<pair<int,int>> p;

        for(int i=1;i<=n && m > 0;++i)
            for(int j=i+1;j<=n && m > 0;++j){
                if(check[i][j] || i==j) continue;
                p.push_back({i, j});
            }

        shuffle(p.begin(), p.end(), rng);

        for(int i=0;i<m;++i)
            check[p[i].first][p[i].second] = 1;
        
        
        for(int i=1;i<=n;++i)
            for(int j=i+1;j<=n;++j)
                if(check[i][j])
                    cout << i << " " << j << endl;
    }

    //in the case where n-1 > m, we can't find the halminton path
    else {
        vector<pair<int,int>> p;


        //randomly select m edges from n*(n-1)/2 edges
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(i!=j)
                p.push_back({i, j});
        
        shuffle(p.begin(), p.end(), rng);

        for(int i=0;i<m;++i)
            cout << p[i].first << " " << p[i].second << endl;
    }
}


void have_no_path(int n, int m){

    if(m == 0) return void();


    //the graph is not connected 
    vector<int> a(n);
    iota(a.begin(), a.end(), 1); // a = [1, 2, ..., n]

    shuffle(a.begin(), a.end(), rng);

    bool check[n+1][n+1];
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n;++j)   
            check[i][j] = 0;
    vector<pair<int,int>> p;
    for(int i=1;i<n;++i)
        for(int j=i+1;j<n;++j)
            if(i!=j)
                p.push_back({min(a[i], a[j]),max(a[i], a[j])});
    
    
    shuffle(p.begin(), p.end(), rng);

    for(int i=0;i<m;++i)
        check[p[i].first][p[i].second] = 1;
    
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)
            if(check[i][j])
                cout<<i<<" "<<j<<endl;
   
}




void genNormalCase() {
    // int n = rnd.next(10, MAXN);
    // int q = rnd.next(5, MAXN);
    // cout << n << " " << q << "\n";
    // for (int i=0;i<n;i++) cout << rnd.next(-100, 100) << " \n"[i==n-1];
    // while(q--){
    //     int l = rnd.next(1, n);
    //     int r = rnd.next(l, n);
    //     cout << l << " " << r << "\n";
    // }

    int n = Rand(1, 12);
    int m;

    cout << n  << " ";

    int k = Rand(0, 1);

    if(k)
        m = Rand(n-1, n * (n-1)/2),
        cout << m << endl,
        have_path(n, m);
    else 
        m = Rand(0, (n-1)*(n-2)/2),
        cout << m << endl,
        have_no_path(n, m);
}

    

void multiple_path(int n, int m){
    vector<int> a(n);
    iota(a.begin(), a.end(), 1); // a = [1, 2, ..., n]

    shuffle(a.begin(), a.end(), rng);

    bool check[n+1][n+1];
    memset(check, 0, sizeof(check)); 

    for(int i=0;i+1<a.size();++i){
        int x = min(a[i], a[i+1]);
        int y = max(a[i], a[i+1]);
        check[x][y] = 1;
    }
    
    shuffle(a.begin(), a.end(), rng);

    for(int i=0;i+1<a.size();++i){
        int x = min(a[i], a[i+1]);
        int y = max(a[i], a[i+1]);
        check[x][y] = 1;
    }

    vector<pair<int,int>> p;


    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)
            if(check[i][j])
                m-=check[i][j];
            else
                p.push_back({i, j});
    
    shuffle(p.begin(), p.end(), rng);

    for(int i=0;i<m;++i)
        check[p[i].first][p[i].second] = 1;
    
    
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)
            if(check[i][j])
                cout<<i<<" "<<j<<endl;
    

    
    
}


void genSpecialCase() {
    int n = Rand(5, 12);
    int m = Rand((n-1)*2, n*(n-1)/2);
    cout << n << " " << m << "\n";

    multiple_path(n, m);
    
}

void genEdgeCase() {
    int n = Rand(0,1)?1:12;
    int m = Rand(0,1)?0:n*(n-1)/2;
    cout << n << " " << m << "\n";
    int k = Rand(0,1);
    have_path(n, m);
}

void genStressCase() {
    int n = 12;
    int m = Rand(n-1, n*(n-1)/2 - n);
    cout << n << " " << m << "\n";
    
    int k = Rand(0,1);

    if(k) have_path(n, m);
    else have_no_path(n, m);
}

int main(int argc, char* argv[]) 
//int main()
{
     registerGen(argc, argv, 1);
     int seed = atoi(argv[1]);
     rnd.setSeed(seed);

     int type = (argc > 1) ? atoi(argv[1]) : 1;
     if (type == 1) genNormalCase();
     else if (type == 2) genSpecialCase();
     else if (type == 3) genEdgeCase();
     else genStressCase();




    return 0;
}
