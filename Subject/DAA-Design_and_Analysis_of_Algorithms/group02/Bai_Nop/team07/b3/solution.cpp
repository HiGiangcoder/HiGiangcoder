#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define double long double
#define endl "\n"
#define NAME "a"
 
const int MAXN = 12;
const int inf = 1e18;
const int MOD = 1e9 + 7;
 
// void FileInput(){
//     if(fopen(NAME".inp" , "r") == NULL)
//         freopen(NAME".inp" , "w" , stdout);
//     freopen(NAME".inp" , "r" , stdin);
//     freopen(NAME".out" , "w" , stdout);
// }
 
int n , m;
vector<int> g[MAXN + 36];
bool dp[MAXN + 3][(1 << MAXN) + 36];
 
bool isOn(int mask , int x){
    return (mask >> (x - 1)) & 1;
}
 
void solve(){
    cin >> n >> m;
    for(int i = 1 ; i <= m ; i++){
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    for(int i = 1 ; i <= n ; i++)
        dp[i][1 << (i - 1)] = true;
 
    for(int mask = 0 ; mask < (1 << n) ; mask++){
        for(int curMask = mask ; curMask > 0 ; curMask -= (curMask & (-curMask))){
            int u = __builtin_ctz(curMask) + 1;
            if(dp[u][mask] == false) continue;
 
            for(auto v : g[u]){
                if(isOn(mask , v)) continue;
                dp[v][mask ^ (1 << (v - 1))] |= dp[u][mask];
            }
        }
    }
    int curMask = (1 << n) - 1 , u = -1;
 
    for(int i = 1 ; i <= n ; i++)
        if(dp[i][curMask] == true){
            u = i;
            break;
        }
 
    if(u == -1){
        cout << u << endl;
        return;
    }
 
    vector<int> path;
    path.push_back(u);
    int cnt = 0;
    while(__builtin_popcount(curMask) > 1 && cnt < 100){
        cnt++;
        for(auto v : g[u]){
            if(isOn(curMask , v) && dp[v][curMask ^ (1 << (u - 1))]){
                path.push_back(v);
                curMask ^= (1 << (u - 1));
                u = v;
            }
        }
    }
 
    reverse(path.begin() , path.end());
 
    for(auto x : path)
        cout << x << " ";
    cout << endl;
}
 
int32_t main(){
    // FileInput();
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}