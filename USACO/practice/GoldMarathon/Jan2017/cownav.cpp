#include <bits/stdc++.h>

using namespace std;

const int chr[4] = {1, 0, -1, 0}, chc[4] = {0, 1, 0, -1};
const int MN = 25;
int N;
bool G[MN][MN], V[MN][MN][MN][MN][4];

struct Item {
    int r1, c1;
    int r2, c2;
    int dir;
    int dist;

    Item(const int _r1, const int _c1, const int _r2, const int _c2, const int _dir, const int _dist) {
        r1 = _r1;
        c1 = _c1;
        r2 = _r2;
        c2 = _c2;
        dir = _dir;
        dist = _dist;
    }

    Item(const Item& prev, int move) {
        dir = (prev.dir + 4 + move) & 3;
        if (move == 0) {
            r1 = prev.r1 + chr[dir];
            c1 = prev.c1 + chc[dir];
            if (G[r1][c1] || (prev.r1 == N && prev.c1 == N)) {
                r1 = prev.r1;
                c1 = prev.c1;
            }

            r2 = prev.r2 + chr[(dir + 1) & 3];
            c2 = prev.c2 + chc[(dir + 1) & 3];
            if (G[r2][c2] || (prev.r2 == N && prev.c2 == N)) {
                r2 = prev.r2;
                c2 = prev.c2;
            }
        } else {
            r1 = prev.r1;
            c1 = prev.c1;
            r2 = prev.r2;
            c2 = prev.c2;
        }

        dist = prev.dist + 1;
    }
    bool set_v() {
        bool ret = V[r1][c1][r2][c2][dir];
        V[r1][c1][r2][c2][dir] = true;
        return !ret;
    }
    bool done() {
        return r1 == N && c1 == N && r2 == N && c2 == N;
    }
    void print() {
        cerr << r1 << ',' << c1 << ' ' << r2 << ',' << c2 << ' ' << dir << ' ' << dist << endl;
    }
};

int main() {
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=N; i>=1; --i) {
        for (int j=1; j<=N; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == 'H';
        }
    }
    for (int i=0; i<=N+1; ++i) {
        G[i][0] = G[i][N+1] = G[0][i] = G[N+1][i] = true;
    }
    //for (int i=0; i<=N+1; ++i) { for (int j=0; j<=N+1; ++j) { cerr << G[i][j]; } cerr << endl; }

    queue<Item> q;
    q.emplace(1, 1, 1, 1, 0, 0);
    V[1][1][1][1][0] = true;
    while (q.size() > 0) {
        Item cur = q.front();
        q.pop();
        //cur.print();

        if (cur.done()) {
            cout << cur.dist << endl;
            return 0;
        }

        Item turn_left(cur, -1);
        Item forward(cur, 0);
        Item turn_right(cur, 1);

        if (turn_left.set_v()) {
            q.push(turn_left);
        }
        if (forward.set_v()) {
            q.push(forward);
        }
        if (turn_right.set_v()) {
            q.push(turn_right);
        }
    }
    assert(false);
}
