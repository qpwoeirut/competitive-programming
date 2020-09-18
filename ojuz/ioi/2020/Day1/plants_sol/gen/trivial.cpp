#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
const int n_max = 200000;;

int main(int argc, char **argv) {
    registerGen(argc, argv, 0);

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int q = atoi(argv[3]);
    int inverted = atoi(argv[4]);

    printf("%d %d %d\n", n, k, q);
    if(inverted) {
        printf("%d", k-1);
        for(int i=1; i<n; i++) {
            printf(" %d", k-1-max(i-n+k,0));
        }
    } else {
        printf("0");
        for(int i=1; i<n; i++) {
            printf(" %d", max(i-n+k,0));
        }
    }
    printf("\n");

    for(int i=0; i<q; i++) {
        int x,y;
        //bool isZero = (bool)rnd.next(2);
        do {
            x = rnd.next(n);
            y = rnd.next(n);
        } while(x==y);
        if(x>y) swap(x,y);
        printf("%d %d\n", x, y);
    }
}
