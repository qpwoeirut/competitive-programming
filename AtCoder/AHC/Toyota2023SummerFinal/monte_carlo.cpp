#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

using ll=long long;
using pii=pair<int,int>;
#define row first
#define col second

const int BLOCKED = 99;
const int EMPTY = -1;

const int D = 9;
int N, M;
int G[D+2][D+2];
const int enter_r = 1, enter_c = 1 + (D - 1) / 2;


mt19937 rng(8);


ll transport(int grid[D + 2][D + 2]);

int H[D+2][D+2];
void copy_grid() {
    for (int r=0; r<D+2; ++r) {
        for (int c=0; c<D+2; ++c) {
            H[r][c] = G[r][c];
        }
    }
}
bitset<D + 2> visited[D + 2];
int dfs(int r, int c) {
    if (r < 1 || r > D || c < 1 || c > D || visited[r][c]) return 0;
    visited[r][c] = true;
    return 1 + dfs(r - 1, c) + dfs(r, c - 1) + dfs(r + 1, c) + dfs(r, c + 1);
}
bool grid_invalid() {
    int expected = 0;
    for (int r=1; r<=D; ++r) {
        for (int c=1; c<=D; ++c) {
            visited[r][c] = G[r][c] != EMPTY;
            expected += G[r][c] == EMPTY;
        }
    }
    const int real = dfs(enter_r, enter_c);
    //debug(real, expected);
    return real < expected;
}

int order[D * D];
int n_order;

pii open[D * D];
int n_open;
ll simulate(int nr, int nc, int val, const set<int>& remaining) {
    //debug(nr, nc, val);
    G[nr][nc] = val;
    if (grid_invalid()) {
        G[nr][nc] = EMPTY;
        return -1;
    }
    copy(remaining.begin(), remaining.end(), order);
    n_order = remaining.size();

    n_open = 0;
    for (int r = 1; r <= D; ++r) {
        for (int c = 1; c <= D; ++c) {
            if (G[r][c] == EMPTY && (r != 1 || c != 1 + (D - 1) / 2)) open[n_open++] = pii(r, c);
        }
    }
    //debug1(open, n_open);

    ll score = 0;
    for (int i=0; i<90; ++i) {
        copy_grid();
        shuffle(order, order + n_order, rng);
        shuffle(open, open + n_open, rng);

        for (int j = 0; j < n_order; ++j) {
            H[open[j].row][open[j].col] = order[j];
        }

        //debug(n_order, n_open);
        //debug2(H, D + 2, D + 2);
        score += transport(H);
    }

    G[nr][nc] = EMPTY;
    return score;
}

void place() {
    set<int> remaining;
    for (int i = 0; i < M; ++i) remaining.insert(i);
    for (int i = 0; i < M; ++i) {
        int val;
        cin >> val;
        remaining.erase(val);

        pii best(-1, -1);
        ll best_score = -1;
        for (int r=1; r<=D; ++r) {
            for (int c=1; c<=D; ++c) {
                if (G[r][c] == EMPTY) {
                    const ll score = simulate(r, c, val, remaining);
                    //debug(val, r, c, score);
                    if (best_score < score) {
                        best_score = score;
                        best = pii(r, c);
                    }
                }
            }
        }

        G[best.row][best.col] = val;
        cout << best.row - 1 << ' ' << best.col - 1 << '\n';
        cout.flush();

        //debug2(G, D+2, D+2);
    }
}

inline int calculate_score(const int B) {
    return round(1e9 - 1e9 * B / ((D * D - N) * (D * D - N - 1) / 2));
}

struct Location {
    int r, c;
    int val;
    Location() : r(0), c(0), val(0) {}
    Location(const int _r, const int _c, const int _val) : r(_r), c(_c), val(_val) {}
    inline bool operator<(const Location& o) const {
        return val < o.val || (val == o.val && (r < o.r || (r == o.r && c < o.c)));
    }
};

const int chr[4] = { 1, 0, -1, 0 };
const int chc[4] = { 0, 1, 0, -1 };

Location answer[D * D];
int n_answer;
pii q[D * D * 4];
int q0, q1;
ll transport(int grid[D + 2][D + 2]) {
    for (int r=1; r<=D; ++r) visited[r].reset();
    //debug2(grid, D+2, D+2);

    q0 = q1 = 0;
    q[q1++] = pii(enter_r, enter_c);
    visited[enter_r][enter_c] = true;

    n_answer = 0;
    set<Location> available;
    while (n_answer < M) {
        while (q0 < q1) {
            const pii cur = q[q0++];
            if (grid[cur.row][cur.col] == EMPTY) {
                for (int i = 0; i < 4; ++i) {
                    if (grid[cur.row + chr[i]][cur.col + chc[i]] != BLOCKED && !visited[cur.row + chr[i]][cur.col + chc[i]]) {
                        visited[cur.row + chr[i]][cur.col + chc[i]] = true;
                        q[q1++] = pii(cur.row + chr[i], cur.col + chc[i]);
                    }
                }
            } else if (grid[cur.row][cur.col] != BLOCKED && grid[cur.row][cur.col] != EMPTY) {
                available.emplace(cur.row, cur.col, grid[cur.row][cur.col]);
            }
        }

        assert(available.size() > 0);
        answer[n_answer] = *available.begin();
        grid[answer[n_answer].r][answer[n_answer].c] = EMPTY;
        q[q1++] = pii(answer[n_answer].r, answer[n_answer].c);

        ++n_answer;
        available.erase(available.begin());
    }

    int B = 0;
    for (int i=0; i<M; ++i) {
        for (int j=i+1; j<M; ++j) {
            B += answer[i].val > answer[j].val;
        }
    }
    return calculate_score(B);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int r=0; r<D+2; ++r) {
        for (int c=0; c<D+2; ++c) {
            G[r][c] = BLOCKED;
        }
    }
    for (int r=1; r<=D; ++r) {
        for (int c=1; c<=D; ++c) {
            G[r][c] = EMPTY;
        }
    }

    int d;
    cin >> d >> N;
    M = D * D - N - 1;

    for (int i=0; i<N; ++i) {
        int ri, rj;
        cin >> ri >> rj; ++ri; ++rj;
        G[ri][rj] = BLOCKED;
    }

    place();
    transport(G);
    for (int i = 0; i < n_answer; ++i) {
        cout << answer[i].r - 1 << ' ' << answer[i].c - 1 << '\n';
    }
    cout.flush();
}
