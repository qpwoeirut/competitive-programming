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
const char EMPTY = '.';
const char GUARD = 'G';
const char MAZE = 'M';

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
    bool a0 = r < 1 || c < 1 || G[r - 1][c - 1] != EMPTY;
    bool a1 = r < 1 || N <= c + 1 || G[r - 1][c + 1] != EMPTY;
    bool a2 = N <= r + 1 || c < 1 || G[r + 1][c - 1] != EMPTY;
    bool a3 = N <= r + 1 || N <= c + 1 || G[r + 1][c + 1] != EMPTY;

    bool b0 = c < 1 || G[r][c - 1] != EMPTY;
    bool b1 = r < 1 || G[r - 1][c] != EMPTY;
    bool b2 = N <= c + 1 || G[r][c + 1] != EMPTY;
    bool b3 = N <= r + 1 || G[r + 1][c] != EMPTY;

    return (b0 && a0 && b1) || (b1 && a1 && b2) || (b2 && a2 && b3) || (b3 && a3 && b0);
}

bool near_guard(int r, int c) {
    for (int d=0; d<8; ++d) {
        int nr = r + chr[d];
        int nc = c + chc[d];
        if (0 <= nr && nr < N && 0 <= nc && nc < N && G[nr][nc] == GUARD) return true;
    }
    return false;
}

int st[MN * MN];
bool check() {
    bitset<MN * MN> vis;
    for (int i=0; i<N*N; ++i) vis[i] = G[i / N][i % N] != EMPTY;
    vis[N/2] = true;

    st[0] = N/2;
    int i_st = G[0][N/2] == EMPTY;
    while (i_st > 0) {
        const int cur = st[--i_st];
        if (cur == t_r * N + t_c) {
            return true;
        }

        if (N <= cur && !vis[cur - N]) {
            vis[cur - N] = true;
            st[i_st++] = cur - N;
        }
        if (0 < cur % N && !vis[cur - 1]) {
            vis[cur - 1] = true;
            st[i_st++] = cur - 1;
        }
        if (cur % N < N - 1 && !vis[cur + 1]) {
            vis[cur + 1] = true;
            st[i_st++] = cur + 1;
        }
        if (cur < N * (N - 1) && !vis[cur + N]) {
            vis[cur + N] = true;
            st[i_st++] = cur + N;
        }
    }
    return false;
}

int reachable() {
    bitset<MN * MN> vis;
    for (int i=0; i<N*N; ++i) vis[i] = G[i / N][i % N] != EMPTY;
    vis[N/2] = true;

    st[0] = N/2;
    int i_st = G[0][N/2] == EMPTY;
    int ct = 0;
    while (i_st > 0) {
        ++ct;
        const int cur = st[--i_st];

        if (N <= cur && !vis[cur - N]) {
            vis[cur - N] = true;
            st[i_st++] = cur - N;
        }
        if (0 < cur % N && !vis[cur - 1]) {
            vis[cur - 1] = true;
            st[i_st++] = cur - 1;
        }
        if (cur % N < N - 1 && !vis[cur + 1]) {
            vis[cur + 1] = true;
            st[i_st++] = cur + 1;
        }
        if (cur < N * (N - 1) && !vis[cur + N]) {
            vis[cur + N] = true;
            st[i_st++] = cur + N;
        }
    }
    return ct;
}

pii path[MN * MN];
int dist[MN][MN];

int recover_path(const pii& src) {
    int i_p = 0;
    int r = src.fi, c = src.se;
    path[i_p++] = src;
    while (dist[r][c] > 0) {
        for (int d=0; d<4; ++d) {
            int nr = r + chr[d];
            int nc = c + chc[d];
            if (0 <= nr && nr < N && 0 <= nc && nc < N && dist[nr][nc] == dist[r][c] - 1) {
                r = nr;
                c = nc;
                path[i_p++] = pii(r, c);
            }
        }
    }
    return i_p;
}

pii q[MN * MN];
int shortest_path(const set<pii>& banned, pii& src) {
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            dist[r][c] = N*N;
        }
    }
    int i_q = 0, n_q = 0;
    q[n_q++] = pii(t_r, t_c);
    dist[t_r][t_c] = 0;
    while (i_q < n_q) {
        const pii cur = q[i_q++];
        if (banned.count(cur) == 0 && (cur.se == 0 || cur.se == N - 1) && ((0 < cur.fi && G[cur.fi - 1][cur.se] == EMPTY) || (cur.fi + 1 < N && G[cur.fi + 1][cur.se] == EMPTY))) {
            src = cur;
            return recover_path(cur);
        }

        for (int d=0; d<4; ++d) {
            int nr = cur.fi + chr[d];
            int nc = cur.se + chc[d];
            if (nr == t_r && abs(nc - t_c) == 2) continue;
            if (0 <= nr && nr < N && 0 <= nc && nc < N && dist[nr][nc] > dist[cur.fi][cur.se] + 1 && G[nr][nc] == EMPTY) {
                dist[nr][nc] = dist[cur.fi][cur.se] + 1;
                q[n_q++] = pii(nr, nc);
            }
        }
    }
    return 0;
}

set<pii> hide_flower() {
    set<pii> blocks, banned;
    for (int i=0; i<100; ++i) {
        pii src(-1, -1);
        const int n_p = shortest_path(banned, src);
        for (int i=0; i<n_p; ++i) {
            for (int d=0; d<4; ++d) {
                int nr = path[i].fi + chr[d];
                int nc = path[i].se + chc[d];
                if (abs(nr - src.fi) == 1 && nc == src.se) continue;
                if (0 <= nr && nr < N && 0 <= nc && nc < N && G[nr][nc] == EMPTY) {
                    blocks.emplace(nr, nc);
                }
            }
        }
        for (int i=0; i<n_p; ++i) {
            blocks.erase(path[i]);
        }
        for (const pii& p: blocks) G[p.fi][p.se] = GUARD;

        if (check()) return blocks;

        for (const pii& p: blocks) G[p.fi][p.se] = EMPTY;
        blocks.clear();
        banned.insert(src);
    }
    return set<pii>();
}

set<pii> create_maze() {
    set<pii> maze;
    int cur_reach = reachable();
    for (int i=0; i<10'000; ++i) {
        const int r = rng() % N, c = rng() % N;
        if (G[r][c] == EMPTY && !triple(r, c) && !near_guard(r, c)) {
            G[r][c] = MAZE;
            int new_reach = reachable();
            if (new_reach + 1 >= cur_reach && check()) {
                cur_reach = new_reach;
                maze.emplace(r, c);
            } else {
                G[r][c] = EMPTY;
            }
        }
    }
    return maze;
}

bitset<MN * MN> seen;
pii sol[MN * MN];
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> t_r >> t_c;
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            cin >> G[r][c];
        }
    }

    const set<pii> blocks = hide_flower();
    int i_s = copy(blocks.begin(), blocks.end(), sol) - sol;
    
    const set<pii> maze = create_maze();
    i_s = copy(maze.begin(), maze.end(), sol + i_s) - sol;

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
