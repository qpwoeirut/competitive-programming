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

// a0 b1 a1
// b0 xx b2
// a3 b3 a2
bool triple(int r, int c) {
    bool a0 = r < 1 || c < 1 || G[r - 1][c - 1] != '.';
    bool a1 = r < 1 || N <= c + 1 || G[r - 1][c + 1] != '.';
    bool a2 = N <= r + 1 || c < 1 || G[r + 1][c - 1] != '.';
    bool a3 = N <= r + 1 || N <= c + 1 || G[r + 1][c + 1] != '.';

    bool b0 = c < 1 || G[r][c - 1] != '.';
    bool b1 = r < 1 || G[r - 1][c] != '.';
    bool b2 = N <= c + 1 || G[r][c + 1] != '.';
    bool b3 = N <= r + 1 || G[r + 1][c] != '.';

    return (b0 && a0 && b1) || (b1 && a1 && b2) || (b2 && a2 && b3) || (b3 && a3 && b0);
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

int reachable() {
    bitset<MN * MN> vis;
    for (int i=0; i<N*N; ++i) vis[i] = G[i / N][i % N] != '.';
    vis[N/2] = true;

    q[0] = N/2;
    int i_q = G[0][N/2] == '.';
    int ct = 0;
    while (i_q > 0) {
        ++ct;
        const int cur = q[--i_q];

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
    return ct;
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

    int i_s = 0;
    int cur_reach = reachable();
    for (int i=0; i<10'000; ++i) {
        const int r = rng() % N, c = rng() % N;
        if (G[r][c] == '.' && !triple(r, c)) {
            G[r][c] = 'A';
            int new_reach = reachable();
            if (new_reach + 1 >= cur_reach && check()) {
                cur_reach = new_reach;
                sol[i_s++] = pii(r, c);
            } else {
                G[r][c] = '.';
            }
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

        cout << i_s;
        while (i_s && i_s --> 0) {
            cout << ' ' << sol[i_s].fi << ' ' << sol[i_s].se;
        }
        cout << endl;
        cout.flush();
    }
}
