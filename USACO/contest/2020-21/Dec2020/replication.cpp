#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 1005;
const int INIT = 1001001001;

int N, D;
string G[MN];

int d1[MN][MN];
int d2[MN][MN];
int rem[MN][MN];

const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> D;

    for (int i=0; i<N; ++i) {
        cin >> G[i];
    }

    queue<pii> q1, q2;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            d1[i][j] = d2[i][j] = INIT;
            if (G[i][j] == 'S') {
                q1.emplace(i, j);
                d1[i][j] = 0;
            } else if (G[i][j] == '#') {
                q2.emplace(i, j);
                d2[i][j] = 0;
            }
        }
    }

    while (q2.size() > 0) {
        const pii cur = q2.front(); q2.pop();

        for (int i=0; i<4; ++i) {
            const int nr = cur.fi + chr[i];
            const int nc = cur.se + chc[i];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N || G[nr][nc] == '#' || d2[nr][nc] < INIT) continue;
            d2[nr][nc] = d2[cur.fi][cur.se] + 1;
            q2.emplace(nr, nc);
        }
    }

    while (q1.size() > 0) {
        const pii cur = q1.front(); q1.pop();

        int rsize = d1[cur.fi][cur.se] / D;
        if (rsize >= d2[cur.fi][cur.se]) continue;

        for (int i=0; i<4; ++i) {
            const int nr = cur.fi + chr[i];
            const int nc = cur.se + chc[i];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N || rsize >= d2[nr][nc] || d1[nr][nc] < INIT) continue;
            d1[nr][nc] = d1[cur.fi][cur.se] + 1;
            q1.emplace(nr, nc);
        }
    }


    queue<pii> q;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (d1[i][j] == INIT) rem[i][j] = -1;
            else {
                int sub = d1[i][j] / D >= d2[i][j];
                rem[i][j] = (d1[i][j] - sub) / D;
                q.emplace(i, j);
            }
        }
    }


    //for (int i=0; i<N; ++i) { for (int j=0; j<N; ++j) { cerr << (d1[i][j] == INIT ? -1 : d1[i][j]) << '\t'; } cerr << endl; } cerr << endl;
    //for (int i=0; i<N; ++i) { for (int j=0; j<N; ++j) { cerr << rem[i][j] << '\t'; } cerr << endl; }
    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();
        //cerr << cur.fi << ' ' << cur.se << ' ' << rem[cur.fi][cur.se] << endl;

        if (rem[cur.fi][cur.se] == 0) continue;
        for (int i=0; i<4; ++i) {
            const int nr = cur.fi + chr[i];
            const int nc = cur.se + chc[i];

            assert(G[nr][nc] != '#');

            if (rem[nr][nc] < rem[cur.fi][cur.se] - 1) {
                rem[nr][nc] = rem[cur.fi][cur.se] - 1;
                q.emplace(nr, nc);
            }
        }
    }
    //for (int i=0; i<N; ++i) { for (int j=0; j<N; ++j) { cerr << rem[i][j] << '\t'; } cerr << endl; }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (rem[i][j] >= 0) ++ans;
        }
    }

    cout << ans << endl;
}

