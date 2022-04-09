#include <bits/stdc++.h>

using namespace std;

using dbl=long double;

const int N = 3;

// CLRS algo book go brrr
// Ax = B, where A is matrix and x, B are vectors

int A[N][N], B[N];
dbl x[N];

dbl L[N][N], U[N][N];
int P[N];

// CLRS page 821
// solves for x given L, U, P
void LUP_solve() {  // uses x as y
    for (int i=0; i<N; ++i) {
        x[i] = B[P[i]];
        for (int j=0; j<i; ++j) {
            x[i] -= L[i][j] * x[j];
        }
    }
    for (int i=N-1; i>=0; --i) {
        for (int j=i+1; j<N; ++j) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

dbl tmp[N][N];
// CLRS page 824
void LUP_decomp() {
    for (int i=0; i<N; ++i) {
        P[i] = i;
        for (int j=0; j<N; ++j) {
            tmp[i][j] = A[i][j];
        }
    }
    for (int k=0; k<N; ++k) {
        dbl p = 0;
        int k_swap = k;
        for (int i=k; i<N; ++i) {
            if (p < abs(tmp[i][k])) {
                p = abs(tmp[i][k]);
                k_swap = i;
            }
        }
        assert(p > 0);
        swap(P[k], P[k_swap]);
        swap(tmp[k], tmp[k_swap]);

        for (int i=k+1; i<N; ++i) {
            tmp[i][k] /= tmp[k][k];
            for (int j=k+1; j<N; ++j) {
                tmp[i][j] -= tmp[i][k] * tmp[k][j];
            }
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            L[i][j] = i > j ? tmp[i][j] : 0;
            U[i][j] = i <= j ? tmp[i][j] : 0;
        }
    }
}

dbl check[N];
int main() {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> A[i][j];
        }
        cin >> B[i];
    }

    LUP_decomp();
    LUP_solve();

    for (int i=0; i<N; ++i) {
        check[i] = 0;
        for (int j=0; j<N; ++j) {
            check[i] += A[i][j] * x[j];
        }
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << x[i];
    } cout << endl;

    for (int i=0; i<N; ++i) {
        cout << check[i] << ' ' << B[i] << endl;
    }
}
/*
3 4 2 9
5 4 9 18
1 2 -1 2
*/
