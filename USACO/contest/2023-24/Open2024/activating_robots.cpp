#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 100005;
const int MR = 19;
const ll INF = 1e18;
const int REPEAT = 5;

ll A[REPEAT * MN];
ll dp[1 << MR][MR];
ll nearest[MN][50];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll L, R, N, K;
    cin >> L >> R >> N >> K;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);
    for (int i=N; i<REPEAT*N; ++i) {
        A[i] = A[i-N] + L;
    }

    const ll D = L / R;
    --R;

    for (int m=0; m<(1<<R); ++m) {
        for (int i=0; i<R; ++i) {
            dp[m][i] = INF;
        }
    }

    for (int i=0; i<N; ++i) {
        for (int r=0; r<R; ++r) {
            ll d_r = A[i] - (r + 1) * D; if (d_r < 0) d_r += L;
            ll d_m = min(A[i], L - A[i]);
            if (d_r * K >= d_m) {
                dp[1 << r][r] = min(dp[1 << r][r], d_r * K);
            } else {
                dp[1 << r][r] = min(dp[1 << r][r], d_r * K + L * K);
            }
        }
    }

    for (int i=0; i<N; ++i) {
        for (int d=-MR; d<=MR; ++d) {
            ll dist_cw = (L - d * D) % L; if (dist_cw < 0) dist_cw += L;
            const ll tk_cw = (dist_cw + K) / (K + 1);
            const ll x_cw = (A[i] - dist_cw + L) % L;
            
            const int j_cw = lower_bound(A, A+REPEAT*N, x_cw + tk_cw) - A;
            const ll t_cw = (A[j_cw] - x_cw) * K;
            nearest[i][d + MR] = t_cw;

            if (K > 1) {
                ll dist_ccw = (d * D) % L; if (dist_ccw < 0) dist_ccw += L;
                const ll tk_ccw = (dist_ccw + K - 2) / (K - 1);
                const ll x_ccw = (A[i] - dist_cw + L) % L;  // use dist_cw, not dist_ccw

                const int j_ccw = lower_bound(A, A+REPEAT*N, x_ccw + tk_ccw) - A;
                const ll t_ccw = (A[j_ccw] - x_ccw) * K;
                nearest[i][d + MR] = min(t_cw, t_ccw);

                //cerr << i << ' ' << d << ' ' << nearest[i][d + MR] << endl;
                //cerr << dist_cw << ' ' << x_cw << ' ' << tk_cw << ' ' << t_cw << endl;
                //cerr << dist_ccw << ' ' << x_ccw << ' ' << tk_ccw << ' ' << t_ccw << endl;
                //cerr << endl;
            }
        }
    }

    for (int m=1; m<(1<<R); ++m) {
        for (int r_i=0; r_i<R; ++r_i) {
            if (dp[m][r_i] == INF) continue;
            const ll x = ((r_i + 1) * D + (dp[m][r_i] / K)) % L;
            const int i = lower_bound(A, A+N, x) - A;
            //cerr << i << ' ' << x << ' ' << A[i] << endl;
            assert(i < N && A[i] == x);
            for (int r_j=0; r_j<R; ++r_j) {
                if ((m >> r_j) & 1) continue;
                dp[m | (1 << r_j)][r_j] = min(dp[m | (1 << r_j)][r_j], dp[m][r_i] + nearest[i][r_j - r_i + MR]);
            }

            //cerr << bitset<8>(m).to_string() << ' ' << r_i << ' ' << dp[m][r_i] << endl;
        }
    }

    ll ans = INF;
    for (int r=0; r<R; ++r) {
        ans = min(ans, dp[(1 << R) - 1][r]);
    }

    cout << ans << '\n';
}
