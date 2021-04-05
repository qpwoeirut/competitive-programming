#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

const int MN = 1e6;
const ll MIN_VAL = -1e18;
const ll MAX_VAL = 1e18;

int N;
ll A[MN];

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int array_type = atoi(argv[1]);
    N = atoi(argv[2]);

    for (int i=0; i<N; ++i) {
        A[i] = rnd.next(MIN_VAL, MAX_VAL);
    }
    if (array_type == 0) {
        fill(A, A+N, rnd.next(MIN_VAL, MAX_VAL));
    } else if (array_type == 1) {
        // do nothing
    } else if (array_type == 2) {
        sort(A, A+N);
    } else if (array_type == 3) {
        sort(A, A+N, greater<ll>());
    } else assert(false);

    cout << N << '\n';
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << '\n';
}

