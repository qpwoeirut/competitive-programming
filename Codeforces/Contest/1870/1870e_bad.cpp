//1870e.cpp created at 09/18/23 08:45:27

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

const int MN = 5000;

int A[MN];
int mex[MN][MN];
bitset<MN+1> reach[MN+1];

void solve() {
    int N;
    cin >> N;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    bitset<MN+1> op;
    for (int i=0; i<N; ++i) {
        int m = 0;
        for (int j=i; j<N; ++j) {
            op[A[j]] = true;
            for (; op[m]; ++m);
            mex[i][j] = m;
        }
        op.reset();
    }

    reach[0].reset();
    reach[0][0] = true;
    for (int i=0; i<N; ++i) {
        reach[i+1] = reach[i];

        op.set(mex[i][i]);
        reach[i+1] |= reach[i] ^ op;
        op.reset(mex[i][i]);
        debug(i, mex[i][i]);

        for (int j=i-1; j>=0; --j) {
            if (mex[j][i] != mex[j+1][i]) {
                op.set(mex[j][i]);
                reach[i+1] |= reach[j] ^ op;
                op.reset(mex[j][i]);
                debug(i, j, mex[j][i]);
            }
        }
        debug(reach[i].to_string().substr(MN - 20, MN));
    }
    debug(reach[N].to_string().substr(MN - 20, MN));

    for (int i=N; i>=0; --i) {
        if (reach[N][i]) {
            cout << i << '\n';
            return;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}

