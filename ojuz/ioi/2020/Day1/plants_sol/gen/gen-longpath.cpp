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
    int x = rnd.next(n/3);
    int y = rnd.next(n/3)*3;
    for(int i=0; i<n/3-1; i++) {
        while(per[y]!=-1) {
            y = (y+rnd.next(k/4))%n;
            while(y%3!=1) y=(y+1)%n;
        }
        per[y] = i;
        while(per[x]!=-1) {
            x = (x+rnd.next(k/4))%n;
            while(x%3!=0) x=(x+1)%n;
        }
        per[x] = n-1-i;
    }

    for(int i=n/3-1; i<n-n/3+1; i++) {
        while(per[x]!=-1) {
            x = (x+rnd.next(k)+k+1)%n;
        }
        per[x] = i;
    }
    for(int i=0; i<n; i++) {
        assert(per[i]!=-1);
        per[i] = n-1-per[i];
    }
    for(int i=0; 2*i+1<n; i++) {
        if(rnd.next(2)) {
            swap(per[2*i], per[2*i+1]);
        }
    }
    gen();
}
