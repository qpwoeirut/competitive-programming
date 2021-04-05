#include <bits/stdc++.h>

using namespace std;

const int MN = 1003;

int N, K;
int G[MN][MN];
bool V[MN][MN];

const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};

int dfs(const int r, const int c, const int k) {
    if (r < 0 || r >= N || c < 0 || c >= N) return 0;
    if (V[r][c]) return 0;
    if (G[r][c] != k) return 0;

    V[r][c] = true;
    int ret = 1;
    for (int i=0; i<4; ++i) {
        int nr = r + chr[i];
        int nc = c + chc[i];
        ret += dfs(nr, nc, k);
    }

    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> G[i][j];
        }
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (dfs(i, j, G[i][j]) >= K) ++ans;
        }
    }

    cout << ans << '\n';
}
