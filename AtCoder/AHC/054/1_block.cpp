#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;
#define fi first
#define se second

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

const int chr[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int chc[8] = {0, 1, 0, -1, 1, -1, 1, -1};

const int MN = 40;

int N;
int t_r, t_c;

char G[MN][MN];

// https://stackoverflow.com/a/1640399
static unsigned long x=123456789, y=362436069, z=521288629;
unsigned long rng() {
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    unsigned long t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

int target_dist(int r, int c) {
    return max((r - t_r) * (r - t_r) + (c - t_c) * (c - t_c), 1);
}

int q[MN * MN];
bool check() {
    bitset<MN * MN> vis;
    for (int i=0; i<N*N; ++i) vis[i] = G[i / N][i % N] != '.';
    vis[N/2] = true;

    q[0] = N/2;
    int i_q = G[0][N/2] == '.';
    while (i_q > 0) {
        const int cur = q[--i_q];
        if (cur == t_r * N + t_c) {
            return true;
        }

        if (N <= cur && !vis[cur - N]) {
            vis[cur - N] = true;
            q[i_q++] = cur - N;
        }
        if (0 < cur % N && !vis[cur - 1]) {
            vis[cur - 1] = true;
            q[i_q++] = cur - 1;
        }
        if (cur % N < N - 1 && !vis[cur + 1]) {
            vis[cur + 1] = true;
            q[i_q++] = cur + 1;
        }
        if (cur < N * (N - 1) && !vis[cur + N]) {
            vis[cur + N] = true;
            q[i_q++] = cur + N;
        }
    }
    return false;
}

bitset<MN * MN> seen;
bool valid_block(int p_r, int p_c, int r_u, int r_d, int c_l, int c_r) {
    bool result = true;
    char old_u = 0, old_d = 0, old_l = 0, old_r = 0;
    if (0 <= r_u) {
        old_u = G[r_u][p_c];
        G[r_u][p_c] = 'A';
        result &= !seen[r_u * N + p_c] || old_u != '.';
    }
    if (r_d < N) {
        old_d = G[r_d][p_c];
        G[r_d][p_c] = 'A';
        result &= !seen[r_d * N + p_c] || old_d != '.';
    }
    if (0 <= c_l) {
        old_l = G[p_r][c_l];
        G[p_r][c_l] = 'A';
        result &= !seen[p_r * N + c_l] || old_l != '.';
    }
    if (c_r < N) {
        old_r = G[p_r][c_r];
        G[p_r][c_r] = 'A';
        result &= !seen[p_r * N + c_r] || old_r != '.';
    }

    result = result && check();

    if (old_u) G[r_u][p_c] = old_u;
    if (old_d) G[r_d][p_c] = old_d;
    if (old_l) G[p_r][c_l] = old_l;
    if (old_r) G[p_r][c_r] = old_r;

    return result;
}

pii sol[MN * MN];
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> t_r >> t_c;
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            cin >> G[r][c];
        }
    }

    while (true) {
        int p_r, p_c;
        cin >> p_r >> p_c;
        if (p_r == t_r && p_c == t_c) break;

        int n;
        cin >> n;

        for (int i=0; i<n; ++i) {
            int revealed_r, revealed_c;
            cin >> revealed_r >> revealed_c;
            seen[revealed_r * N + revealed_c] = true;
        }

        int i_s = 0;
        for (int d=0; d<8; ++d) {
            int r = p_r + chr[d];
            int c = p_c + chc[d];
            if (0 <= r && r < N && 0 <= c && c < N && abs(r - t_r) + abs(c - t_c) <= N/5 && G[r][c] == '.') {
                G[r][c] = 'A';
                if (check()) {
                    sol[i_s++] = pii(r, c);
                } else {
                    G[r][c] = '.';
                }
            }
        }

        debug2(G, N, N);
        double best_sc = N*N;
        int b_u, b_d, b_l, b_r;
        for (int total = 4; total <= 2*N && best_sc == N*N; ++total) {
            double sc_u = 0;
            for (int u=1; u<N; ++u) {
                const int r_u = p_r - u;
                if (0 <= r_u && !seen[r_u * N + p_c]) sc_u += 1 + 0.1 / target_dist(r_u, p_c);

                double sc_d = 0;
                for (int d=1; d<N; ++d) {
                    const int r_d = p_r + d;
                    if (r_d < N && !seen[r_d * N + p_c]) sc_d += 1 + 0.1 / target_dist(r_d, p_c);

                    double sc_l = 0;
                    for (int l=1; l<N; ++l) {
                        const int c_l = p_c - l;
                        if (0 <= c_l && !seen[p_r * N + c_l]) sc_l += 1 + 0.1 / target_dist(p_r, c_l);

                        const int r = total - u - d - l;
                        const int c_r = p_c + r;
                        double sc_r = 0;
                        for (int i_r=1; i_r<=r; ++i_r) {
                            const int ci_r = p_c + i_r;
                            if (ci_r < N && !seen[p_r * N + ci_r]) sc_r += 1 + 0.1 / target_dist(p_r, ci_r);
                        }
                        if (r > 0 && valid_block(p_r, p_c, r_u, r_d, c_l, c_r)) {
                            debug(u, d, l, r);
                            debug(sc_u, sc_d, sc_l, sc_r);
                        }
                        if (r > 0 && best_sc > sc_u + sc_d + sc_l + sc_r && valid_block(p_r, p_c, r_u, r_d, c_l, c_r)) {
                            best_sc = sc_u + sc_d + sc_l + sc_r;
                            b_u = p_r - u;
                            b_d = p_r + d;
                            b_l = p_c - l;
                            b_r = p_c + r;
                        }
                    }
                }
            }
        }

        if (0 <= b_u && G[b_u][p_c] == '.') G[b_u][p_c] = 'A', sol[i_s++] = pii(b_u, p_c);
        if (b_d < N  && G[b_d][p_c] == '.') G[b_d][p_c] = 'A', sol[i_s++] = pii(b_d, p_c);
        if (0 <= b_l && G[p_r][b_l] == '.') G[p_r][b_l] = 'A', sol[i_s++] = pii(p_r, b_l);
        if (b_r < N  && G[p_r][b_r] == '.') G[p_r][b_r] = 'A', sol[i_s++] = pii(p_r, b_r);

        cout << i_s;
        while (i_s --> 0) {
            cout << ' ' << sol[i_s].fi << ' ' << sol[i_s].se;
        }
        cout << endl;
        cout.flush();
    }
}
