#include <bits/stdc++.h>
#include "testlib.h"
#include "solver.h"
#define low(i) (i<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)
#define high(i) ((i+1)<<(__builtin_clz(i)-31+n_bits))-(1<<n_bits)-1
using namespace std;

int main(int argc, char **argv) {
    registerGen(argc, argv, 0);

    n = atoi(argv[1]);
    k = atoi(argv[2]);
    q = atoi(argv[3]);
    int path_length = atoi(argv[4]); // this is an "average" path length
    printf("%d %d %d\n", n, k, q);
    assert(k==2);
    vector<int> r(n);
    r[0] = 0;
    r[1] = 1; // prevent all 0 or all n
    for(int i=2; i<n; i++) {
        r[i] = (rnd.next(path_length) ? r[i-1] : 1-r[i-1]);
    }
    for(int i=0; i<n; i++) {
        if(i) printf(" ");
        printf("%d",r[i]);
    }
    printf("\n");
    plant pl;
    pl.init(r);
    // ensure an equal amount of 0 and non-0 output
    for(int i=0; i<q; i++) {
        int x,y;
        bool isZero = (bool)rnd.next(2);
        do {
            x = rnd.next(n);
            y = (x + rnd.next(3*path_length))%n;
            if(x>y) swap(x,y);
        } while(x==y || pl.comparable(x,y)==isZero);
        printf("%d %d\n", x, y);
    }
}
