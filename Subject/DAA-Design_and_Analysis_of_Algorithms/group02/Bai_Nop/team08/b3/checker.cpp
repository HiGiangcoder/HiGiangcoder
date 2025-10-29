#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = inf.readInt();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }


    int jury_first_token = ans.readInt();

    int participant_first_token = ouf.readInt();

    if (participant_first_token == -1) {
        if (jury_first_token == -1) {
            quitf(_ok, "Correctly answered -1");
        } else {
            quitf(_wa, "Contestant answered -1, but a solution exists");
        }
    }

    vector<int> path;
    path.push_back(participant_first_token);
    for (int i = 1; i < n; ++i) {
        path.push_back(ouf.readInt());
    }
    if (!ouf.eof()) {
        quitf(_pe, "Participant printed extra data after the path");
    }

    vector<bool> visited(n + 1, false);
    for (int v : path) {
        if (v < 1 || v > n) {
            quitf(_wa, "Path contains vertex %d which is out of range [1, %d]", v, n);
        }
        if (visited[v]) {
            quitf(_wa, "Vertex %d appears more than once in the path", v);
        }
        visited[v] = true;
    }

    for (size_t i = 0; i < path.size() - 1; ++i) {
        int u = path[i];
        int v = path[i+1];
        if (u > v) swap(u, v);

        if (edges.find({u, v}) == edges.end()) {
            quitf(_wa, "Path contains a non-existent edge between %d and %d", path[i], path[i+1]);
        }
    }

    quitf(_ok, "Correct Hamiltonian path");
}
