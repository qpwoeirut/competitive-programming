#include <bits/stdc++.h>
#include "testlib.h"
#include "solver.h"
using namespace std;

int interval_length;

int main(int argc, char **argv) {
    registerGen(argc, argv, 0);
    n = atoi(argv[1]);
    k = atoi(argv[2]);
    q = atoi(argv[3]);
    interval_length = atoi(argv[4]);

    if(argc==6) {
        subtask = atoi(argv[5]);
    }
    printf("%d %d %d\n", n, k, q);
    for(int i=0; i<n; i++) {
        per[i] = -1;
    }
    int a = n/2;
    int b = n/2-1;
    bool c = true;
    vector<int> change;
    for(int i=0; i<n; i++) {
        if(i%interval_length==0) {
            c=(!c);
            change.push_back(i);
        }
        if(c) {
            per[i] = a;
            a = (a+1)%n;
        } else {
            per[i] = b;
            b = (b+n-1)%n;
        }
    }
    change.push_back(n);
    for(int i=1; i<(int)change.size(); i++) {
        shuffle(per+change[i-1],per+change[i]);
    }
    gen();
}
