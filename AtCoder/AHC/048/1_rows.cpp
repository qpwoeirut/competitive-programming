#pragma GCC optimize("O3,unroll-loops")

#include <iostream>
#include <bitset>
#include <cassert>
#include <cmath>
#include <queue>
#include <unordered_map>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

inline double square(const double& x) {
    return x * x;
}

struct Color {
    double amount;
    int capacity;
    double c, m, y;

    Color() : amount(0), capacity(0), c(0), m(0), y(0) {}
    Color(const int _capacity) : amount(0), capacity(_capacity), c(0), m(0), y(0) {}

    Color(const Color& c1, const Color& c2) {
        capacity = c1.capacity + c2.capacity;
        amount = c1.amount + c2.amount;
        c = (c1.c * c1.amount + c2.c * c2.amount) / amount; 
        m = (c1.m * c1.amount + c2.m * c2.amount) / amount; 
        y = (c1.y * c1.amount + c2.y * c2.amount) / amount; 
    }

    double error(const Color& color) const {
        return sqrt(square(c - color.c) + square(m - color.m) + square(y - color.y));
    }
};

string to_string(const Color& color) {
    return "Color(amt=" + to_string(color.amount) + ",cap=" + to_string(color.capacity) + ",c=" + to_string(color.c) + ",m=" + to_string(color.m) + ",y=" + to_string(color.y) + ")";
}

const int N = 20;
int K;
const int H = 1000;
int T;
int D;

const int MAX_T = 64000;
const double INF = 1e10;

using hash_t = unsigned long long;
using phi = pair<hash_t, int>;
const int HM = 10000;
const int SH = 14;
const long long MULT = 72057594037928017LL;  // first prime after 2^56
struct Row {
    Color color[N];
    int n;
    int left;

    Row() : n(1), left(1) {
        color[0] = Color(N);
    }

    bool split(int c) {
        //debug("split", c, n);
        assert(1 <= c && c < N);
        if ((left >> c) & 1) return false;
        left |= 1 << c;
        for (int i = 0, col = 0; i < n; ++i) {
            col += color[i].capacity;
            if (col >= c) {
                assert(col > c);
                for (int j = n - 1; j > i; --j) color[j + 1] = color[j];
                ++n;

                const int b = col - c;
                const int a = color[i].capacity - b;
                color[i + 1] = color[i];

                color[i].capacity = a;
                color[i].amount *= (double)(a) / (a + b);
                color[i + 1].capacity = b;
                color[i + 1].amount *= (double)(b) / (a + b);

                return true;
            }
        }
        assert(0);
    }

    bool merge(int c) {
        //debug("merge", c);
        assert(1 <= c && c < N);
        if (((left >> c) & 1) == 0) return false;
        left ^= 1 << c;
        for (int i = 0, col = 0; i < n; ++i) {
            col += color[i].capacity;
            if (col >= c) {
                assert(col == c);
                assert(i + 1 < n);

                color[i] = Color(color[i], color[i + 1]);

                --n;
                for (int j = i + 1; j < n; ++j) color[j] = color[j + 1];

                return true;
            }
        }
        assert(0);
    }

    bool pour(int c, const Color& color_to_pour) {
        assert(0 <= c && c < N);
        assert((left >> c) & 1);
        for (int i = 0, col = 0; i < n; ++i) {
            col += color[i].capacity;
            if (col > c) {
                if (color[i].amount + 1 > color[i].capacity) return false;
                color[i] = Color(color[i], color_to_pour);
                return true;
            }
        }
        assert(0);
    }

    int give(const Color& targ) {
        double best_error = INF;
        int best_i = -1;
        int best_col = -1;
        for (int i = 0, col = 0; i < n; ++i) {
            col += color[i].capacity;
            if (color[i].amount < 1) continue;
            const double error = color[i].error(targ);
            if (best_error > error) {
                best_error = error;
                best_i = i;
                best_col = col - 1;
            }
        }
        assert(best_col != -1 && best_i != -1);
        color[best_i].amount -= 1;
        return best_col;
    }

    Color discard(int c) {
        assert(0 <= c && c < N);
        assert((left >> c) & 1);
        for (int i = 0, col = 0; i < n; ++i) {
            col += color[i].capacity;
            if (col > c) {
                color[i].amount = max(color[i].amount - 1, 0.0);
                return color[i];
            }
        }
        assert(0);
    }

    bool empty() const {
        return n == 1 && color[0].amount == 0;
    }

    double error(const Color& target) const {
        double best = INF;
        for (int i = 0; i < n; ++i) {
            if (color[i].amount >= 1) best = min(best, color[i].error(target));
        }
        return best;
    }
    
    hash_t hash() const {
        hash_t value = 0;
        for (int i = 0; i < n; ++i) {
            hash_t cell = (((llround(color[i].c * HM) << SH) | llround(color[i].m * HM)) << SH) | llround(color[i].y * HM);
            cell = llround(color[i].amount * HM) ? ((cell << SH) | llround(color[i].amount * HM)) : 0;
            value = value * MULT + ((cell << 5) | color[i].capacity);
        }
        return value;
    }
};

string to_string(const Row& row) {
    string s = "[";
    for (int i = 0; i < row.n; ++i) {
        if (i) s += ",";
        s += to_string(row.color[i]);
    }
    s += "]";
    return s;
}

struct State {
    Row row;
    int pours;
    int turns;

    State() {}
    State(const Row& _row, const int _pours, const int _turns) : row(_row), pours(_pours), turns(_turns) {}

    const bool operator<(const State& o) const {
        return pours > o.pours || (pours == o.pours && turns > o.turns);
    }
};

Color own[20];
Color target[H];

const int POUR = 1;
const int GIVE = 2;
const int DISCARD = 3;
const int TOGGLE = 4;

inline int pack(int op, int a, int b) { return (((b << 6) | a) << 6) | op; }
inline int pack(int op, int a, int b, int c) { return (pack(a, b, c) << 6) | op; }
inline int pack(int op, int a, int b, int c, int d) { return (pack(a, b, c, d) << 6) | op; }

unordered_map<hash_t, pair<State, int>> visited;
State search(const int turn_limit, const Color& targ, Row row, int r, int moves[]) {
    State best_state(row, 0, 0);
    priority_queue<State> pq;
    pq.push(best_state);

    visited.clear();
    visited[row.hash()] = pair<State, int>(best_state, 0);

    double best_cost = row.error(targ);

    const auto update = [&](const State& before, State& state, int operation) {
        ++state.turns;
        if (visited.insert({state.row.hash(), pair<State, int>(before, operation)}).second == true) {  // TODO: enforce ordering
            const double cost = state.row.error(targ) * 10000 + state.pours * D;
            if (best_cost > cost) {
                best_cost = cost;
                best_state = state;
            }
            pq.push(state);
        }
    };

    while (pq.size() > 0) {
        const State cur = pq.top(); pq.pop();
        if (cur.pours * D >= best_cost) break;
        if (cur.turns >= turn_limit) continue;

        //for (int i = 1; i < N; ++i) {
        //    State nstate = cur;
        //    if (nstate.row.split(i));
        //    else assert(nstate.row.merge(i));
        //    update(cur, nstate, pack(TOGGLE, r, i - 1, r, i));
        //}

        //for (int i = 0; i < N; ++i) {
        //    if (((cur.row.left >> i) & 1) == 0) continue;
        //    State nstate = cur;
        //    nstate.row.discard(i);
        //    update(cur, nstate, pack(DISCARD, r, i));

        //    for (int k = 0; k < K; ++k) {
        //        nstate = cur;
        //        if (nstate.row.pour(i, own[k])) {
        //            ++nstate.pours;
        //            update(cur, nstate, pack(POUR, r, i, k));
        //        }
        //    }
        //}
        State nstate = cur;
        nstate.row.discard(0);
        update(cur, nstate, pack(DISCARD, r, 0));

        for (int k = 0; k < K; ++k) {
            nstate = cur;
            if (nstate.row.pour(0, own[k])) {
                ++nstate.pours;
                update(cur, nstate, pack(POUR, r, 0, k));
            }
        }
    }

    State trace = best_state;
    for (int i = best_state.turns - 1; i >= 0; --i) {
        const pair<State, int> before = visited[trace.row.hash()];
        trace = before.first;
        moves[i] = before.second;

        assert(trace.turns == i);
    }
    return best_state;
}

struct Board {
    bitset<N * N> above;
    Row rows[N];

    Board() {
        for (int i = 0; i < above.size(); ++i) above[i] = true;
    }

    friend ostream& operator<<(ostream& os, const Board& board) {
        for (int r = 0; r < N; ++r) {
            for (int c = 1; c < N; ++c) {
                if (c > 1) os << ' ';
                os << ((board.rows[r].left >> c) & 1);
            }
            os << '\n';
        }
        for (int r = 1; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (c) os << ' ';
                os << board.above[r * N + c];
            }
            os << '\n';
        }

        return os;
    }
};

int final_moves[MAX_T], best_moves[MAX_T], cur_moves[MAX_T];
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _N, _H;
    cin >> _N >> K >> _H >> T >> D;
    assert(N == _N);
    assert(H == _H);

    for (int k = 0; k < K; ++k) {
        cin >> own[k].c >> own[k].m >> own[k].y;
        own[k].amount = 1;
        own[k].capacity = 0;
    }
    for (int h = 0; h < H; ++h) {
        cin >> target[h].c >> target[h].m >> target[h].y;
        target[h].amount = 1;
        target[h].capacity = 0;
    }

    Board board;
    cout << board;

    int total_turns = 0;
    double total_cost = 1 - (D * H);
    for (int h = 0; h < H; ++h) {
        const int turn_limit = 4; //(T - total_turns) / (H - h);

        double best_cost = INF;
        State best_state;
        int best_row = -1;

        bool empty = false;
        for (int r = 0; r < N; ++r) {
            if (board.rows[r].empty()) {
                if (empty) continue;
                empty = true;
            }

            const State result = search(turn_limit - 1, target[h], board.rows[r], r, cur_moves);
            const double cost = result.row.error(target[h]) * 10000 + result.pours * D;
            if (best_cost > cost) {
                best_cost = cost;
                best_state = result;
                best_row = r;
                copy(cur_moves, cur_moves + result.turns, best_moves);
            }
        }

        total_turns = copy(best_moves, best_moves + best_state.turns, final_moves + total_turns) - final_moves;
        total_cost += best_cost;

        debug(best_state.row);
        board.rows[best_row] = best_state.row;
        const int c = board.rows[best_row].give(target[h]);
        final_moves[total_turns++] = pack(GIVE, best_row, c);

        debug(best_row, best_cost);
        debug(h, total_turns, total_cost);
    }

    for (int i = 0; i < total_turns; ++i) {
        const int op = final_moves[i] & 63;
        const int a = (final_moves[i] >>  6) & 63;
        const int b = (final_moves[i] >> 12) & 63;
        const int c = (final_moves[i] >> 18) & 63;
        const int d = (final_moves[i] >> 24) & 63;
        if (op == POUR) {
            cout << POUR << ' ' << a << ' ' << b << ' ' << c << '\n';
        } else if (op == GIVE || op == DISCARD) {
            cout << op << ' ' << a << ' ' << b << '\n';
        } else if (op == TOGGLE) {
            cout << TOGGLE << ' ' << a << ' ' << b << ' ' << c << ' ' << d << '\n';
        }
    }

    debug(total_cost);
}
