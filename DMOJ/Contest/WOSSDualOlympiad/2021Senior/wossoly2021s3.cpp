#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

using pii=pair<int,int>;

const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};
const int MN = 202;

int N, M;
string G[MN];
int dist[MN][MN];

pii pos_of(char c) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (G[i][j] == c) return pii(i, j);
        }
    }
    assert(0);
}

int solve(char start, char finish) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            dist[i][j] = 1e9;
        }
    }

    pii p = pos_of(start);
    dist[p.fi][p.se] = 0;
    
    deque<pii> q;
    q.push_front(p);

    while (q.size() > 0) {
        const pii cur = q.front(); q.pop_front();

        if (G[cur.fi][cur.se] == finish) {
            return dist[cur.fi][cur.se];
        }

        if (isalpha(G[cur.fi][cur.se]) && isupper(G[cur.fi][cur.se])) {
            const pii nxt = pos_of(tolower(G[cur.fi][cur.se]));
            dist[nxt.fi][nxt.se] = dist[cur.fi][cur.se];
            q.push_front(nxt);
            continue;
        }

        for (int i=0; i<4; ++i) {
            const pii nxt(cur.fi + chr[i], cur.se + chc[i]);
            if (nxt.fi < 0 || nxt.fi >= N || nxt.se < 0 || nxt.se >= M || G[nxt.fi][nxt.se] == '#' || (isalpha(G[nxt.fi][nxt.se]) && islower(G[nxt.fi][nxt.se]))) {
                continue;
            }
            if (dist[nxt.fi][nxt.se] > dist[cur.fi][cur.se] + 1) {
                dist[nxt.fi][nxt.se] = dist[cur.fi][cur.se] + 1;
                q.push_back(nxt);
            }
        }
    }

    return -1e8;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> G[i];
    }

    const int ans = solve('0', '1') + solve('1', '2') + solve('2', '3') + solve('3', '4');
    cout << (ans < 0 ? -1 : ans) << '\n';
}
