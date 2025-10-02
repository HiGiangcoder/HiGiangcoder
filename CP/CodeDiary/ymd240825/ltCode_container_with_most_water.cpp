/* sort template*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int ans(0);
        int n = height.size();

        vector<pair<int, int>> hsort;
        for (int i = 0; i < n; i ++) {
            hsort.push_back({height[i], i});
        }
        sort(hsort.begin(), hsort.end(), greater<pair<int, int>>());

        int leftContainer = n - 1; 
        int rightContainer = 0; 

        for (const pair<int, int> &vertical : hsort) {
            leftContainer = min(leftContainer, vertical.second);
            rightContainer = max(rightContainer, vertical.second);

            ans = max(ans, (rightContainer - leftContainer) * vertical.first);
        }

        return ans; 
    }
} sol;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    vector<int> v = {1,8,6,2,5,4,8,3,7};
    cout << sol.maxArea(v);

    return 0;
}

