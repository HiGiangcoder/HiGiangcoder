#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
int g[MAXN + 36][MAXN + 36];

void genCircleGraph(){
    int n , m;
    n = rnd.next(10, 12);
    m = n - 1;

    vector<int> nodes;

    for(int i = 1 ; i <= n ; i++)
        nodes.push_back(i);

    shuffle(nodes.begin() , nodes.end(), mt19937(rnd.next(0, INT_MAX)));

    cout << n << " " << m + 1 << endl;
    for(int i = 1 ; i < nodes.size() ; i++){
        cout << nodes[i - 1] << " " << nodes[i] << endl;
        g[nodes[i - 1]][nodes[i]] = 1;
        g[nodes[i]][nodes[i - 1]] = 1;
    }
    cout << nodes.back() << " " << nodes[0] << endl;
}

void genBamBooGraph(){
    int n , m;
    n = rnd.next(10, 12);
    m = n - 1;

    vector<int> nodes;

    for(int i = 1 ; i <= n ; i++)
        nodes.push_back(i);

    shuffle(nodes.begin() , nodes.end());

    cout << n << " " << m << endl;
    for(int i = 1 ; i < nodes.size() ; i++){
        cout << nodes[i - 1] << " " << nodes[i] << endl;
        g[nodes[i - 1]][nodes[i]] = 1;
        g[nodes[i]][nodes[i - 1]] = 1;
    }
}

void genFullGraph(int nL, int nR, bool notCenter = true){
    if (notCenter){
        int n , m;
        n = rnd.next(nL , nR);
        m = n * (n - 1) / 2;
        
        cout << n << " " << m << endl;
        for(int i = 1 ; i <= n ; i++)
            for(int j = i + 1 ; j <= n ; j++)
                cout << i << " " << j << endl;
    }
    else{
        int n = rnd.next(nL, nR);
        int m = (n - 1)*(n - 2)/2;
        
        cout << n << ' ' << m << '\n';
        vector<int> node;
        for (int i=1;i<= n;i++ )
            node.push_back(i);
        shuffle(node.begin(), node.end(), mt19937(rnd.next(0, INT_MAX)));

        for (int i=1;i< n;i++ )
            for (int j=i+1;j< n;j++ )
                cout << node[i] << ' ' << node[j] << '\n';
    }
}

void genUnconnectedGraph(){
    int n , m;
    n = rnd.next(11 , 12);
    m = n - 2;

    vector<int> nodes;

    for(int i = 1 ; i <= n ; i++)
        nodes.push_back(i);

    shuffle(nodes.begin() , nodes.end());

    int split = rnd.next(3 , n - 3);

    cout << n << " " << m << endl;

    for(int i = 1 ; i < split ; i++){
        int u = rnd.next(0 , i - 1);
        cout << nodes[u] << " " << nodes[i] << endl;
    }

    for(int i = split + 1 ; i < nodes.size() ; i++){
        int u = rnd.next(split , i - 1);
        cout << nodes[u] << " " << nodes[i] << endl;
    }
}

void genEmptyGraph(){
    int n = rnd.next(1 , 12);
    cout << n << " " << 0 << endl;
}

void genRandomGraph(int nL, int nR){
    int n , m;
    n = rnd.next(nL , nR);
    m = rnd.next(n - 1 , n * (n - 1) / 2);

    vector<int> nodes;

    for(int i = 1 ; i <= n ; i++)
        nodes.push_back(i);

    shuffle(nodes.begin() , nodes.end(), mt19937(rnd.next(0, INT_MAX)));

    cout << n << " " << m << endl;
    for(int i = 1 ; i < nodes.size() ; i++){
        cout << nodes[i - 1] << " " << nodes[i] << endl;
        g[nodes[i - 1]][nodes[i]] = 1;
        g[nodes[i]][nodes[i - 1]] = 1;
    }

    vector<pair<int , int>> left_edges;
    for(int i = 1 ; i <= n ; i++)
        for(int j = i + 1 ; j <= n ; j++)
            if (!g[i][j] && !g[j][i]){
                left_edges.push_back({i , j});
                g[i][j] = g[j][i] = 1;
            }

    shuffle(left_edges.begin() , left_edges.end(), mt19937(rnd.next(0, INT_MAX)));        

    int left = m - n + 1;
    for(int i = 0 ; i < left ; i++){
        cout << left_edges[i].first << " " << left_edges[i].second << endl;
    }
}

void genNormalCase() {
    int n , m;
    n = rnd.next(8 , 12);
    m = rnd.next(n - 1 , n * (n - 1) / 2);

    vector<int> nodes;

    for(int i = 1 ; i <= n ; i++)
        nodes.push_back(i);

    shuffle(nodes.begin() , nodes.end(), mt19937(rnd.next(0, INT_MAX)));

    cout << n << " " << m << endl;
    for(int i = 1 ; i < nodes.size() ; i++){
        cout << nodes[i - 1] << " " << nodes[i] << endl;
        g[nodes[i - 1]][nodes[i]] = 1;
        g[nodes[i]][nodes[i - 1]] = 1;
    }

    vector<pair<int , int>> left_edges;
    for(int i = 1 ; i <= n ; i++)
        for(int j = i + 1 ; j <= n ; j++)
            if (!g[i][j] && !g[j][i]){
                left_edges.push_back({i , j});
                g[i][j] = g[j][i] = 1;
            }

    shuffle(left_edges.begin() , left_edges.end(), mt19937(rnd.next(0, INT_MAX)));        

    int left = m - n + 1;
    for(int i = 0 ; i < left ; i++){
        cout << left_edges[i].first << " " << left_edges[i].second << endl;
    }
}

void genSpecialCase(int s) {
    if (s % 4 == 0)
        genCircleGraph();
    else if (s % 4 == 1)
        genBamBooGraph();
    else if (s % 4 == 2)
        genFullGraph(7, 12);
    else genUnconnectedGraph();
}

void genEdgeCase(int s) {
    if (s & 1)
        genEmptyGraph();
    else genRandomGraph(1, 5);
}

void genStressCase(int s) {
    if (s % 3 == 0)
        genFullGraph(MAXN-2,MAXN);
    else if (s % 3 == 1)
        genRandomGraph(MAXN, MAXN);
    else
        genFullGraph(MAXN, MAXN, false);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rnd.setSeed(seed);
    
    if (type == 1) genNormalCase();
    else if (type == 2) genSpecialCase(seed);
    else if (type == 3) genEdgeCase(seed);
    else genStressCase(seed);
    return 0;
}
