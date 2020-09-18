#include <bits/stdc++.h>
#include "testlib.h"
#include "solver.h"
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 0);

    n = atoi(argv[1]);
    k = atoi(argv[2]);
    q = atoi(argv[3]);
    if(argc==5) {
        subtask = atoi(argv[4]);
    }
    printf("%d %d %d\n", n, k, q);
    for(int i=0; i<n; i++) {
        per[i] = -1;
    }

    int x = rnd.next(n);
    for(int i=0; i<n; i++) {
        while(rnd.next(100)==0 || per[x]!=-1) {
            x = (x+n/2+rnd.next(3)+1)%n;
        }
        per[x] = i;
    }
    gen();
}
