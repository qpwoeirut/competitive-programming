#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int div = atoi(argv[1]);

    int LO = -1e9;
    int HI = 1e9;
    for (int i=0; i<div; i++) {
        LO /= 10;
        HI /= 10;
    }

    int A = rnd.next(LO, HI); 
    int B = rnd.next(LO, HI); 
    cout << A << ' ' << B << endl;
}
