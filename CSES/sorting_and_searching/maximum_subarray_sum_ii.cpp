//maximum_subarray_sum_ii.cpp created at 12/16/20 21:58:26

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;
const int LG = 20;

int N, L1, L2;
ll A[MN];

ll psum[MN];
ll sparse[LG][MN];
int lg2[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> L1 >> L2;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        psum[i+1] = A[i] + psum[i];
    }

    for (int i=0; i<N; ++i) {
        sparse[0][i] = psum[i];
    }

    for (int i=1; i<LG; ++i) {
        for (int j=0; j + (1 << i) <= N; ++j) {
            sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j + (1 << (i - 1))]);
        }
    }

    lg2[1] = 0;
    for (int i=2; i<=N; ++i) {
        lg2[i] = lg2[i >> 1] + 1;
    }

    ll ans = -1e18;
    for (int i=L1; i<=N; ++i) {
        int L = max(0, i - L2);
        int R = max(0, i - L1);

        int lg = lg2[R - L + 1];
        ans = max(ans, psum[i] - min(sparse[lg][L], sparse[lg][R - (1 << lg) + 1]));
    }

    cout << ans << endl;
}

