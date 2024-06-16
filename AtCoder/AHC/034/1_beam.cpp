#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

using namespace std;

using pii = pair<int, int>;

const int N = 20;
using grid_t = array<short, N * N>;

const char DIRS[4] = {'R', 'D', 'L', 'U'};
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

const int MOVE_COST = 100;
int FIX_MULT = 8;
int COST_MULT = 7;

struct State {
    grid_t G;
    int r, c;
    int soil;
    int cost;
    int to_fix;

    int parent;

    State(const grid_t& _G, const int _r, const int _c, const int s, const int co, const int tf, const int par) : G(_G), r(_r), c(_c), soil(s), cost(co), to_fix(tf), parent(par) {}

    State(const State& s, const int nr, const int nc, const int par) : G(s.G), r(nr), c(nc), soil(s.soil), cost(s.cost), to_fix(s.to_fix), parent(par) {
        const int amt = G[r * N + c] >= 0 ? G[r * N + c] : -min(soil, -G[r * N + c]);

        const int dist = abs(r - s.r) + abs(c - s.c);
        const int move_cost = dist * (soil + MOVE_COST);

        soil += amt;
        G[r * N + c] -= amt;
        to_fix -= abs(amt);

        cost += move_cost + abs(amt);
    }
    State() {
        cost = to_fix = 1e9;
        parent = -1;
    }

    int value() {
        return FIX_MULT * to_fix + COST_MULT * cost;
    }
};

const int MOVES = 3 * N * N;
const int ITER = 2 * N;
const int MAX_WIDTH = 50 * N;
const auto STOP_TIME = chrono::steady_clock::now() + 1960ms;

grid_t A;

State moves[MOVES * MAX_WIDTH];
int n_move;

int q[MOVES][MAX_WIDTH];
int n_queue[MOVES];

bool comp_move(const int a, const int b) {
    return moves[a].value() > moves[b].value();
}

void add_children(const int m, const int cur) {
    if (m + 1 == MOVES) return;
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N && n_queue[m + 1] < MAX_WIDTH && n_move < MOVES * MAX_WIDTH; ++c) {
            if (moves[cur].G[r * N + c] > 0 || (moves[cur].G[r * N + c] < 0 && moves[cur].soil > 0)) {
                moves[n_move] = State(moves[cur], r, c, cur);
                q[m + 1][n_queue[m + 1]++] = n_move++;
                push_heap(q[m + 1], q[m + 1] + n_queue[m + 1], comp_move);
            }
        }
    }
}

void recover_ops(int cur, vector<pii>& ops) {
    while (cur > 0) {
        const int r = moves[cur].r, c = moves[cur].c;
        const int par = moves[cur].parent;
        const int diff = moves[par].G[r * N + c] - moves[cur].G[r * N + c];

        if (diff != 0) ops.emplace_back(diff, 0);

        int dr = moves[cur].r - moves[par].r;
        int dc = moves[cur].c - moves[par].c;
        for (; dc > 0; --dc) ops.emplace_back(0, RIGHT);
        for (; dr > 0; --dr) ops.emplace_back(0, DOWN);
        for (; dc < 0; ++dc) ops.emplace_back(0, LEFT);
        for (; dr < 0; ++dr) ops.emplace_back(0, UP);

        cur = par;
    }
    reverse(ops.begin(), ops.end());
}

int beam_search(const int base, vector<pii>& ops) {
    fill(n_queue, n_queue + MOVES, 0);
    n_move = 0;

    int best = 0;

    moves[n_move++] = State(A, 0, 0, 0, 0, base, -1);
    q[0][n_queue[0]++] = 0;
    while (chrono::steady_clock::now() < STOP_TIME) {
        for (int i=0; i < MOVES; ++i) {
            for (int j=0; j<ITER && n_queue[i] > 0; ++j) {
                pop_heap(q[i], q[i] + n_queue[i], comp_move);
                const int cur = q[i][--n_queue[i]];
                if (moves[cur].to_fix == 0) {
                    if (best == 0 || moves[best].cost > moves[cur].cost) {
                        best = cur;
                    }
                } else add_children(i, cur);
            }
        }
    }

    if (best == 0) return 0;
    recover_ops(best, ops);
    return round(1e9 * (double)base / moves[best].cost);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _N;
    cin >> _N;
    assert(N == _N);
    
    int base = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> A[i*N + j];
            base += abs(A[i*N + j]);
        }
    }

    vector<pii> ops;
    const int score = beam_search(base, ops);

    cout << showpos;
    for (const pii& p: ops) {
        if (p.first == 0) cout << DIRS[p.second] << '\n';
        else cout << p.first << '\n';
    }
}
