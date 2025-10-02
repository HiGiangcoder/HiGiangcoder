/* sort template*/
#include <bits/stdc++.h>
using namespace std;

#define fi  first
#define se  second
typedef long long ll;
typedef pair<int, int> ii;

template<class T> bool maximize(T &a, const T &b){ return (a < b ? a = b, 1 : 0); }
template<class T> bool minimize(T &a, const T &b){ return (a > b ? a = b, 1 : 0); }

const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAX = 2e5 + 7; 

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    class Val {
    public:
        int val;
        ListNode *ptr;
        Val(int _val, ListNode *_ptr) {
            val = _val;
            ptr = _ptr;
        }
        bool operator > (const Val &other) const {
            return val > other.val;
        }
    };

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *ans = new ListNode();
        ListNode *ptr = ans;

        priority_queue<Val, vector<Val>, greater<Val>> pq;

        for (ListNode *p : lists) if (p != nullptr) {
            pq.push(Val(p->val, p));
        }

        while (pq.size()) {
            ptr->next = new ListNode();
            ptr = ptr->next;

            Val p = pq.top();
            pq.pop();

            ptr->val = p.val;

            if (p.ptr->next != nullptr) pq.push(Val(p.ptr->next->val, p.ptr->next));
        }

        return ans->next;
    }
} sol;

void process() {
    vector<vector<int>> vec = {{1, 4, 5}, {1, 3, 4}, {2, 6}};    
    vector<ListNode*> test;
    for (const vector<int> &v : vec) {
        ListNode* root = new ListNode();
        ListNode* ptr = root;
        for (const int &x : v) {
            ptr->next = new ListNode();
            ptr = ptr->next;

            ptr->val = x;
        }
        test.push_back(root->next);
    }

    ListNode *ans = sol.mergeKLists(test);

    cout << endl;
    while (ans != nullptr) {
        cout << ans->val << ' ';
        ans = ans->next;
    }
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    process();

    return 0;
}

