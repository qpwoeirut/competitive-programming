/*
Stealing ideas from BOI 2020 Mixture
http://www.boi2020.lv/data/tasks/en/day1/mixture.pdf
http://www.boi2020.lv/data/spoilers/mixture.pdf

Also maybe useful:
https://stackoverflow.com/questions/13437589/how-is-pythons-fractions-limit-denominator-implemented
https://math.stackexchange.com/questions/3415854/ratios-between-consecutive-k-smooth-numbers

Using 3 colors should be sufficient
Try all triplets and use gauss-jordan to find solution
Scale up largest color to 1, only 3 pours should be necessary (maybe not for smaller D?)
Pick a base based on turn limit
Draw a snake pattern in the grid, toggle dividers and discard to build the fraction

Later:
allow limit_denominator to return either closest or lower bound
use reverse order to handle very small values
handle targets outside the triangle
add alternative solution for low T
try only using one or two colors
try beam search or randomness
implement the exact epsilon scheme that the problem has
*/

#pragma GCC optimize("O3,unroll-loops")

#include <iostream>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <numeric>
#include <vector>

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
inline int clamp(int a, int b, int c) {
    return a >= b ? a : (b >= c ? c : b);
}

// ======================================== COLOR REPRESENTATION ========================================
struct Color {
    double amount;
    int capacity;
    double c, m, y;

    Color() : amount(0), capacity(0), c(0), m(0), y(0) {}
    Color(const int _capacity) : amount(0), capacity(_capacity), c(0), m(0), y(0) {}

    Color(const Color& c1, const Color& c2) {
        amount = c1.amount + c2.amount;
        capacity = c1.capacity + c2.capacity;
        c = (c1.c * c1.amount + c2.c * c2.amount) / amount;
        m = (c1.m * c1.amount + c2.m * c2.amount) / amount;
        y = (c1.y * c1.amount + c2.y * c2.amount) / amount;
        assert(amount <= capacity);
    }

    Color split(int to_split) {
        double old_cap = capacity;

        Color split_out(*this);
        split_out.capacity = to_split;
        split_out.amount *= split_out.capacity / old_cap;

        capacity -= to_split;
        amount *= capacity / old_cap;

        //debug("split", *this, split_out);
        return split_out;
    }

    double error(const Color& color) const {
        return sqrt(square(c - color.c) + square(m - color.m) + square(y - color.y));
    }
};

string to_string(const Color& color) {
    return "Color(amt=" + to_string(color.amount) + ",cap=" + to_string(color.capacity) + ",c=" + to_string(color.c) + ",m=" + to_string(color.m) + ",y=" + to_string(color.y) + ")";
}

// ======================================== PROBLEM INPUT ========================================
const int N = 20;
int K;
const int H = 1000;
int T;
int D;

Color own[20];
Color target[H];

const double INF = 1e10;
const double EPS = 1e-14;
const double MGN = 1e-6;

// ======================================== PACKING MOVES ========================================
const int POUR = 1;
const int GIVE = 2;
const int DISCARD = 3;
const int TOGGLE = 4;

inline int pack(int op, int a, int b) { return (((b << 6) | a) << 6) | op; }
inline int pack(int op, int a, int b, int c) { return (pack(a, b, c) << 6) | op; }
inline int pack(int op, int a, int b, int c, int d) { return (pack(a, b, c, d) << 6) | op; }

// ======================================== BOARD REPRESENTATION ========================================
const int COLUMN[2] = {(N / 2) - 2, (N / 2) + 1};

struct Board {
    Color base;
    Color parts[2][200];
    int n[2];
    bool connected[2];
    bitset<N * N> above, left;

    double cost;

    Board() : cost(1) {
        base = Color(2);
        parts[0][0] = parts[1][0] = Color(199);
        n[0] = n[1] = 1;
        connected[0] = connected[1] = false;

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                above[r * N + c] = true;
                left[r * N + c] = true;
            }
        }

        const int h = N / 2;
        for (int r = 0; r < N; ++r) {
            for (int c = 1; c < h; ++c) {
                left[r * N + c] = false;
                left[r * N + c + h] = false;
            }
        }
        for (int r = 1; r < N; ++r) {
            if (r & 1) {
                above[r * N] = false;
                above[r * N + N - 1] = false;
            } else {
                above[r * N + h - 1] = false;
                above[r * N + h] = false;
            }
        }

        left[h - 1] = true;
        left[h] = false;
        left[h + 1] = true;
    }

    void pour_base(const int k, vector<int>& moves) {
        assert(!connected[0] && !connected[1]);

        base = Color(base, own[k]);
        moves.push_back(pack(POUR, 0, N / 2, k));
        cost += D;
    }
    void pour(int idx, const int k, vector<int>& moves) {
        assert(!connected[idx]);

        parts[idx][0] = Color(parts[idx][0], own[k]);
        moves.push_back(pack(POUR, 0, COLUMN[idx], k));
        cost += D;
    }

    void give(const Color& targ, vector<int>& moves) {
        assert(base.amount >= 1);

        base.amount -= 1;
        if (connected[0]) parts[0][0] = base;
        if (connected[1]) parts[1][0] = base;
        moves.push_back(pack(GIVE, 0, N / 2));
        cost += targ.error(base) * 10000;
    }

    void set(const int idx, int pos, vector<int>& moves) {
        assert(!connected[idx]);
        ++pos;
        const int r = pos / 10;
        int c;
        if (pos % 10 == 0) {
            c = (r & 1) ? 0 : (N / 2) - 1;
            if (idx == 1) c = N - c - 1;
        } else {
            c = (r & 1) ? pos % 10 : 10 - (pos % 10);
            if (idx == 1) c = N - c;
        }

        if (pos % 10 == 0) {
            assert(above[r * N + c] == false);
            above[r * N + c] = true;
            moves.push_back(pack(TOGGLE, r - 1, c, r, c));
        } else {
            assert(1 <= c && c < N);
            assert(left[r * N + c] == false);
            left[r * N + c] = true;
            moves.push_back(pack(TOGGLE, r, c - 1, r, c));
        }

        for (int i = 0, cur = 1; i < n[idx]; ++i) {
            cur += parts[idx][i].capacity;
            if (cur >= pos) {
                assert(cur > pos);
                for (int j = n[idx] - 1; j > i; --j) {
                    parts[idx][j + 1] = parts[idx][j];
                }
                parts[idx][i + 1] = parts[idx][i].split(cur - pos);
                ++n[idx];
                debug(parts[idx][i], parts[idx][i + 1]);

                break;
            }
        }

        debug("set", idx, pos, r, c);
        debug1(parts[idx], n[idx]);
    }

    void merge(int idx, int p_idx, vector<int>& moves) {
        debug(idx, p_idx);
        assert(p_idx > 0);

        int pos = 199;
        for (int i = n[idx] - 1; i >= p_idx; --i) {
            pos -= parts[idx][i].capacity;
            debug(i, parts[idx][i]);
        }

        const int r = pos / 10;
        int c;
        if (pos % 10 == 0) {
            c = (r & 1) ? 0 : (N / 2) - 1;
            if (idx == 1) c = N - c - 1;
        } else {
            c = (r & 1) ? pos % 10 : 10 - (pos % 10);
            if (idx == 1) c = N - c;
        }
        debug("merge", idx, p_idx, pos, r, c);
        debug1(parts[idx], n[idx]);

        if (pos % 10 == 0) {
            assert(above[r * N + c] == true);
            above[r * N + c] = false;
            moves.push_back(pack(TOGGLE, r - 1, c, r, c));
        } else {
            assert(1 <= c && c < N);
            assert(left[r * N + c] == true);
            left[r * N + c] = false;
            moves.push_back(pack(TOGGLE, r, c - 1, r, c));
        }

        parts[idx][p_idx - 1] = Color(parts[idx][p_idx - 1], parts[idx][p_idx]);
        --n[idx];
        for (int j = p_idx; j < n[idx]; ++j) {
            parts[idx][j] = parts[idx][j + 1];
        }

        if (connected[idx]) {
            base = parts[idx][0];
            if (connected[idx ^ 1]) parts[idx ^ 1][0] = base;
        }
        
        debug1(parts[idx], n[idx]);
    }

    void toggle(const int idx, vector<int>& moves) {
        debug("toggle", idx, connected[idx]);
        assert(idx == 0 || idx == 1);
        connected[idx] = !connected[idx];
        if (connected[idx]) {
            base = parts[idx][0] = Color(base, parts[idx][0]);
        } else {
            int other_cap = 0;
            for (int i = 1; i < n[idx]; ++i) other_cap += parts[idx][i].capacity;
            parts[idx][0] = base.split(199 - other_cap);
        }
        if (connected[idx ^ 1]) parts[idx ^ 1][0] = base;

        moves.push_back(pack(TOGGLE, 0, COLUMN[idx] - 1, 0, COLUMN[idx]));
        debug1(parts[idx], n[idx]);
    }

    void reset(vector<int>& moves) {
        debug("reset start", n[0], n[1], connected[0], connected[1]);
        while (n[0] > 1) {
            merge(0, n[0] - 1, moves);
        }
        while (n[1] > 1) {
            merge(1, n[1] - 1, moves);
        }

        while (base.amount > 0) {
            base.amount = max(0.0, base.amount - 1);
            moves.push_back(pack(DISCARD, 0, N / 2));
        }
        if (connected[0]) {
            parts[0][0] = base;
            toggle(0, moves);
        }
        if (connected[1]) {
            parts[1][0] = base;
            toggle(1, moves);
        }
        while (parts[0][0].amount > 0) {
            parts[0][0].amount = max(0.0, parts[0][0].amount - 1);
            moves.push_back(pack(DISCARD, 0, COLUMN[0]));
        }
        while (parts[1][0].amount > 0) {
            parts[1][0].amount = max(0.0, parts[1][0].amount - 1);
            moves.push_back(pack(DISCARD, 0, COLUMN[1]));
        }
        debug("reset end", n[0], n[1], connected[0], connected[1]);
    }

    friend ostream& operator<<(ostream& os, const Board& board) {
        for (int r = 0; r < N; ++r) {
            for (int c = 1; c < N; ++c) {
                if (c > 1) os << ' ';
                os << (board.left[r * N + c] & 1);
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

// ======================================== MATH STUFF ========================================
using proportion = array<double, 3>;
// https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
proportion calculate_proportion(const Color& a, const Color& b, const Color& c, const Color& targ) {
    const int n = 3;
    const int m = 3;
    double mat[n][m + 1] = {
        {a.c, b.c, c.c, targ.c},
        {a.m, b.m, c.m, targ.m},
        {a.y, b.y, c.y, targ.y}
    };

    int where[m] = {-1, -1, -1};
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs(mat[i][col]) > abs(mat[sel][col]))
                sel = i;
        if (abs(mat[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap(mat[sel][i], mat[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                const double x = mat[i][col] / mat[row][col];
                for (int j=col; j<=m; ++j)
                    mat[i][j] -= mat[row][j] * x;
            }
        ++row;
    }

    double ans[m] = {0, 0, 0};
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = mat[where[i]][m] / mat[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * mat[i][j];
        assert(abs(sum - mat[i][m]) < EPS);
    }

    const double test_c = a.c * ans[0] + b.c * ans[1] + c.c * ans[2];
    const double test_m = a.m * ans[0] + b.m * ans[1] + c.m * ans[2];
    const double test_y = a.y * ans[0] + b.y * ans[1] + c.y * ans[2];
    assert(abs(targ.c / test_c - targ.m / test_m) < EPS);
    assert(abs(targ.c / test_c - targ.y / test_y) < EPS);

    return proportion({ans[0], ans[1], ans[2]});
}

using ll = long long;
pair<ll, ll> approximate(double x) {
    ll den = 1;
    for (int i=0; i<61 && x < (1LL << 61); ++i) {
        x *= 2;
        den <<= 1;
    }
    const ll num = llround(x);
    return pair<ll, ll>(num / gcd(num, den), den / gcd(num, den));
}

// https://github.com/python/cpython/issues/95723
pair<ll, ll> limit_denominator(ll m, ll n, ll lim) {
    ll a = n, b = m % n;
    ll p = 1, q = 0;
    ll r = m / n, s = 1;
    bool v = true;
    while (0 < b && q + a / b * s <= lim) {
        const ll _a = a, _b = b, _p = p, _q = q;
        a = _b;
        b = _a % _b;
        p = r;
        q = s;
        r = _p + _a / _b * r;
        s = _q + _a / _b * s;
        v = !v;
    }
    if (v) return pair<ll, ll>(r / gcd(r, s), s / gcd(r, s));
    const ll t = p + (lim - q) / s * r;
    const ll u = q + (lim - q) / s * s;
    return pair<ll, ll>(t / gcd(t, u), u / gcd(t, u));
}

// ======================================== MAIN LOGIC ========================================
void half_combo(Board& board, const int idx, double r, const int k, const int turn_lim, vector<int>& moves) {
    debug(idx, r, k, turn_lim);

    if (turn_lim <= 1) {
        board.pour(idx, k, moves);
        return;
    }

    int cur = 1;
    const int iters = (turn_lim + 2) / 4;
    for (int i = 0; i < iters; ++i) {
        cerr << "\n\n\n";
        pair<ll, ll> frac;
        if (i * 4 + 2 == turn_lim) {
            frac.first = lround(r * (200 - cur));
            frac.second = 200 - cur;
        } else {
            pair<ll, ll> r_frac = approximate(r);
            frac = limit_denominator(r_frac.first, r_frac.second, (200 - cur) / (iters - i));
        }
        assert(frac.first < frac.second);
        if (frac.first == 0) break;

        debug(i, idx, cur, frac);
        debug1(board.parts[idx], board.n[idx]);

        if (cur + frac.second < 200) board.set(idx, cur + frac.second, moves);
        if (i == 0) {
            board.pour(idx, k, moves);
            board.set(idx, cur + frac.first, moves);
        } else {
            board.merge(idx, 2, moves);
            board.set(idx, cur + frac.first, moves);
            board.merge(idx, 1, moves);
        }

        cur += frac.first;
        // r = (r - (frac.first / frac.second)) * frac.second / (frac.second - frac.first);
        r = (r * frac.second - frac.first) / (frac.second - frac.first);
    }
}

Board try_combo(Board board, proportion& r, int k_a, int k_b, int k_c, const Color& targ, const int turn_lim, vector<int>& moves) {
    assert(moves.empty());
    if (r[0] < r[1]) {
        swap(r[0], r[1]);
        swap(k_a, k_b);
    }
    if (r[1] < r[2]) {
        swap(r[1], r[2]);
        swap(k_b, k_c);
    }
    if (r[0] < r[1]) {
        swap(r[0], r[1]);
        swap(k_a, k_b);
    }

    board.reset(moves);
    board.pour_base(k_a, moves);

    half_combo(board, 0, r[1], k_b, (turn_lim - (moves.size() + 3) + 1) / 2, moves);
    half_combo(board, 1, r[2], k_c,  turn_lim - (moves.size() + 3), moves);

    board.toggle(0, moves);
    board.toggle(1, moves);
    board.give(targ, moves);

    if (moves.size() > turn_lim) board.cost = INF;
    return board;
}

Board solve(const Board& board, const int h, vector<int>& moves) {
    Board best = board;
    best.cost = INF;
    vector<int> best_moves;

    for (int k = 0; k < K; ++k) {
        const double cost = D + 10000 * target[h].error(own[k]);
        if (best.cost > board.cost + cost) {
            Board single = board;
            best_moves.clear();
            single.reset(best_moves);
            single.pour_base(k, best_moves);
            single.give(target[h], best_moves);
            best = single;
        }
    }

    for (int k_a = 0; k_a < K; ++k_a) {
        for (int k_b = k_a + 1; k_b < K; ++k_b) {
            for (int k_c = k_b + 1; k_c < K; ++k_c) {
                proportion prop = calculate_proportion(own[k_a], own[k_b], own[k_c], target[h]);
                if (prop[0] < 0 || prop[1] < 0 || prop[2] < 0) continue;

                vector<int> cur_moves; 
                const Board cur = try_combo(board, prop, k_a, k_b, k_c, target[h], (T - moves.size()) / (H - h), cur_moves);
                if (best.cost > cur.cost) {
                    best = cur;
                    best_moves = cur_moves;
                }
            }
        }
    }
    for (int x: best_moves) moves.push_back(x);
    return best;
}

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

    vector<int> moves;
    Board board;
    cout << board << '\n';
    for (int h = 0; h < H; ++h) {
        board = solve(board, h, moves);
    }
    board.cost -= H * D;
    for (int i = 0; i < moves.size(); ++i) {
        const int op = moves[i] & 63;
        const int a = (moves[i] >>  6) & 63;
        const int b = (moves[i] >> 12) & 63;
        const int c = (moves[i] >> 18) & 63;
        const int d = (moves[i] >> 24) & 63;
        if (op == POUR) {
            cout << POUR << ' ' << a << ' ' << b << ' ' << c << '\n';
        } else if (op == GIVE || op == DISCARD) {
            cout << op << ' ' << a << ' ' << b << '\n';
        } else if (op == TOGGLE) {
            cout << TOGGLE << ' ' << a << ' ' << b << ' ' << c << ' ' << d << '\n';
        }
    }
    debug(board.cost, moves.size());
}

