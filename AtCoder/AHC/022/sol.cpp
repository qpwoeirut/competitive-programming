#include <bits/stdc++.h>

#pragma GCC optimize("O3")

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

const int MAX_L = 50;
const int MAX_N = 100;
const int MIN_TEMP = 0;
const int MAX_TEMP = 1000;
const int MEASUREMENTS = 10000;

#ifndef USING_TESTER
// avoid using virtual functions because they cause performance hit
struct Judge {
    const int L, N, S;
    Judge(int L, int N, int S) : L(L), N(N), S(S) {}

    void set_temperature(const int temperature[MAX_L][MAX_L]) {
        for (int r = 0; r < L; ++r) {
            for (int c = 0; c < L; ++c) {
                cout << temperature[r][c] << (c + 1 == L ? "\n" : " ");
            }
        }
        cout.flush();
    }

    int measure(int i, int dr, int dc) {
        cout << i << " " << dr << " " << dc << '\n';
        cout.flush();

        int v;
        cin >> v;
        if (v == -1) {
            cerr << "something went wrong. i=" << i << " dr=" << dr << " dc=" << dc << endl;
            exit(0);
        }
        return v;
    }

    void answer(const int estimate[MAX_N]) {
        cout << "-1 -1 -1\n";
        for (int i = 0; i < N; ++i) {
            cout << estimate[i] << '\n';
        }
        cout.flush();
    }
};
#else
using Judge=Tester::Judge;
#endif

template <class T> inline T square(const T x) { return x * x; }
inline int ceil_log(const int x, const int b) {
    int b_pow = b;
    int lg = 1;
    while (x > b_pow) {
        b_pow *= b;
        ++lg;
    }
    return lg;
}
inline int isqrt(const int x) {
    for (int i = 0; i <= x; ++i) {
        if (i * i >= x) return i;
    }
    return 0;
}

const int EXTRA_M = 4;
const int MAX_CT = 9;
static_assert(EXTRA_M * MAX_N <= (1 << MAX_CT));

struct Counter {
    int ct[EXTRA_M * MAX_N * MAX_TEMP + 1];
    int total;
    
    int n_clear;
    int to_clear[MAX_TEMP * MAX_CT * MAX_CT * 8];

    int n_dupe;
    int duplicates[MAX_TEMP * MAX_CT * MAX_CT * 8];

    Counter() : total(0), n_clear(0), n_dupe(0) {}

    void inc(int x) {
        if (++ct[x] == 1) {
            ++total;
            to_clear[n_clear++] = x;
        } else if (ct[x] == 2) {
            duplicates[n_dupe++] = x;
        }
    }
    void dec(int x) {
        if (--ct[x] == 0) {
            --total;
        }
        while (n_dupe > 0 && ct[duplicates[n_dupe - 1]] < 2) --n_dupe;
    }
    int get_dupe() {
        return n_dupe > 0 ? duplicates[n_dupe - 1] : -1;
    }
    void clear() {
        total = 0;
        while (n_clear > 0) {
            ct[to_clear[--n_clear]] = 0;
        }
        n_dupe = 0;
    }
} counter;

const int TEMP_ITERS = MAX_N;
const chrono::milliseconds PATTERN_TIME = 3750ms;

const int TEMP_RANGE[31] = {
    MAX_TEMP,
    100,
    200,
    300,
    300,
    300,
    300,
    500,
    600,
    600,
    800,
    800,
    800,
    800,
    800,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
};
const int S_MARGIN[31] = {
    3,
    6,
    5,
    4,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
};

mt19937 rng(8);

const int chr[8] = { 0,  1,  0, -1, -1,  1,  1, -1 };
const int chc[8] = { 1,  0, -1,  0,  1,  1, -1, -1 };

template <const int P_SIZE>
struct Solver {
    static const int MAX_P = P_SIZE + 1 + P_SIZE;

    const chrono::time_point<chrono::high_resolution_clock> pattern_end;

    const int L, N, S;
    const array<pii, MAX_N> landing_pos;
    Judge judge;

    const int temp_range;
    const int s_margin;

    const int options;
    const int jump, offset;  // opts[i] = offset + i * jump;
    const int n_pattern;

    int G[MAX_L][MAX_L];
    pii best_pattern[MAX_CT];
    int estimate[MAX_N];

    int opt_pow[MAX_CT+1];

    Solver(const int _L, const int _N, const int _S, const array<pii, MAX_N>& landing_pos) : 
        pattern_end(chrono::high_resolution_clock::now() + PATTERN_TIME),
        L(_L), N(_N), S(_S + 1), landing_pos(landing_pos), judge(_L, _N, _S),
        temp_range(TEMP_RANGE[isqrt(_S)]), s_margin(S_MARGIN[isqrt(_S)]),
        options(max(2, temp_range / (s_margin * S))), jump(min(s_margin * S, temp_range / (options - 1))), offset((temp_range - (options - 1) * jump) / 2), n_pattern(ceil_log(EXTRA_M * N, options)) {
            opt_pow[0] = 1;
            for (int i = 1; i <= n_pattern; ++i) {
                opt_pow[i] = opt_pow[i - 1] * options;
            }
#ifdef USING_TESTER
            judge.set_landing_pos(landing_pos);
#endif
    }

#ifdef USING_TESTER
    Solver(const int _L, const int _N, const int _S, const array<pii, MAX_N>& landing_pos, const int _temp_range, const int _s_margin) : 
        pattern_end(chrono::high_resolution_clock::now() + PATTERN_TIME),
        L(_L), N(_N), S(_S + 1), landing_pos(landing_pos), judge(_L, _N, _S),
        temp_range(_temp_range), s_margin(_s_margin),
        options(max(2, temp_range / (s_margin * S))), jump(min(s_margin * S, temp_range / (options - 1))), offset((temp_range - (options - 1) * jump) / 2), n_pattern(ceil_log(EXTRA_M * N, options)) {
            opt_pow[0] = 1;
            for (int i = 1; i <= n_pattern; ++i) {
                opt_pow[i] = opt_pow[i - 1] * options;
            }
            judge.set_landing_pos(landing_pos);
    }
#endif

    void solve() {
        create_temperature();
        judge.set_temperature(G);
        predict();
        judge.answer(estimate);

        //double time_taken = (chrono::high_resolution_clock::now() - pattern_end + PATTERN_TIME).count() / 1e6;
        //debug(L, N, S, time_taken);
    }

    inline void copy_grid(const int from[MAX_L][MAX_L], int to[MAX_L][MAX_L]) {
        for (int r=0; r<L; ++r) {
            for (int c=0; c<L; ++c) {
                to[r][c] = from[r][c];
            }
        }
    }
    inline int shift_coord(const int start, const int shift) {
        return (start + shift < 0) ? start + shift + L : ((start + shift < L) ? start + shift : start + shift - L);
    }

    pii pattern[MAX_CT];
    bitset<MAX_P> in[MAX_P];
    void mutate_pattern(int& idx, int& change) {
        do {
            idx = rng() % n_pattern;
            change = rng() % 8;
        } while (in[(pattern[idx].row + MAX_P + chr[change]) % MAX_P][(pattern[idx].col + MAX_P + chc[change]) % MAX_P]);

        in[pattern[idx].row][pattern[idx].col] = false;
        pattern[idx].row = (pattern[idx].row + MAX_P + chr[change]) % MAX_P;
        pattern[idx].col = (pattern[idx].col + MAX_P + chc[change]) % MAX_P;
        in[pattern[idx].row][pattern[idx].col] = true;
    }

    int G_pattern[MAX_L][MAX_L];
    bitset<MAX_L> picked[MAX_L];

    int n_cell = 0;
    int cell_idx[MAX_L][MAX_L];
    pii cells[MAX_L * MAX_L];
    vector<int> uses[MAX_L * MAX_L];  // pos idx << 8 | pattern idx
    void apply_pattern() {
        for (int r = 0; r < L; ++r) picked[r].reset();
        n_cell = 0;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<n_pattern; ++j) {
                const int r = shift_coord(landing_pos[i].row, pattern[j].row - P_SIZE);
                const int c = shift_coord(landing_pos[i].col, pattern[j].col - P_SIZE);
                if (!picked[r][c]) {
                    picked[r][c] = true;
                    cells[n_cell++] = pii(r, c);
                }
            }
        }
    }

    int G_val[MAX_N];
    int cell_val[MAX_L * MAX_L];
    int to_change[MAX_CT];  // cell idx
    void remove_duplicate(const int dupe_idx) {
        for (int i = 0; i < n_pattern; ++i) {
            to_change[i] = cell_idx[shift_coord(landing_pos[dupe_idx].row, pattern[i].row - P_SIZE)][shift_coord(landing_pos[dupe_idx].col, pattern[i].col - P_SIZE)];
        }
        sort(to_change, to_change + n_pattern, [&](const int ia, const int ib) {
            return uses[ia].size() < uses[ib].size() || (uses[ia].size() == uses[ib].size() && ia < ib);
        });

        for (int change = 1; change < options; ++change) {
            for (int i = 0; i < n_pattern; ++i) {
                const int old_val = cell_val[to_change[i]];
                const int original_total = counter.total;

                const int bigger_val = old_val + change;
                if (offset + bigger_val * jump <= MAX_TEMP) {
                    for (int use: uses[to_change[i]]) {
                        counter.dec(G_val[use >> 8]);
                        G_val[use >> 8] += opt_pow[use & 0xff] * (bigger_val - old_val);
                        counter.inc(G_val[use >> 8]);
                    }
                    if (counter.total > original_total) {
                        cell_val[to_change[i]] = bigger_val;
                        return;
                    }
                    for (int use: uses[to_change[i]]) {
                        counter.dec(G_val[use >> 8]);
                        G_val[use >> 8] -= opt_pow[use & 0xff] * (bigger_val - old_val);
                        counter.inc(G_val[use >> 8]);
                    }
                }

                const int smaller_val = old_val - change;
                if (0 <= offset + smaller_val * jump) {
                    for (int use: uses[to_change[i]]) {
                        counter.dec(G_val[use >> 8]);
                        G_val[use >> 8] += opt_pow[use & 0xff] * (smaller_val - old_val);
                        counter.inc(G_val[use >> 8]);
                    }
                    if (counter.total > original_total) {
                        cell_val[to_change[i]] = smaller_val;
                        return;
                    }
                    for (int use: uses[to_change[i]]) {
                        counter.dec(G_val[use >> 8]);
                        G_val[use >> 8] -= opt_pow[use & 0xff] * (smaller_val - old_val);
                        counter.inc(G_val[use >> 8]);
                    }
                }
            }
        }
    }

    void assign_temps() {
        for (int r=0; r<L; ++r) {
            for (int c=0; c<L; ++c) {
                cell_idx[r][c] = -1;
            }
        }

        const auto comp_edge = [&](const pii& a, const pii& b) {
            const int edge_a = min(min(a.row, L - a.row - 1), min(a.col, L - a.col - 1));
            const int edge_b = min(min(b.row, L - b.row - 1), min(b.col, L - b.col - 1));
            return edge_a < edge_b || (edge_a == edge_b && a < b);
        };

        sort(cells, cells + n_cell, comp_edge);
        fill(uses, uses+n_cell, vector<int>());
        for (int i=0; i<N; ++i) {
            for (int j=0; j<n_pattern; ++j) {
                const int r = shift_coord(landing_pos[i].row, pattern[j].row - P_SIZE);
                const int c = shift_coord(landing_pos[i].col, pattern[j].col - P_SIZE);
                if (cell_idx[r][c] == -1) {
                    cell_idx[r][c] = lower_bound(cells, cells + n_cell, pii(r, c), comp_edge) - cells;
                }
                uses[cell_idx[r][c]].push_back(i << 8 | j);
            }
        }

        fill(G_val, G_val + N, 0);
        for (int i = 0; i < n_cell; ++i) {
            cell_val[i] = i * options / n_cell;
            for (int use: uses[i]) {
                G_val[use >> 8] += opt_pow[use & 0xff] * cell_val[i];
            }
        }

        for (int it = 0; it < TEMP_ITERS; ++it) {
            counter.clear();
            for (int i = 0; i < N; ++i) counter.inc(G_val[i]);
            const int dupe_val = counter.get_dupe();
            if (dupe_val == -1) break;

            const int dupe_idx = find(G_val, G_val + N, dupe_val) - G_val;
            remove_duplicate(dupe_idx);
        }

        for (int i = 0; i < n_cell; ++i) {
            G_pattern[cells[i].row][cells[i].col] = offset + cell_val[i] * jump;
        }
    }

    void fill_grid() {
        for (int i=0; i<100; ++i) {
            bool changed = false;
            for (int r=0; r<L; ++r) {
                for (int c=0; c<L; ++c) {
                    if (!picked[r][c]) {
                        const int new_val = (G_pattern[shift_coord(r, -1)][c] + G_pattern[r][shift_coord(c, -1)] + G_pattern[shift_coord(r, 1)][c] + G_pattern[r][shift_coord(c, 1)] + 2) / 4;
                        if (G_pattern[r][c] != new_val) {
                            G_pattern[r][c] = new_val;
                            changed = true;
                        }
                    }
                }
            }
            if (!changed) {
                break;
            }
        }
    }

    inline ll cost(const int grid[MAX_L][MAX_L]) {
        ll ret = (N - counter.total) * 1'000'000'000'000'000LL;  // have as few duplicates as possible
        for (int r=0; r<L; ++r) {
            for (int c=0; c<L; ++c) {
                ret += square(grid[r][c] - grid[shift_coord(r, 1)][c]) + square(grid[r][c] - grid[r][shift_coord(c, 1)]);
            }
        }
        for (int i=0; i<n_pattern; ++i) {
            ret += (MEASUREMENTS / n_pattern) * 100 * (10 + abs(pattern[i].row - P_SIZE) + abs(pattern[i].col - P_SIZE));
        }
        return ret;
    }
    bool shift_pattern(pii pat[MAX_CT]) {
        int com_r = 0;
        int com_c = 0;
        for (int i = 0; i < n_pattern; ++i) {
            com_r += pat[i].row;
            com_c += pat[i].col;
        }
        com_r = (com_r + (n_pattern / 2)) / n_pattern;
        com_c = (com_c + (n_pattern / 2)) / n_pattern;
        int shift_r = P_SIZE - com_r;
        int shift_c = P_SIZE - com_c;
        for (int i = 0; i < n_pattern; ++i) {
            shift_r = min(shift_r, MAX_P - pat[i].row - 1);
            shift_r = max(shift_r, -pat[i].row);
            shift_c = min(shift_c, MAX_P - pat[i].col - 1);
            shift_c = max(shift_c, -pat[i].col);
        }

        if (shift_r != 0 || shift_c != 0) {
            for (int r=0; r<MAX_P; ++r) {
                in[r].reset();
            }
            for (int i = 0; i < n_pattern; ++i) {
                pat[i].row += shift_r;
                pat[i].col += shift_c;
                in[pat[i].row][pat[i].col] = true;
            }
            return true;
        }
        return false;
    }
    void create_temperature() {
        const int iters = n_pattern * 150;
        ll best_cost = 1e18;
        while (chrono::high_resolution_clock::now() < pattern_end) {
            for (int r=0; r<MAX_P; ++r) {
                in[r].reset();
            }

            // generate random pattern
            for (int i=0; i<n_pattern; ++i) {
                int r, c;
                do {
                    r = rng() % MAX_P;
                    c = rng() % MAX_P;
                } while (in[r][c]);
                in[r][c] = true;
                pattern[i] = pii(r, c);
            }
            //debug1(pattern, n_pattern);

            // mutate pattern
            ll old_cost = 1e18;
            for (int it=0; it<iters && chrono::high_resolution_clock::now() < pattern_end; ++it) {
                int idx, change;
                mutate_pattern(idx, change);
                apply_pattern();
                assign_temps();
                fill_grid();
                //debug2(G_pattern, L, L);

                const ll cur_cost = cost(G_pattern);
                if (best_cost > cur_cost) {
                    best_cost = cur_cost;
                    copy_grid(G_pattern, G);
                    copy(pattern, pattern+n_pattern, best_pattern);
                }

                if (old_cost < cur_cost) {
                    in[pattern[idx].row][pattern[idx].col] = false;
                    pattern[idx].row = (pattern[idx].row + MAX_P - chr[change]) % MAX_P;
                    pattern[idx].col = (pattern[idx].col + MAX_P - chc[change]) % MAX_P;
                    in[pattern[idx].row][pattern[idx].col] = true;
                } else {
                    old_cost = cur_cost;
                }

                if (shift_pattern(pattern)) {
                    apply_pattern();
                    assign_temps();
                    fill_grid();

                    const ll cur_cost = cost(G_pattern);
                    if (best_cost > cur_cost) {
                        best_cost = cur_cost;
                        copy_grid(G_pattern, G);
                        copy(pattern, pattern+n_pattern, best_pattern);
                    }
                    old_cost = min(old_cost, cur_cost);
                }
                //debug(cur_cost, old_cost, best_cost);
            }
            //debug(old_cost, best_cost);
        }
        //debug1(best_pattern, n_pattern);
        //debug(best_cost);
    }

    void predict() {
        int remaining = MEASUREMENTS;
        double sum[n_pattern];
        for (int i_in = 0; i_in < N; ++i_in) {
            estimate[i_in] = -1;
            fill(sum, sum + n_pattern, 0);
            const int trials = min(remaining / (n_pattern * (N - i_in)), 100);
            //debug(i_in, trials);
            for (int t = 1; t <= trials; ++t) {
                for (int j = 0; j < n_pattern; ++j) {
                    sum[j] += judge.measure(i_in, best_pattern[j].row - P_SIZE, best_pattern[j].col - P_SIZE);
                    --remaining;
                }

                const int diff_threshold = S * S * (7 - t > 1 ? square(7 - t) / 2 : 1);
                double diff1 = 1e12, diff2 = 1e12;
                int idx1 = -1;
                for (int i_out = 0; i_out < N; ++i_out) {
                    const pii& pos = landing_pos[i_out];
                    double diff = 0;
                    for (int j = 0; j < n_pattern; ++j) {
                        diff += square((sum[j] / t) - G[shift_coord(pos.row, best_pattern[j].row - P_SIZE)][shift_coord(pos.col, best_pattern[j].col - P_SIZE)]);
                    }
                    //debug(i_in, i_out, diff);
                    if (diff1 > diff) {
                        diff2 = diff1;
                        diff1 = diff;
                        idx1 = i_out;
                    } else if (diff2 > diff) {
                        diff2 = diff;
                    }
                }

                //if (diff2 - diff1 > diff_threshold || t == trials) debug(i_in, t, idx1, diff1, diff2, diff2 - diff1, diff_threshold);
                if (diff2 - diff1 > diff_threshold) {
                    estimate[i_in] = idx1;
                    break;
                }
            }
            if (estimate[i_in] == -1) {
                double min_diff = 1e12;
                for (int i_out = 0; i_out < N; ++i_out) {
                    const pii& pos = landing_pos[i_out];
                    double diff = 0;
                    for (int j = 0; j < n_pattern; ++j) {
                        diff += square((sum[j] / trials) - G[shift_coord(pos.row, best_pattern[j].row - P_SIZE)][shift_coord(pos.col, best_pattern[j].col - P_SIZE)]);
                    }
                    if (min_diff > diff) {
                        min_diff = diff;
                        estimate[i_in] = i_out;
                    }
                    //debug(i_in, i_out, diff, min_diff);
                }
            }
        }
        //debug1(estimate, N);
    }
};

#ifndef USING_TESTER
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int L, N, S;
    cin >> L >> N >> S;
    array<pii, MAX_N> landing_pos;
    for (int i = 0; i < N; i++) {
        cin >> landing_pos[i].row >> landing_pos[i].col;
    }

    if (L < 11) {
        Solver<4> solver(L, N, S, landing_pos);
        solver.solve();
    } else if (L < 13) {
        Solver<5> solver(L, N, S, landing_pos);
        solver.solve();
    } else if (L < 15) {
        Solver<6> solver(L, N, S, landing_pos);
        solver.solve();
    } else if (L < 17) {
        Solver<7> solver(L, N, S, landing_pos);
        solver.solve();
    } else {
        Solver<8> solver(L, N, S, landing_pos);
        solver.solve();
    }
}
#endif

/*
S = 1: 
*/
