#include <bits/stdc++.h>
using namespace std;

// Bài toán mẫu: cho mảng a[] gồm n phần tử, q truy vấn (l, r).
// Mỗi truy vấn in ra tổng các phần tử từ l đến r (1-based).
// -> Code trâu: O(n * q)

random_device rd;

mt19937 rng(rd());


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    bool edge[n+1][n+1];
    memset(edge, 0, sizeof(edge));

    while(m--){
        int x, y;
        cin >> x >> y;
        edge[x][y] = edge[y][x] = 1;
    }

    vector<int> a(n);
    iota(a.begin(), a.end(), 1); // a = [1, 2, ..., n]

    bool have = 0;
    do{
        bool ok=1;
        for(int i=0; i+1<a.size();++i)
            if(!edge[a[i]][a[i+1]]){
                ok = 0;
                break;
            }
        if(ok){
            have = 1;
            break;
        }
    }while(next_permutation(a.begin(), a.end()));


    if(have)
        for(int i=0;i<a.size();++i)
            cout << a[i] << " \n"[i+1==a.size()];
    else cout << -1;



   
    return 0;
}
