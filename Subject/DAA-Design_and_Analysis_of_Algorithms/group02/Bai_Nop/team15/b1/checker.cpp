#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    inf.readEoln();


    for (int i=0;i<n;++i){
        inf.readInt();
        if(i < n-1) inf.readSpace();
    }




    
    
    // for (int i=0;i<q;i++){
    //     int l = inf.readInt();
    //     int r = inf.readInt();
    //     // int correct = *max_element(a.begin()+l-1, a.begin()+r);
    //     int correct = ans.readInt();
    //     int contestant = ouf.readInt();
    //     if (contestant != correct)
    //         quitf(_wa, "Query %d: expected %d, found %d", i+1, correct, contestant);
    // }

    long long correct = ans.readLong();
    long long contestant = ouf.readLong();
    if (contestant != correct)
        quitf(_wa, "Expected %d, found %d", correct, contestant);



    quitf(_ok, "Correct");
}
