#include "testlib.h"
using namespace std;

const int MAXN = 13;

int n;
bool g[ MAXN + 5 ][ MAXN + 5 ];
int deg[ MAXN + 5 ];

bool Check(vector<int> &a) {
    for (int i = 1; i < (int)a.size(); i++) {
        if (!g[a[i-1]][a[i]]) return false;
    }
    for(int i = 1; i <= n; i++) {
        if (deg[i] != 1) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> edges(m+10);
    for (int i=0;i<m;i++) {
        edges[i].first = inf.readInt();
        edges[i].second = inf.readInt();
        g[edges[i].first][edges[i].second] = g[edges[i].second][edges[i].first] = true;
    }
    vector<int>path;
    int contestant = ouf.readInt();
    int correct = ans.readInt();
    cout << contestant << " " << correct << "\n";
    if(correct == -1)
    {
        if (contestant != -1) {
            quitf(_wa, "Answer: expected -1, found %d", contestant);
        } else {
            quitf(_ok, "Answer correct");
        }
    }
    else
    {
        if (contestant == -1) {
            quitf(_wa, "Answer: expected -1, found %d", contestant);
        }
        else{
            path.push_back(contestant);
            deg[contestant]++;
            while(path.size()!=n)
            {
                int v = ouf.readInt();
                path.push_back(v);
                deg[v]++;
            }
            if (!ouf.seekEof()) quitf(_wa, "Extra data after %d numbers", n);

            if(!Check(path))
            {
                quitf(_wa, "Path is not Hamiltonian");
            }
            else{
                quitf(_ok, "Answer correct");
            }
        }
    }
}
