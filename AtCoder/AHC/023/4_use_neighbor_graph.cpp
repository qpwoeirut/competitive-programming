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

using pii=pair<int,int>;
#define plant first
#define harvest second
#define row first
#define col second

const int INF = 1e9;

const int T = 100;
const int H = 20;
const int W = 20;
const int MAX_K = H * W * T;

const int chr[4] = { 0,  1,  0, -1 };
const int chc[4] = { 1,  0, -1,  0 };
const int RIGHT_WALL= 0b0001;
const int DOWN_WALL = 0b0010;
const int LEFT_WALL = 0b0100;
const int UP_WALL = 0b1000;

mt19937 rng(8);

int K, i0;
pii crop[MAX_K];
int wall[H][W];

void read_input() {
    int _T, _H, _W;
    cin >> _T >> _H >> _W >> i0;
    assert(T == _T && H == _H && W == _W);

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            wall[r][c] = 
                (r == 0 ? UP_WALL : 0) | 
                (c == 0 ? LEFT_WALL : 0) |
                (r + 1 == H ? DOWN_WALL : 0) |
                (c + 1 == W ? RIGHT_WALL : 0);
        }
    }
    for (int r = 0; r < H - 1; ++r) {
        string s; cin >> s;
        for (int c = 0; c < W; ++c) {
            if (s[c] == '1') {
                wall[r][c] |= DOWN_WALL;
                wall[r + 1][c] |= UP_WALL;
            }
        }
    }
    for (int r = 0; r < H; ++r) {
        string s; cin >> s;
        for (int c = 0; c < W - 1; ++c) {
            if (s[c] == '1') {
                wall[r][c] |= RIGHT_WALL;
                wall[r][c + 1] |= LEFT_WALL;
            }
        }
    }
    cin >> K;
    for (int i = 0; i < K; ++i) cin >> crop[i].plant >> crop[i].harvest;
}

struct Work {
    int k, i, j, s;
    Work() : Work(0, 0, 0, 0) {}
    Work(const int _k, const int _i, const int _j, const int _s) : k(_k), i(_i), j(_j), s(_s) {}

    string to_string() const {
        return std::to_string(k + 1) + " " + std::to_string(i) + " " + std::to_string(j) + " " + std::to_string(s);
    }
};

vector<int> plant_list[T + 1];
vector<int> harvest_list[T + 1];
pii position[H * W];
int dist[H][W];
void init() {
    for (int k = 0; k < K; ++k) {
        plant_list[crop[k].plant].push_back(k);
        harvest_list[crop[k].harvest].push_back(k);
    }
    for (int t = 0; t <= T; ++t) {
        sort(plant_list[t].begin(), plant_list[t].end(), [](const int ia, const int ib) {
            return crop[ia].harvest > crop[ib].harvest;
        });
    }

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            dist[r][c] = INF;
            position[r * W + c] = pii(r, c);
        }
    }

    queue<pii> q;
    q.emplace(i0, 0);
    dist[i0][0] = 0;
    while (!q.empty()) {
        const pii cur = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            if (wall[cur.row][cur.col] & (1 << dir)) continue;
            const int nrow = cur.row + chr[dir], ncol = cur.col + chc[dir];
            if (dist[nrow][ncol] == INF) {
                dist[nrow][ncol] = dist[cur.row][cur.col] + 1;
                q.emplace(nrow, ncol);
            }
        }
    }

    sort(position, position+H*W, [](const pii& a, const pii& b) {
        return dist[a.row][a.col] < dist[b.row][b.col];
    });
}

pii ngraph[H * W];
int n_ngraph;

bitset<W> in_ngraph[H];
bitset<W> visited[H];
void dfs_floodfill(int r, int c) {
    if (visited[r][c]) return;
    visited[r][c] = true;
    if (!in_ngraph[r][c]) return;
    for (int dir = 0; dir < 4; ++dir) {
        if (wall[r][c] & (1 << dir)) continue;
        dfs_floodfill(r + chr[dir], c + chc[dir]);
    }
}

int user[H][W];
bool ngraph_connected() {
    if (!in_ngraph[i0][0]) return false;

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            visited[r][c] = user[r][c] != -1;
        }
    }

    dfs_floodfill(i0, 0);
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (in_ngraph[r][c] && !visited[r][c]) return false;
        }
    }
    return true;
}

pii priority[H * W];
int n_priority;
void dfs_priority(const int r, const int c) {
    visited[r][c] = true;

    int dirs[4] = { 0, 1, 2, 3 };
    shuffle(dirs, dirs + 4, rng);

    int to_add[4];
    int n_add = 0;

    for (int d = 0; d < 4; ++d) {
        if (wall[r][c] & (1 << dirs[d])) continue;
        const int nr = r + chr[dirs[d]];
        const int nc = c + chc[dirs[d]];

        if (in_ngraph[nr][nc]) {
            if (!visited[nr][nc]) dfs_priority(nr, nc);
        }
        else to_add[n_add++] = dirs[d];
    }
    for (int i = 0; i < n_add; ++i) {
        priority[n_priority++] = pii(r + chr[to_add[i]], c + chc[to_add[i]]);
    }
}
void create_random_priority() {
    for (int r = 0; r < H; ++r) visited[r].reset();

    n_priority = 0;
    dfs_priority(i0, 0);
}

Work plan[MAX_K];
int n_plan;

bitset<MAX_K> in_plan;
Work work[MAX_K];
int create_plan() {
    in_plan.reset();
    n_plan = 0;

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            user[r][c] = -1;
        }
    }

    for (int t = 1; t <= T; ++t) {
        // planting phase
        for (const int k : plant_list[t]) {
            work[k] = Work(k, -1, -1, crop[k].plant);
            int min_diff = INF;
            for (int i = 0; i < n_ngraph; ++i) {
                if (user[ngraph[i].row][ngraph[i].col] != -1 || (ngraph[i].row == i0 && ngraph[i].col == 0)) continue;
                int diff = INF;
                for (int dir = 0; dir < 4; ++dir) {
                    if (wall[ngraph[i].row][ngraph[i].col] & (1 << dir)) continue;
                    const int nr = ngraph[i].row + chr[dir];
                    const int nc = ngraph[i].col + chc[dir];
                    if (user[nr][nc] != -1) {
                        diff = min(diff, crop[user[nr][nc]].harvest - crop[k].harvest);
                    } else if (!in_ngraph[nr][nc]) {
                        diff = -1;
                        break;
                    }
                }

                if (diff >= 0 && min_diff > diff) {
                    in_ngraph[ngraph[i].row][ngraph[i].col] = false;
                    if (ngraph_connected()) {
                        min_diff = diff;
                        work[k].i = ngraph[i].row;
                        work[k].j = ngraph[i].col;
                    }
                    in_ngraph[ngraph[i].row][ngraph[i].col] = true;
                }
            }
            if (work[k].i == -1) {
                for (int i = 0; i < n_priority; ++i) {
                    if (user[priority[i].row][priority[i].col] == -1) {
                        work[k].i = priority[i].row;
                        work[k].j = priority[i].col;
                        break;
                    }
                }
            }
            if (work[k].i != -1) {
                plan[n_plan++] = work[k];
                user[work[k].i][work[k].j] = k;
                in_plan[k] = true;
            }
        }

        // harvesting phase
        for (const int k : harvest_list[t]) {
            if (in_plan[k]) user[work[k].i][work[k].j] = -1;
        }
    }

    int score = 0;
    for (int i = 0; i < n_plan; ++i) {
        score += crop[plan[i].k].harvest - crop[plan[i].k].plant + 1;
    }

    return score;
}

void find_neighbor_graph() {
    for (int r = 0; r < H; ++r) in_ngraph[r].set();

    for (int i = H*W - 1; i > 0; --i) {
        for (int r = 0; r < H; ++r) {
            visited[r].reset();
        }
        in_ngraph[position[i].row][position[i].col] = false;
        dfs_floodfill(i0, 0);

        bool ok = true;
        for (int r = 0; r < H; ++r) {
            ok &= visited[r].count() == W;
        }
        if (!ok) in_ngraph[position[i].row][position[i].col] = true;
    }

    n_ngraph = 0;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (in_ngraph[r][c]) ngraph[n_ngraph++] = pii(r, c);
        }
    }
    //for (int r = 0; r < H; ++r) { for (int c = 0; c < W; ++c) { cerr << in_ngraph[r][c]; } cerr << '\n'; }
}

Work best_plan[MAX_K];
int n_best_plan;
int main() {
    const auto END_TIME = chrono::high_resolution_clock::now() + 1700ms;

    cin.tie(0)->sync_with_stdio(0);

    read_input();
    init();
    find_neighbor_graph();

    int best_score = 0;
    while (chrono::high_resolution_clock::now() < END_TIME) {
        create_random_priority();
        const int score = create_plan();
        if (best_score < score) {
            best_score = score;
            copy(plan, plan + n_plan, best_plan);
            n_best_plan = n_plan;
        }
        //debug(score);
    }

    cout << n_best_plan << '\n';
    for (int i = 0; i < n_best_plan; ++i) {
        cout << best_plan[i].to_string() << '\n';
    }
    best_score *= 1000000 / (H * W * T);
    debug(best_score);
}
