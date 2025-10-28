#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    inf.readSpace();
    int m = inf.readInt();
    inf.readEoln();

    bool edge[n+1][n+1];
    memset(edge, 0, sizeof(edge));

    while(m--){
        int x = inf.readInt();
        inf.readSpace();
        int y = inf.readInt();
        inf.readEoln();
        edge[x][y] = edge[y][x] = 1;
    }

    vector<int> contestant(n);

    int x = ouf.readInt();
    if(x == -1){
        int y = ans.readInt();
        if(x == y) 
            quitf(_ok, "Correct!!");
        else 
            quitf(_wa, "Have hamilton path!!!");
        return 0;
    }

    contestant[0] = x;

    if(n > 1) 
        ouf.readSpace();
    
    for(int i=1;i<n;++i){
        contestant[i] = ouf.readInt();
        if(i < n-1) 
            ouf.readSpace();
    }


    for(int i=0;i+1<n;++i)
        if(!edge[contestant[i]][contestant[i+1]]){
            quitf(_wa, "Is not hamilton path!!");
            break;
        }
    


    
    
    quitf(_ok, "Correct!!");
}
