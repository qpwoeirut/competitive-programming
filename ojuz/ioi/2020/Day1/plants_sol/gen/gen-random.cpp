#include <bits/stdc++.h>
#include "testlib.h"
#include "solver.h"

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
        per[i]=i;
    }
    shuffle(per, per+n);
    gen();
}
