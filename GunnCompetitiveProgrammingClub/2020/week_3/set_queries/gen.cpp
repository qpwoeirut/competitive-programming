#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef pair<int,int> pii;

const int MX = 1e9;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = atoi(argv[1]);
    int Q = atoi(argv[2]);
    vector<int> A(N);
    vector<pii> q(Q);
    for (int i=0; i<N; ++i) {
        A[i] = rnd.next(-MX, MX);
    }
    for (int i=0; i<Q; ++i) {
        q[i].first = rnd.next(1, 4);
        q[i].second = rnd.next(-MX, MX);
    }
    
    cout << N << ' ' << Q << endl;
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << endl;
    for (int i=0; i<Q; ++i) {
        cout << q[i].first;
        if (q[i].first != 3) {
            cout << ' ' << q[i].second;
        }
        cout << endl;
    }
}

