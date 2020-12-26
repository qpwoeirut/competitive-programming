/*
ID: zhongbr1
TASK: camelot
LANG: C++14
*/

//camelot.cpp created at 12/23/20 11:57:23


#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MX = 32;
const int MN = MX * MX;
const int INIT = 1001001;

const int chr[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int chc[8] = {2, 1, -1, -2, -2, -1, 1, 2};

struct Item {
    int r, c;
    int dst;
    bool has_king;

    Item(const int _r, const int _c, const int _dst, const bool _has_king) {
        r = _r;
        c = _c;
        dst = _dst;
        has_king = _has_king;
    }
    inline const bool operator<(const Item& other) const {
        if (dst == other.dst) {
            if (has_king == other.has_king) {
                if (r == other.r) return c < other.c;
            }
            return has_king > other.has_king;
        }
        return dst > other.dst;
    }
};

int R, C;
int N;
pii A[MN];
pii king;
int dist[MN][MX][MX][2];

bool chmn(int& a, const int b) {return a>b ? ((a=b) || true) : false;}

int kdist(const int r, const int c) {
    return max(abs(king.fi - r), abs(king.se - c));
}

void calc(const int idx) {
    for (int i=0; i<R; ++i) {
        for (int j=0; j<C; ++j) {
            dist[idx][i][j][0] = dist[idx][i][j][1] = INIT;
        }
    }

    priority_queue<Item> q;
    q.emplace(A[idx].fi, A[idx].se, 0, false);
    dist[idx][A[idx].fi][A[idx].se][0] = 0;

    while (q.size() > 0) {
        const Item cur = q.top(); q.pop();

        if (dist[idx][cur.r][cur.c][cur.has_king] < cur.dst) continue;

        for (int i=0; i<8; ++i) {
            const int nr = cur.r + chr[i], nc = cur.c + chc[i];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;

            if (chmn(dist[idx][nr][nc][cur.has_king], cur.dst + 1)) {
                q.emplace(nr, nc, dist[idx][nr][nc][cur.has_king], cur.has_king);
            }
        }

        if (!cur.has_king && chmn(dist[idx][cur.r][cur.c][1], cur.dst + kdist(cur.r, cur.c))) {
            q.emplace(cur.r, cur.c, dist[idx][cur.r][cur.c][1], true);
        }
    }
}

int main() {
    freopen("camelot.in", "r", stdin);
    freopen("camelot.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> R >> C;
    char c;
    cin >> c >> king.se;
    king.fi = c - 'A';
    king.se -= 1;
    swap(king.fi, king.se);

    N = 0;
    cin >> ws;
    while (cin.peek() != EOF) {
        cin >> c >> A[N].se >> ws;
        A[N].fi = c - 'A';
        A[N].se -= 1;
        swap(A[N].fi, A[N].se);
        ++N;
    }

    for (int i=0; i<N; ++i) {
        calc(i);
    }

    int ans = N == 0 ? 0 : INIT;
    for (int j=0; j<R; ++j) {
        for (int k=0; k<C; ++k) {
            int sum = 0, best = INIT;
            for (int i=0; i<N; ++i) {
                sum += dist[i][j][k][0];
                chmn(best, dist[i][j][k][1] - dist[i][j][k][0]);
            }
            sum += best;
            chmn(ans, sum);
        }
    }
    //for (int i=0; i<N; ++i) { for (int j=0; j<R; ++j) { for (int k=0; k<C; ++k) { cerr << dist[i][j][k][0] << ' ' << dist[i][j][k][1] << "  "; } cerr << endl; } cerr << endl; }

    cout << ans << endl;
}

