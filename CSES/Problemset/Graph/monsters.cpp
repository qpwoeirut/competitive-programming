//monsters.cpp created at 12/18/20 23:14:58

#include <bits/stdc++.h>

using namespace std;

const int MN = 1005;
const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};
const string dir = "DRUL";

struct Item {
    bool me;
    int r, c;

    Item(const int _r, const int _c, const bool _me) {
        r = _r;
        c = _c;
        me = _me;
    }
};

int N, M;
string G[MN];

int par[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    queue<Item> q;
    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> G[i];
    }

    int sr = -1, sc = -1;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            par[i][j] = 4;
            if (G[i][j] == 'M') {
                q.emplace(i, j, false);
            } else if (G[i][j] == 'A') {
                sr = i;
                sc = j;
            } else {
                par[i][j] = -1;
            }
        }
    }
    assert(sr != -1 && sc != -1);
    q.emplace(sr, sc, true);

    while (q.size() > 0) {
        const Item cur = q.front(); q.pop();

        if (cur.me && (cur.r == 0 || cur.r == N-1 || cur.c == 0 || cur.c == M-1)) {
            int r = cur.r;
            int c = cur.c;

            cout << "YES" << endl;
            string ans;
            while (G[r][c] != 'A') {
                ans.push_back(dir[par[r][c]]);
                const int nr = r - chr[par[r][c]];
                const int nc = c - chc[par[r][c]];
                r = nr;
                c = nc;
            }
            reverse(ans.begin(), ans.end());
            cout << ans.size() << endl;
            cout << ans << endl;
            return 0;
        }

        for (int i=0; i<4; ++i) {
            const int nr = cur.r + chr[i], nc = cur.c + chc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M || par[nr][nc] != -1 || G[nr][nc] == '#') continue;

            par[nr][nc] = i;
            q.emplace(nr, nc, cur.me);
        }
    }

    cout << "NO" << endl;
}

