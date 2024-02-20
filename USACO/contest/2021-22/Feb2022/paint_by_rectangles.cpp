#include <bits/stdc++.h>

using namespace std;

const int MN = 6005;
const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};

int N, T;
int A[MN][MN];

void bfs(const int r, const int c, const int v) {
    queue<pair<int,int>> q;
    q.emplace(r, c);
    A[r][c] = -1;
    while (q.size() > 0) {
        const pair<int,int> p = q.front(); q.pop();
        for (int i=0; i<4; ++i) {
            const int nr = p.first + chr[i];
            const int nc = p.second + chc[i];
            if (nr < 0 || nc < 0 || nr >= MN || nc >= MN || A[nr][nc] != v) continue;
            A[nr][nc] = -1;
            q.emplace(nr, nc);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T;
    for (int i=0; i<N; ++i) {
        int r1, c1, r2, c2;
        cin >> c1 >> r1 >> c2 >> r2;
        ++A[r1][c1]; --A[r1][c2]; --A[r2][c1]; ++A[r2][c2];
    }

    for (int r=1; r<MN; ++r) {
        for (int c=1; c<MN; ++c) {
            A[r][c] += A[r-1][c] + A[r][c-1] - A[r-1][c-1];
        }
    }

    int ans[2] = {0, 0};
    for (int r=0; r<MN; ++r) {
        for (int c=0; c<MN; ++c) {
            if (A[r][c] != -1) {
                ++ans[A[r][c] & 1];
                bfs(r, c, A[r][c]);
            }
        }
    }

    if (T == 1) {
        cout << ans[0] + ans[1] << '\n';
    } else {
        cout << ans[0] << ' ' << ans[1] << '\n';
    }
}
