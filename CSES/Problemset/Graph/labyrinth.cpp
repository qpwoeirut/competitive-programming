//labyrinth.cpp created at 12/18/20 14:19:35

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 1005;

int N, M;
string G[MN];
int par[MN][MN];

const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};
const string dir = "DRUL";

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int sr = -1, sc = -1, fr = -1, fc = -1;
    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> G[i];
        for (int j=0; j<M; ++j) {
            par[i][j] = -1;
            if (G[i][j] == 'A') {
                sr = i;
                sc = j;
            } else if (G[i][j] == 'B') {
                fr = i;
                fc = j;
            }
        }
    }
    assert(sr != -1 && sc != -1 && fr != -1 && fc != -1);

    queue<pii> q;
    q.emplace(sr, sc);
    par[sr][sc] = 4;

    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();

        if (cur.fi == fr && cur.se == fc) {
            break;
        }

        for (int i=0; i<4; ++i) {
            const int nr = cur.fi + chr[i];
            const int nc = cur.se + chc[i];

            if (nr < 0 || nr >= N || nc < 0 || nc >= M || G[nr][nc] == '#' || par[nr][nc] != -1) continue;
            par[nr][nc] = i;
            q.emplace(nr, nc);
        }
    }

    string ans;
    int r = fr, c = fc;
    while (par[r][c] != -1 && (r != sr || c != sc)) {
        ans.push_back(dir[par[r][c]]);
        const int nr = r - chr[par[r][c]];
        const int nc = c - chc[par[r][c]];
        r = nr;
        c = nc;
    }

    if (r == sr && c == sc) {
        reverse(ans.begin(), ans.end());
        cout << "YES\n";
        cout << ans.size() << '\n';
        cout << ans << endl;
    } else {
        cout << "NO\n";
    }
}        

