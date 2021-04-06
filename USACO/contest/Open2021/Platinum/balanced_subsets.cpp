#include <bits/stdc++.h>

using namespace std;

#define x real()
#define y imag()

typedef long long ll;
typedef complex<int> pt;

const int MN = 152;
const ll MOD = 1e9 + 7;

int N, M;
pt A[MN * MN];
bool G[MN * 3][MN * 3];

pt cur[MN * MN];

inline bool cmpx(const pt& a, const pt& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
inline bool cmpy(const pt& a, const pt& b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

int k;
const int chx[4] = {1, 0, -1, 0};
const int chy[4] = {0, 1, 0, -1};
bool vis[MN * MN];
int dfs(const int idx) {
    if (vis[idx]) return 0;

    int ret = 1;
    vis[idx] = true;
    for (int i=0; i<4; ++i) {
        const pt nxt(cur[idx].x + chx[i], cur[idx].y + chy[i]);
        const int nxt_idx = lower_bound(cur, cur+k, nxt, cmpx) - cur;
        if (nxt_idx == k || cur[nxt_idx] != nxt) continue;

        ret += dfs(nxt_idx);
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=N; i<N+N; ++i) {
        for (int j=N; j<N+N; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == 'G';
            if (G[i][j]) A[M++] = pt(i, j);
        }
    }

    int ans = 0;
    for (int i=1; i<(1 << M); ++i) {
        k = 0;
        for (int j=0; j<M; ++j) {
            if ((i >> j) & 1) {
                cur[k++] = A[j];
            }
        }


        sort(cur, cur+k, cmpx);
        fill(vis, vis+k, false);

        bool ok = dfs(0) == k;
        if (!ok) continue;

        for (int j=0; j+1<k; ++j) {
            if (cur[j].x == cur[j+1].x && cur[j].y + 1 != cur[j+1].y) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;

        sort(cur, cur+k, cmpy);
        for (int j=0; j+1<k; ++j) {
            if (cur[j].y == cur[j+1].y && cur[j].x + 1 != cur[j+1].x) {
                ok = false;
                break;
            }
        }
        if (!ok) continue;

        if (++ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';
}
