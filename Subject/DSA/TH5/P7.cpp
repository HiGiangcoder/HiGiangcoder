
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;


vector<int> get_ans(const vector<int>& A,int K){
	map<int,int> Hash;
	vector<int> ans;
    for (int i = 0; i < A.size(); i++){
        Hash[A[i]]++;
    }

    for (int rep = 1; rep <= n; rep++){
        vector<int> list_erase;

        for (pair<const int,int> &p: Hash){
            p.second --;
            if (p.second == 0){
                list_erase.push_back(p.first);
            }

            if (K > 0) {
                ans.push_back(p.first);
                K--;
            }
            else {
                break;
            }
        }
        for (int i = 0; i < list_erase.size(); i++){
            Hash.erase(list_erase[i]);
        }
    }
    return ans;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	cin >> n >> k;
	
	a.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	
	vector<int> ans = get_ans(a,k);
	
	for (const int& x: ans) cout << x << ' ';
	return 0;
}
