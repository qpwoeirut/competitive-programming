#include <bits/stdc++.h>

using namespace std;

const int MN = 1001;
const int chr[4] = {1, 0, -1, 0};
const int chc[4] = {0, 1, 0, -1};

struct Item {
    int r, c;
    int dist;
    Item(int _r, int _c, int _dist) {
        r = _r;
        c = _c;
        dist = _dist;
    }
};

int N, M;
string grid[MN];
bool visited[MN][MN];

int main() {
    //cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;

    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int i=0; i<N; ++i) {
        cin >> grid[i];
        for (int j=0; j<M; ++j) {
            if (grid[i][j] == 'S') {
                sr = i;
                sc = j;
            }
            if (grid[i][j] == 'E') {
                er = i;
                ec = j;
            }
        }
    }
    assert(sr != -1 && sc != -1 && er != -1 && ec != -1);

    queue<Item> q;
    q.push(Item(sr, sc, 0));

    while (q.size() > 0) {
        Item cur = q.front();
        q.pop();

        if (cur.r == er && cur.c == ec) {
            cout << cur.dist << endl;
            return 0;
        }

        for (int i=0; i<4; ++i) {
            Item nxt(cur.r + chr[i], cur.c + chc[i], cur.dist + 1);
            if (nxt.r < 0 || nxt.r >= N || nxt.c < 0 || nxt.c >= M) continue;
            if (!visited[nxt.r][nxt.c] && grid[nxt.r][nxt.c] != 'B') {
                visited[nxt.r][nxt.c] = true;
                q.push(nxt);
            }
        }
    }

    cout << -1 << endl;
}
    
