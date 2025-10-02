#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;
#define fi first
#define se second

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> t_r >> t_c;
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            cin >> G[r][c];
        }
    }

    vector<pii> sol;
    for (int i=0; i<N*N/2; ++i) {
        const int r = rng() % N, c = rng() % N;
        if (G[r][c] == '.') {
            G[r][c] = 'A';
            if (!check()) {
                G[r][c] = '.';
            } else {
                sol.emplace_back(r, c);
            }
        }
    }

    while (true) {
        int p_r, p_c;
        cin >> p_r >> p_c;

        if (p_r == t_r && p_c == t_c) break;
        int n;
        cin >> n;

        int revealed_r, revealed_c;
        for (int i=0; i<n; ++i) {
            cin >> revealed_r >> revealed_c;
        }

        cout << sol.size();
        for (const pii& p: sol) {
            cout << ' ' << p.fi << ' ' << p.se;
        }
        cout << endl;
        cout.flush();

        sol.clear();
    }
}
