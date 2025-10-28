#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;

bool visited[MAXN];

vector<int> adj[MAXN];
int parent[MAXN];
int n, m;
int cnt = 0;
bool ok = 0;

vector<int> path;



void input(){
  cin >> n >> m;

  for (int i=0, x, y;i<m;++i)
    cin >> x >> y,
    adj[x].push_back(y),
    adj[y].push_back(x);
}

void travel(int u){

  if(ok) return void();


  //cout << u << " " << parent[u] << endl;

  ++cnt;
  if(cnt == n){

    ok = 1;

    while(parent[u] != 0)
        path.push_back(u),
        u = parent[u];

    path.push_back(u);
    return;
  }


  for(auto &v : adj[u])
      if(!visited[v])
        visited[v] = 1,
        parent[v] = u,
        travel(v),
        visited[v] = 0;


  --cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    input();

    int root = 1;

    for(int i=1;i<=n;++i){
      if(adj[i].size()==1) root=i;
    }
    

    visited[root] = 1;



    travel(root);

    if(path.size() == 0)
      return cout << -1 << endl, 0;


    for(int i=0;i<path.size();++i)
      cout << path[i] << " \n"[i == (int)path.size()-1];








    return 0;

}
