#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 105;
const int chr[4] = {1, 0, -1, 0}, chc[4] = {0, 1, 0, -1};

ll N, T;
ll G[MN][MN];
ll D[MN][MN][4];

struct Item {
    int r, c;
    ll dist;

    int grass;

    Item (const int _r, const int _c, const ll _dist, const int _grass) {
        r = _r;
        c = _c;
        dist = _dist;
        grass = _grass;
    }
    Item(const Item& prev, const int dir) {
        r = prev.r + chr[dir];
        c = prev.c + chc[dir];
        grass = (prev.grass + 2) % 3;
        dist = prev.dist + T;
        if (valid() && grass == 0) {
            dist += G[r][c];
        }
    }
    inline const bool operator<(const Item& other) const {
        if (dist == other.dist) {
            if (grass == other.grass) {
                if (r == other.r) {
                    return c < other.c;
                }
                return r < other.r;
            }
            return grass < other.grass;
        }
        return dist > other.dist;
    }
    bool valid() {
        return 0 <= r && r < N && 0 <= c && c < N && D[r][c][grass] > dist;
    }
    void upd_dist() {
        D[r][c][grass] = dist;
    }
    void print() {
        cerr << "r,c,dist,grass: " << r << ' ' << c << ' ' << dist << ' ' << grass << endl;
    }
};

int main() {
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> G[i][j];
            for (int k=0; k<4; ++k) {
                D[i][j][k] = 1e18;
            }
        }
    }

    priority_queue<Item> pq;
    pq.emplace(0, 0, 0, 0);
    D[0][0][0] = 0;

    while (pq.size() > 0) {
        Item cur = pq.top(); pq.pop();
        //cur.print();

        if (cur.r == N-1 && cur.c == N-1) {
            cout << cur.dist << endl;
            return 0;
        }

        for (int i=0; i<4; ++i) {
            Item nxt(cur, i);
            if (nxt.valid()) {
                nxt.upd_dist();
                pq.push(nxt);
            }
        }
    }

    assert(false);
}
