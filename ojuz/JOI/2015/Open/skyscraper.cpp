#include <bits/stdc++.h>

using namespace std;

const int MN = 14;
const int MX = 101;
const int MOD = 1e9 + 7;

int N, L;
int A[MN];

int dp[1 << MN][MN][MX];

void add(int& a, const int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> L;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    int ans = 0;
    if (N <= 8) {
        sort(A, A+N);

        do {
            int cur = 0;
            for (int i=1; i<N; ++i) {
                cur += abs(A[i] - A[i-1]);
            }
            if (cur <= L) ++ans;
        } while (next_permutation(A, A+N));

        cout << ans << endl;
        return 0;
    }
    for (int i=0; i<N; ++i) {
        dp[1 << i][i][0] = 1;
    }

    for (int i=1; i<(1<<N); ++i) {
        for (int j=0; j<N; ++j) {
            if (((i >> j) & 1) == 0) continue;
            for (int k=0; k<N; ++k) {
                if (i & (1 << k)) continue;
                for (int l=0; l<=L; ++l) {
                    int diff = l - abs(A[j] - A[k]);
                    if (diff < 0) continue;
                    add(dp[i + (1 << k)][k][l], dp[i][j][diff]);
                }
            }
        }
    }

    int mask = (1 << N) - 1;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<=L; ++j) {
            add(ans, dp[mask][i][j]);
        }
    }

    cout << ans << endl;
}
/*
4 10
3 6 2 9

8 35
3 7 1 5 10 2 11 6
*/
