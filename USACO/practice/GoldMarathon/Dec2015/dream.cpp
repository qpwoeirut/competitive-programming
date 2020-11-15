//dream.cpp created at 11/12/20 17:14:50

#include <bits/stdc++.h>

using namespace std;

const int MN = 1005;
const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};

int N, M;
int G[MN][MN];

bool V[MN][MN][4][2];

struct Item {
    int r, c;
    int dir;
    bool smell;
    int dist;

    Item(int _r, int _c, int _dir, bool _smell, int _dist) {
        r = _r;
        c = _c;
        dir = _dir;
        smell = _smell;
        dist = _dist;

        if (inside()) {
            smell |= G[r][c] == 2;
            if (G[r][c] == 4) smell = false;
        }
    }

    bool inside() {
        return 0 <= r && r < N && 0 <= c && c < M;
    }

    bool visitable() {
        return inside() && G[r][c] != 0 && !(G[r][c] == 3 && !smell);
    }

    bool valid() {
        return visitable() && !V[r][c][dir][smell];
    }

    void set_visited() {
        if (G[r][c] == 4) {
            V[r][c][dir][smell] = true;
        } else {
            for (int i=0; i<4; ++i) {
                V[r][c][i][smell] = true;
            }
        }
    }
    void print() {
        cerr << r << ',' << c << ' ' << dir << ' ' << smell << ": " << dist << endl;
    }
};

int main() {
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
        }
    }

    queue<Item> q;
    Item start(0, 0, 0, false, 0);
    start.set_visited();
    q.push(start);

    while (q.size() > 0) {
        Item cur = q.front(); q.pop();
        //cur.print();

        if (cur.r == N-1 && cur.c == M-1) {
            cout << cur.dist << endl;
            return 0;
        }

        if (G[cur.r][cur.c] == 4) {
            Item nxt(cur.r + chr[cur.dir], cur.c + chc[cur.dir], cur.dir, cur.smell, cur.dist + 1);
            if (nxt.visitable()) {
                nxt.set_visited();
                q.push(nxt);
                continue;
            }
        }

        for (int i=0; i<4; ++i) {
            Item nxt(cur.r + chr[i], cur.c + chc[i], i, cur.smell, cur.dist + 1);

            if (nxt.valid()) {
                nxt.set_visited();
                q.push(nxt);
            }
        }
    }

    cout << -1 << endl;
}

