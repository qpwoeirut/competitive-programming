#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int flag = atoi(argv[1]);
    int N = atoi(argv[2]);
    vector<int> A(N);
    if (flag == 2) {
        int m = atoi(argv[3]);
        int upper = atoi(argv[4]);
        for (int i=0; i<N; ++i) {
            A[i] = i*m + rnd.next(1, upper);
        }
    }
    else if (flag == 1) {
        for (int i=0; i<N; ++i) {
            A[i] = rnd.next(1, (int)1e9);
        }
    } else {
        for (int i=0; i<N; ++i) {
            A[i] = atoi(argv[i+3]);
        }
    }
    
    cout << N << endl;
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << endl;
}
