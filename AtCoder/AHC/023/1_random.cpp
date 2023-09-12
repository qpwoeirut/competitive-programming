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

Work plan[MAX_K];
int n_plan;
bitset<W> used[H];
bitset<W> visited[H];

bool reachable(int i, int j) {
    if (used[i][j] || used[i0][0]) {
        return false;
    } else if (i == i0 && j == 0) {
        return true;
    }
    //debug(i, j);

    for (int r = 0; r < H; ++r) visited[r] = used[r];

    queue<pii> q;
    q.emplace(i0, 0);
    visited[i0][0] = true;
    while (!q.empty()) {
        const pii cur = q.front(); q.pop();
        //debug(cur);
        for (int dir = 0; dir < 4; ++dir) {
            if (wall[cur.row][cur.col] & (1 << dir)) continue;

            const int nrow = cur.row + chr[dir], ncol = cur.col + chc[dir];
            if (nrow == i && ncol == j) {
                return true;
            } else if (!visited[nrow][ncol]) {
                visited[nrow][ncol] = true;
                q.emplace(nrow, ncol);
            }
        }
    }

    return false;
}

bitset<MAX_K> in_plan;
Work work[MAX_K];
int create_random_plan() {
    in_plan.set();

    vector<vector<Work>> plant_list(T + 1), harvest_list(T + 1);
    for (int k = 0; k < K; ++k) {
        work[k] = Work(k, rng() % H, rng() % W, crop[k].plant);
        plant_list[crop[k].plant].push_back(work[k]);
        harvest_list[crop[k].harvest].push_back(work[k]);
    }

    for (int r = 0; r < H; ++r) used[r].reset();

    for (int t = 1; t <= T; ++t) {
        // planting phase
        for (const Work &w : plant_list[t]) {
            if (!reachable(w.i, w.j)) {
                in_plan[w.k] = false;
            }
        }
        for (const Work &w : plant_list[t]) {
            if (used[w.i][w.j]) {
                in_plan[w.k] = false;
            } else if (in_plan[w.k]) {
                used[w.i][w.j] = true;
            }
        }

        // harvesting phase
        for (const Work &w : harvest_list[t]) {
            if (in_plan[w.k]) {
                used[w.i][w.j] = false;
            }
        }
        for (const Work &w : harvest_list[t]) {
            if (in_plan[w.k] && !reachable(w.i, w.j)) {
                in_plan[w.k] = false;
            }
        }
    }

    int score = 0;
    n_plan = 0;
    for (int k = 0; k < K; ++k) {
        if (in_plan[k]) {
            plan[n_plan++] = work[k];
            score += crop[k].harvest - crop[k].plant + 1;
        }
    }

    return score;
}

Work best_plan[MAX_K];
int n_best_plan;

int main() {
    const auto END_TIME = chrono::high_resolution_clock::now() + 1800ms;

    read_input();

    int best_score = 0;
    while (chrono::high_resolution_clock::now() < END_TIME) {
        const int score = create_random_plan();
        if (best_score < score) {
            best_score = score;
            copy(plan, plan + n_plan, best_plan);
            n_best_plan = n_plan;
        }
        //debug(score);
    }
    debug(best_score * 1e6 / (H * W * T));

    cout << n_best_plan << '\n';
    for (int i = 0; i < n_best_plan; ++i) {
        cout << best_plan[i].to_string() << '\n';
    }
}

