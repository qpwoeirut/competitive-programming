#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
const int n_max = 200000;;

// this one generates cases where k = n
int main(int argc, char **argv) {
    registerGen(argc, argv, 0);

    int n = atoi(argv[1]);
    int q = atoi(argv[2]);

    printf("%d %d %d\n", n, n, q);
    int r[n];
    for(int i=0; i<n; i++) {
        r[i] = i;
    }
    shuffle(r, r+n);
    for(int i=0; i<n; i++) {
        if(i) printf(" ");
        printf("%d", r[i]);
    }
    printf("\n");

    for(int i=0; i<q; i++) {
        int x,y;
        do {
            x = rnd.next(n);
            y = rnd.next(n);
        } while(x==y);
        if(x>y) swap(x,y);
        printf("%d %d\n", x, y);
    }
}
