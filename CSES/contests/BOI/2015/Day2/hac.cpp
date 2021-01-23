//hac.cpp created at 01/13/21 19:13:42

#include <bits/stdc++.h>

using namespace std;

const int MN = 500005;
const int LG = 21;

int N;
int A[MN];

int op[MN];
int sparse[LG][MN << 1];
int lg2[MN];

int main() {
    cin.tie(0)->sync_with_stdio();

    lg2[1] = 0;
    for (int i=2; i<MN; ++i) {
        lg2[i] = lg2[i >> 1] + 1;
    }
    
    cin >> N;
    const int X = N >> 1;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    int sum = 0;
    int cur = 0;
    for (int i=N-X; i<N; ++i) cur += A[i];
    for (int i=0; i<N; ++i) {
        cur += A[i];
        cur -= A[(N + i - X) % N];

        op[i] = cur;
        sum += A[i];
    }
    for (int i=0; i<N+N; ++i) {
        sparse[0][i] = op[i%N];
    }

    for (int i=1; i<LG; ++i) {
        for (int j=0; j + (1 << i) <= N+N; ++j) {
            sparse[i][j] = max(sparse[i-1][j], sparse[i-1][j + (1 << (i-1))]);
        }
    }

    //cerr << "X=" << X << endl; for (int i=0; i<N; ++i) { cerr << op[i] << ' '; } cerr << endl;

    int ans = 0;
    const int lg = lg2[N - X];
    //for (int i=0; i<=lg; ++i) { for (int j=0; j<N+N; ++j) { cerr << sparse[i][j] << ' '; } cerr << endl; }
    for (int i=0; i<N; ++i) {
        const int L = i + X;
        const int R = i + N;
        const int op_sum = max(sparse[lg][L], sparse[lg][R - (1 << lg)]);
        //cerr << i << ' ' << op_sum << endl;
        ans = max(ans, sum - op_sum);
    }

    cout << ans << endl;
}

/*
4
7 6 8 4

5
1 1 1 1 1
*/

