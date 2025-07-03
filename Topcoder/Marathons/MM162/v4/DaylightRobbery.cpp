#pragma GCC optimize("Ofast,unroll-loops")

#include <bits/stdc++.h>
#include "moves.h"

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

using ll = long long;

template<typename T>
typename std::enable_if<std::is_integral<T>::value, string>::type to_base(T x, const int base) {
    const bool negative = x < 0;
    string s;
    while (x > 0) {
        s += '0' + (x % base);
        x /= base;
    }
    reverse(s.begin(), s.end());
    return s.empty() ? "0" : (negative ? "-" + s : s);
}

struct Point {
    int x, y;

    Point() : x(0), y(0) {}
    Point(const int x, const int y) : x(x), y(y) {}

    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    bool operator!=(const Point& p) const { return x != p.x || y != p.y; }
    Point operator-() const { return {-x, -y}; }
    Point operator*(const int t) const { return {x * t, y * t}; }
    Point operator/(const int t) const { return {x / t, y / t}; }

    int dot(const Point& other) const { return x * other.x + y * other.y; }
    int det(const Point& other) const { return x * other.y - y * other.x; }

    double norm() const { return sqrtl(x * x + y * y); }
    double angle() const { return atan2(y, x); }
    int sqnorm() const { return x * x + y * y; }

    friend istream& operator>>(istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << p.x << ' ' << p.y;
        return os;
    }
};

string to_string(const Point& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

int ccw(const Point& A, const Point& B, const Point& C) {
    const int x = (B - A).det(C - A);
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

struct Triangle {
    Point a, b, c;

    Triangle() : a(), b(), c() {}
    Triangle(const Point& a, const Point& b, const Point& c) : a(a), b(b), c(c) {}

    bool contains(const Point& p) const {
        const int d1 = ccw(a, b, p);
        const int d2 = ccw(b, c, p);
        const int d3 = ccw(c, a, p);
        return (d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0);
    }

    bool can_bribe(const Point& p) const {
        return p == a;
    }
};

const int MAX_C = 100;
const int MAX_G = 50;

const int RUN_SPEED = 400;
const int CROUCH_SPEED = 200;

const int SIZE = 10000;
const int TURNS = 1000;
const int ESCAPE_BONUS = 5000;

int C, G, B;
Point coin[MAX_C];
vector<Triangle> guard[2][MAX_G];

struct Game {
    int turn;

    int score, collected;
    Point thief;
    
    uint64_t m_coin0, m_coin1;
    uint64_t m_guard;

    Game(const Point& thief) : turn(0), score(TURNS * C + ESCAPE_BONUS), thief(thief), m_coin0(0), m_coin1(0), m_guard(0) {}
    Game(const Game& other) : turn(other.turn), score(other.score), collected(other.collected), thief(other.thief), m_coin0(other.m_coin0), m_coin1(other.m_coin1), m_guard(other.m_guard) {}

    bool move(const Point& target) {
        // debug("move", thief, target, (target - thief).sqnorm());
        const int dist = (target - thief).sqnorm();
        assert(dist <= RUN_SPEED * RUN_SPEED);

        ++turn;
        thief = target;

        if (target.x < 0 || target.x >= SIZE || target.y < 0 || target.y >= SIZE) {
            score -= ESCAPE_BONUS;
            return false;
        }

        bool crouching = dist <= CROUCH_SPEED * CROUCH_SPEED;
        for (int i = 0; i < G; ++i) {
            if ((m_guard & (1LL << i)) == 0 && guard[crouching][i][turn % guard[crouching][i].size()].can_bribe(thief)) {
                crouching = false;
                m_guard |= 1LL << i;
                score += 20 * B;
            }
        }

        for (int i = 0; i < G; ++i) {
            if ((m_guard & (1LL << i)) == 0 && guard[crouching][i][turn % guard[crouching][i].size()].contains(thief)) {
                return false;
            }
        }

        for (int i = 0; i < C && i < 64; ++i) {
            if ((m_coin0 & (1ULL << i)) == 0 && thief == coin[i]) {
                score -= TURNS - turn;
                m_coin0 |= 1ULL << i;
                ++collected;
            }
        }
        for (int i = 64; i < C; ++i) {
            if ((m_coin1 & (1ULL << (i - 64))) == 0 && thief == coin[i]) {
                score -= TURNS - turn;
                m_coin1 |= 1ULL << (i - 64);
                ++collected;
            }
        }
        return turn < TURNS;
    }

    bool safe(int turn, const Point& p, bool crouching) const {
        for (int g = 0; g < G; ++g) {
            if ((m_guard & (1LL << g)) == 0 && guard[crouching][g][turn % guard[crouching][g].size()].contains(p)) {
                return false;
            }
        }
        return true;
    }

    bool safe_bribe(int turn, const Point& p) const {
        for (int g = 0; g < G; ++g) {
            if ((m_guard & (1LL << g)) == 0 && guard[0][g][turn % guard[0][g].size()].contains(p) && !guard[0][g][turn % guard[0][g].size()].can_bribe(p)) {
                return false;
            }
        }
        return true;
    }
};

string to_string(const Game& game) {
    return "(turn=" + to_string(game.turn) + ", thief=" + to_string(game.thief) + ", score=" + to_string(game.score) + ", m_coin0=" + to_base(game.m_coin0, 2) + ", m_coin1=" + to_base(game.m_coin1, 2) + ", m_guard=" + to_base(game.m_guard, 2) + ")";
}

struct Moves {
    int n;
    Point moves[TURNS];

    Moves() : n(0) {}
    Moves(const Moves& other) : n(other.n) {
        copy(other.moves, other.moves + other.n, moves);
    }
};

struct State {
    Point pos;
    int turn;
    double heuristic;

    State(const Point& pos, const int turn, const double heuristic) : pos(pos), turn(turn), heuristic(heuristic) {}

    bool operator<(const State& other) const {
        return heuristic > other.heuristic;
    }
    bool operator==(const State& other) const {
        return pos == other.pos && turn == other.turn;
    }
    bool operator!=(const State& other) const {
        return !(*this == other);
    }
};

struct StateHash {
    size_t operator()(const State& state) const {
        return (size_t)state.pos.x * 2000 * 15000 + state.pos.y * 2000 + state.turn;
    }
};

string to_string(const State& state) {
    return "(pos=" + to_string(state.pos) + ", turn=" + to_string(state.turn) + ", heuristic=" + to_string(state.heuristic) + ")";
}

int recover_moves(const unordered_map<State, State, StateHash>& back_move, State cur, Moves& moves) {
    int n = 0;
    unordered_map<State, State, StateHash>::const_iterator it = back_move.find(cur);
    while (it != back_move.end()) {
        if (moves.n + n >= TURNS) return -1;
        moves.moves[moves.n + n++] = cur.pos;
        cur = it->second;
        it = back_move.find(cur);
    }
    reverse(moves.moves + moves.n, moves.moves + moves.n + n);
    return n;
}

const int MAX_SEARCH = 50000;
double heuristic(const double dist) {
    return dist * 0.01966903866 + dist * 0.003443700872;
}

const int TIME_LIMIT = 9600;
chrono::time_point<chrono::high_resolution_clock> end_time;

int moves_out(const Game& game, Moves& moves) {
    // debug("moves_out", game);
    unordered_map<State, State, StateHash> back_move;
    priority_queue<State> pq;
    pq.emplace(game.thief, game.turn, heuristic(min({game.thief.x + 1, game.thief.y + 1, SIZE - game.thief.x, SIZE - game.thief.y})));
    for (int i = 0; i < MAX_SEARCH && pq.size() > 0; ++i) {
        const State cur = pq.top(); pq.pop();
        // debug(i, pq.size(), cur);

        if (cur.pos.x - RUN_SPEED < 0) {
            const State nstate(cur.pos + Point{-RUN_SPEED, 0}, cur.turn + 1, 0);
            back_move.insert({nstate, cur});
            return recover_moves(back_move, nstate, moves);
        }
        if (cur.pos.y - RUN_SPEED < 0) {
            const State nstate(cur.pos + Point{0, -RUN_SPEED}, cur.turn + 1, 0);
            back_move.insert({nstate, cur});
            return recover_moves(back_move, nstate, moves);
        }
        if (cur.pos.x + RUN_SPEED >= SIZE) {
            const State nstate(cur.pos + Point{RUN_SPEED, 0}, cur.turn + 1, 0);
            back_move.insert({nstate, cur});
            return recover_moves(back_move, nstate, moves);
        }
        if (cur.pos.y + RUN_SPEED >= SIZE) {
            const State nstate(cur.pos + Point{0, RUN_SPEED}, cur.turn + 1, 0);
            back_move.insert({nstate, cur});
            return recover_moves(back_move, nstate, moves);
        }

        if (chrono::high_resolution_clock::now() > end_time) {
            return -1;
        }

        for (int j = 0; j < CROUCH_MOVES; ++j) {
            const Point nxt = cur.pos + Point{CROUCH_X[j], CROUCH_Y[j]};
            if (!game.safe(cur.turn + 1, nxt, true)) continue;

            const State nstate(nxt, cur.turn + 1, heuristic(min({nxt.x + 1, nxt.y + 1, SIZE - nxt.x, SIZE - nxt.y})) + cur.turn + 1 - game.turn);
            if (back_move.insert({nstate, cur}).second) {
                for (int m = 1; m <= 10 && game.safe(nstate.turn + m, nxt, true); ++m) {
                    back_move.insert({State(nxt, nstate.turn + m, nstate.heuristic), nstate});
                }
                pq.emplace(nstate);
            }
        }

        for (int j = 0; j < RUN_MOVES; ++j) {
            const Point nxt = cur.pos + Point{RUN_X[j], RUN_Y[j]};
            if (!game.safe(cur.turn + 1, nxt, false)) continue;

            const State nstate(nxt, cur.turn + 1, heuristic(min({nxt.x + 1, nxt.y + 1, SIZE - nxt.x, SIZE - nxt.y})) + cur.turn + 1 - game.turn);
            if (back_move.insert({nstate, cur}).second) {
                for (int m = 1; m <= 10 && game.safe(nstate.turn + m, nxt, true); ++m) {
                    back_move.insert({State(nxt, nstate.turn + m, nstate.heuristic), nstate});
                }
                pq.emplace(nstate);
            }
        }
    }

    debug("failed", game);
    return -1;
}

unordered_set<ll> failures;
int moves_to(const Game& game, const Point& target, const bool target_is_bribe, Moves& moves) {
    // debug("moves_to", game, target, target_is_bribe);
    const ll op_hash = ((ll)(game.thief.x * SIZE + game.thief.y) * SIZE + target.x) * SIZE + target.y;
    if (failures.count(op_hash)) return -1;
    if ((game.thief - target).sqnorm() >= RUN_SPEED * RUN_SPEED * 20 * 20) return -1;

    unordered_map<State, State, StateHash> back_move;
    priority_queue<State> pq;
    pq.emplace(game.thief, game.turn, heuristic((game.thief - target).norm()));
    for (int i = 0; i < MAX_SEARCH && pq.size() > 0; ++i) {
        const State cur = pq.top(); pq.pop();
        // debug(i, pq.size(), cur, target, (target - cur.pos).sqnorm());
        if ((target - cur.pos).sqnorm() <= CROUCH_SPEED * CROUCH_SPEED && !target_is_bribe && game.safe(cur.turn + 1, target, true)) {
            const State nstate(target, cur.turn + 1, 0);
            back_move.insert({nstate, cur});
            return recover_moves(back_move, nstate, moves);
        }
        if ((target - cur.pos).sqnorm() <= RUN_SPEED * RUN_SPEED && (target_is_bribe ? game.safe_bribe(cur.turn + 1, target) : game.safe(cur.turn + 1, target, false))) {
            const State nstate(target, cur.turn + 1, 0);
            back_move.insert({nstate, cur});
            return recover_moves(back_move, nstate, moves);
        }

        if (chrono::high_resolution_clock::now() > end_time) {
            return -1;
        }

        for (int j = 0; j < CROUCH_MOVES; ++j) {
            const Point nxt = cur.pos + Point{CROUCH_X[j], CROUCH_Y[j]};
            if (nxt.x < 0 || nxt.x >= SIZE || nxt.y < 0 || nxt.y >= SIZE || !game.safe(cur.turn + 1, nxt, true)) continue;

            const State nstate(nxt, cur.turn + 1, heuristic((nxt - target).norm()) + cur.turn + 1 - game.turn);
            if (back_move.insert({nstate, cur}).second) {
                pq.emplace(nstate);
            }
        }

        for (int j = 0; j < RUN_MOVES; ++j) {
            const Point nxt = cur.pos + Point{RUN_X[j], RUN_Y[j]};
            if (nxt.x < 0 || nxt.x >= SIZE || nxt.y < 0 || nxt.y >= SIZE || !game.safe(cur.turn + 1, nxt, false)) continue;

            const State nstate(nxt, cur.turn + 1, heuristic((nxt - target).norm()) + cur.turn + 1 - game.turn);
            if (back_move.insert({nstate, cur}).second) {
                pq.emplace(nstate);
            }
        }
    }

    debug("failed", game, target, target_is_bribe);
    failures.insert(op_hash);
    return -1;
}

void recurse(const Game& game, const Moves& moves, int& best_score, Moves& best_moves) {
    debug(game, moves.n);
    if (best_score > game.score) {
        best_score = game.score;
        best_moves = Moves(moves);
        debug(game, moves.n);
    }

    Game esc(game);
    Moves esc_moves(moves);

    int esc_n_moves = moves_out(esc, esc_moves);
    if (esc_n_moves != -1) {
        for (int i = 0; i < esc_n_moves; ++i) {
            esc.move(esc_moves.moves[esc_moves.n + i]);
        }
        esc_moves.n += esc_n_moves;
        if (best_score > esc.score) {
            best_score = esc.score;
            best_moves = Moves(esc_moves);
            debug(esc, esc_moves.n);
        }
    }

    int n = 0;
    int order[C];
    for (int i = 0; i < C; ++i) {
        if (i < 64 && (game.m_coin0 & (1LL << i)) == 0) order[n++] = i;
        if (i >= 64 && (game.m_coin1 & (1LL << (i - 64))) == 0) order[n++] = i;
    }
    sort(order, order + n, [&](int i, int j){return (game.thief - coin[i]).sqnorm() < (game.thief - coin[j]).sqnorm();});

    int closest_dist = (game.thief - coin[order[0]]).sqnorm();
    
    for (int i = 0; i < n; ++i) {
        Moves collect_moves(moves);
        Game collect(game);
        int n_moves = moves_to(collect, coin[order[i]], false, collect_moves);
        debug(i, game, (game.thief - coin[order[i]]).sqnorm(), closest_dist, n_moves);
        if (n_moves != -1) {
            for (int j = 0; j < n_moves; ++j) {
                collect.move(collect_moves.moves[collect_moves.n + j]);
            }
            collect_moves.n += n_moves;
            recurse(collect, collect_moves, best_score, best_moves);
        }
    }
}

int main() {
    cin >> C >> G >> B;
    for (int i = 0; i < C; ++i) cin >> coin[i];
    for (int i = 0; i < G; ++i) {
        int n;
        cin >> n;
        guard[0][i].resize(n);
        guard[1][i].resize(n);
        for (int j = 0; j < n; ++j) {
            Point p0, p1, p2, p3, p4;
            cin >> p0 >> p1 >> p2 >> p3 >> p4;
            guard[0][i][j] = Triangle(p0, p3, p4);
            guard[1][i][j] = Triangle(p0, p1, p2);
        }
    }
    Point thief;
    cin >> thief;

    end_time = chrono::high_resolution_clock::now() + chrono::milliseconds(TIME_LIMIT);

    int best_score = 2 * SIZE * SIZE;
    Moves moves;
    recurse(Game(thief), Moves(), best_score, moves);

    if (moves.n == 0) {
        moves.n = 1;
        moves.moves[0] = thief;
    }
    cout << moves.n << '\n';
    for (int i = 0; i < moves.n; ++i) {
        cout << moves.moves[i].x << ' ' << moves.moves[i].y << '\n';
    }

    // cerr << moves.n << '\n';
    // for (int i = 0; i < moves.n; ++i) {
    //     cerr << moves.moves[i].x << ' ' << moves.moves[i].y << '\n';
    // }
}
