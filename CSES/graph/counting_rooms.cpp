//counting_rooms.cpp created at 12/18/20 14:12:19

#include <bits/stdc++.h>

using namespace std;

const int MN = 1005;

int N, M;
bool G[MN][MN];
bool V[MN][MN];

const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};
void dfs(int r, int c) {
    if (r < 0 || r >= N || c < 0 || c >= M) return;
    if (!G[r][c] || V[r][c]) return;

    V[r][c] = true;
    for (int i=0; i<4; ++i) {
        dfs(r + chr[i], c + chc[i]);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == '.';
        }
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (G[i][j] && !V[i][j]) {
                ++ans;
                dfs(i, j);
            }
        }
    }

    cout << ans << endl;
}

