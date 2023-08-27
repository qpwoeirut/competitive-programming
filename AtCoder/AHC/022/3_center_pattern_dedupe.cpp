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
const int MAX_TEMP = 1000;

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

const int EXTRA_M = 4;
const int MAX_CT = 9;
static_assert(EXTRA_M * MAX_N <= (1 << MAX_CT));
const int S_MARGIN = 5;

struct Counter {
    int ct[EXTRA_M * MAX_N * (MAX_TEMP / S_MARGIN) + 1];
    int total;
    
    int n_clear;
    int to_clear[(MAX_TEMP / S_MARGIN) * MAX_CT * MAX_CT * 8];

    int n_dupe;
    int duplicates[(MAX_TEMP / S_MARGIN) * MAX_CT * MAX_CT * 8];

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
        options(max(2, MAX_TEMP / (S_MARGIN * S))), jump(min(S_MARGIN * S, MAX_TEMP / (options - 1))), offset((MAX_TEMP - (options - 1) * jump) / 2), n_pattern(ceil_log(EXTRA_M * N, options)) {
            opt_pow[0] = 1;
            for (int i = 1; i <= n_pattern; ++i) {
                opt_pow[i] = opt_pow[i - 1] * options;
            }
#ifdef USING_TESTER
            judge.set_landing_pos(landing_pos);
#endif
    }

    void solve() {
        create_temperature();
        judge.set_temperature(G);
        predict();
        judge.answer(estimate);

        double time_taken = (chrono::high_resolution_clock::now() - pattern_end + PATTERN_TIME).count() / 1e6;
        debug(L, N, S, time_taken);
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
        ll ret = 0;
        for (int r=0; r<L; ++r) {
            for (int c=0; c<L; ++c) {
                ret += square(grid[r][c] - grid[shift_coord(r, 1)][c]) + square(grid[r][c] - grid[r][shift_coord(c, 1)]);
            }
        }
        for (int i=0; i<n_pattern; ++i) {
            ret += (10000 / n_pattern) * 100 * (10 + abs(pattern[i].row - P_SIZE) + abs(pattern[i].col - P_SIZE));
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
        const int iters = n_pattern * 100;
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
            ll best_cost = 1e18;
            ll old_cost = 1e18;
            for (int it=0; it<iters && chrono::high_resolution_clock::now() < pattern_end; ++it) {
                int idx, change;
                mutate_pattern(idx, change);
                apply_pattern();
                assign_temps();
                fill_grid();
                //debug2(G_pattern, L, L);

                const ll cur_cost = cost(G_pattern);
                if (best_cost > cur_cost && counter.total == N) {
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
                    if (best_cost > cur_cost && counter.total == N) {
                        best_cost = cur_cost;
                        copy_grid(G_pattern, G);
                        copy(pattern, pattern+n_pattern, best_pattern);
                    }
                }
            }
        }
        //debug1(best_pattern, n_pattern);
    }

    void predict() {
        int remaining = 10000;
        double sum[n_pattern];
        for (int i_in = 0; i_in < N; ++i_in) {
            estimate[i_in] = -1;
            fill(sum, sum + n_pattern, 0);
            const int trials = min(remaining / (n_pattern * (N - i_in)), 100);
            const double diff_threshold = (double)(3 * n_pattern * S * S) / trials;
            //debug(i_in, trials);
            for (int t = 1; t <= trials; ++t) {
                for (int j = 0; j < n_pattern; ++j) {
                    sum[j] += judge.measure(i_in, best_pattern[j].row - P_SIZE, best_pattern[j].col - P_SIZE);
                    --remaining;
                }

                if (t < 4 || t*t <= S) continue;

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

                if (diff2 - diff1 > diff_threshold) {
                    //debug(i_in, t, idx1, diff1, diff2, diff2 - diff1, diff_threshold);
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
With PATTERN_TIME = 1000ms
TESTS = 20. L = -1, N = -1, S = 1.
scores      mean, stddev, stderr, min, q1, med, q3, max: [17152810.900000 2384092.107153 533099.201622 14259595.000000 15264915.000000 16725127.000000 19326705.000000 22937222.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5110449.700000 700025.667729 156530.497904 3638126.000000 4556634.000000 5249028.000000 5794126.000000 6123222.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [726160.000000 151471.523396 33870.062297 504000.000000 621600.000000 730800.000000 798000.000000 1088000.000000]
TESTS = 20. L = -1, N = -1, S = 4.
scores      mean, stddev, stderr, min, q1, med, q3, max: [18092008.400000 2186475.305223 488910.741360 14198580.000000 16298399.000000 18418975.000000 19853608.000000 22272440.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [4841518.400000 634604.727070 141901.930857 3877454.000000 4407668.000000 4650936.000000 5509624.000000 6102958.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [669600.000000 104159.109059 23290.684833 512400.000000 571200.000000 663600.000000 781200.000000 840000.000000]
TESTS = 20. L = -1, N = -1, S = 9.
scores      mean, stddev, stderr, min, q1, med, q3, max: [17094684.550000 2827955.584805 632350.092497 13397388.000000 14929777.000000 17371957.000000 18992949.000000 24919610.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5170433.500000 845134.602310 188977.842090 3366904.000000 4558602.000000 5182564.000000 6083330.000000 6750942.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [730580.000000 165653.299394 37041.203814 504000.000000 613200.000000 756000.000000 800000.000000 1224000.000000]
TESTS = 20. L = -1, N = -1, S = 16.
scores      mean, stddev, stderr, min, q1, med, q3, max: [14917395.000000 1392701.225483 311417.461253 13217534.000000 13930169.000000 14544330.000000 15743064.000000 19045798.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5122589.200000 431891.550052 96573.886482 4126502.000000 4982580.000000 5198664.000000 5541296.000000 5904852.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [1534325.000000 351924.149321 78692.632080 1024000.000000 1280000.000000 1534500.000000 1880000.000000 2115000.000000]
TESTS = 20. L = -1, N = -1, S = 25.
scores      mean, stddev, stderr, min, q1, med, q3, max: [11965903.950000 1786727.400426 399524.392461 9670238.000000 10589418.000000 11279097.000000 14165382.000000 14887967.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [6173630.600000 555066.561184 124116.656284 5149632.000000 5919232.000000 6239036.000000 6511582.000000 7386040.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2266710.000000 786901.710444 175956.571616 1264800.000000 1555200.000000 2346000.000000 2998800.000000 3654000.000000]
TESTS = 20. L = -1, N = -1, S = 36.
scores      mean, stddev, stderr, min, q1, med, q3, max: [9295944.000000 1276438.889610 285420.412629 6685124.000000 8410489.000000 9494733.000000 10298874.000000 11382778.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [7499061.600000 1452747.763794 324844.275400 5612902.000000 6451312.000000 7098308.000000 8409350.000000 11895486.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [3378235.000000 546334.752029 122164.164401 2665600.000000 2963100.000000 3219300.000000 3834600.000000 4558400.000000]
TESTS = 20. L = -1, N = -1, S = 49.
scores      mean, stddev, stderr, min, q1, med, q3, max: [6066376.850000 1490073.150861 333190.485677 3679806.000000 5046089.000000 5912436.000000 7301196.000000 9798794.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [12382641.600000 3154708.588705 705414.285355 7333338.000000 10361450.000000 11908070.000000 14339426.000000 19955352.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [4998960.000000 1289201.156686 288274.142302 2772000.000000 4118400.000000 5376000.000000 6042400.000000 7120000.000000]
TESTS = 20. L = -1, N = -1, S = 64.
scores      mean, stddev, stderr, min, q1, med, q3, max: [4732945.150000 906187.755662 202629.742204 3265344.000000 4194756.000000 4701356.000000 5255451.000000 6689411.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [15329214.400000 3466152.456781 775055.251374 8450000.000000 13420624.000000 15575090.000000 17079294.000000 22656852.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [6471315.000000 1105008.047154 247087.310912 4687200.000000 5929200.000000 6399000.000000 7200000.000000 9166500.000000]
TESTS = 20. L = -1, N = -1, S = 81.
scores      mean, stddev, stderr, min, q1, med, q3, max: [2528818.550000 995372.226139 222571.996056 1.000000 2420037.000000 2600984.000000 3223124.000000 3898584.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [5.550000 16.865571 3.771256 0.000000 0.000000 0.000000 0.000000 64.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [27109215.400000 10623689.003212 2375529.078300 13111800.000000 20478540.000000 25790022.000000 28598160.000000 56317982.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [13939840.000000 4283538.379704 957828.300125 9272000.000000 12062000.000000 12771000.000000 14440000.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 100.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1942836.000000 681746.700373 152443.196547 9.000000 1538352.000000 1933638.000000 2213199.000000 3307057.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [2.550000 11.115192 2.485433 0.000000 0.000000 0.000000 0.000000 51.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [41376321.600000 19619235.794062 4386994.490212 19381900.000000 31304334.000000 39754716.000000 49395538.000000 113685254.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [14849065.000000 3331909.628618 745037.642448 8525000.000000 13459600.000000 15155800.000000 16163400.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 121.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1303412.500000 627716.137280 140361.595353 1.000000 1088116.000000 1510790.000000 1812817.000000 2025462.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [10.150000 24.866192 5.560250 0.000000 0.000000 0.000000 0.000000 83.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [65019217.600000 31920222.433096 7137578.721732 36118518.000000 43486690.000000 55148574.000000 75521420.000000 140593890.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17172730.000000 4291875.082537 959692.443549 11869200.000000 13708800.000000 17404800.000000 18878400.000000 26000000.000000]
TESTS = 20. L = -1, N = -1, S = 144.
scores      mean, stddev, stderr, min, q1, med, q3, max: [848869.350000 654514.864191 146353.972862 1.000000 5.000000 878496.000000 1559570.000000 1829673.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [19.400000 30.092192 6.728819 0.000000 0.000000 0.000000 56.000000 80.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [94529701.800000 43518179.371265 9730960.733118 39947500.000000 62006234.000000 89001670.000000 124798846.000000 202422298.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [19148090.000000 4943756.239531 1105457.501578 10316800.000000 16553900.000000 18220400.000000 25997400.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 169.
scores      mean, stddev, stderr, min, q1, med, q3, max: [769613.250000 285172.429877 63766.493851 1.000000 626101.000000 735491.000000 884505.000000 1390439.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [4.250000 18.525321 4.142388 0.000000 0.000000 0.000000 0.000000 85.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [118007314.500000 33425143.624891 7474089.330295 58883752.000000 103042190.000000 119300552.000000 146413950.000000 192990572.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18099880.000000 2691647.734864 601870.730664 12936000.000000 16905000.000000 18138400.000000 19664700.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 196.
scores      mean, stddev, stderr, min, q1, med, q3, max: [630892.900000 323776.191092 72398.557278 1.000000 484885.000000 692304.000000 886130.000000 1231138.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [11.400000 27.364941 6.118987 0.000000 0.000000 0.000000 0.000000 88.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [146439987.400000 58210181.647888 13016192.314729 69047684.000000 111090764.000000 136616162.000000 191409530.000000 318637278.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17316825.000000 4084998.361918 913433.402522 12078000.000000 16080000.000000 16983000.000000 17887100.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 225.
scores      mean, stddev, stderr, min, q1, med, q3, max: [560030.750000 279773.930442 62559.352680 1.000000 461334.000000 540385.000000 719764.000000 1357696.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [7.550000 22.743076 5.085506 0.000000 0.000000 0.000000 0.000000 82.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [170270231.200000 58186326.106578 13010858.053528 60000000.000000 128929184.000000 178728962.000000 211691330.000000 322175730.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18787485.000000 3009084.631125 672851.778525 13094400.000000 17553800.000000 18887000.000000 19553600.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 256.
scores      mean, stddev, stderr, min, q1, med, q3, max: [513887.700000 361014.916370 80725.389389 1.000000 383596.000000 618224.000000 696775.000000 1323752.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [17.700000 31.088744 6.951654 0.000000 0.000000 0.000000 57.000000 83.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [198602518.200000 107110759.684452 23950693.977608 60000000.000000 131885056.000000 158294258.000000 275386074.000000 420238818.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [19950555.000000 3758960.092163 840529.029079 15442900.000000 17442700.000000 19220300.000000 25997400.000000 26000000.000000]
TESTS = 20. L = -1, N = -1, S = 289.
scores      mean, stddev, stderr, min, q1, med, q3, max: [610689.050000 206205.035628 46108.847697 2.000000 516199.000000 628805.000000 741416.000000 1103095.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [2.800000 12.204917 2.729102 0.000000 0.000000 0.000000 0.000000 56.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [150451944.900000 38459487.033538 8599802.738676 76000000.000000 126988922.000000 152054074.000000 183850700.000000 239339402.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17975010.000000 2362882.969573 528356.694284 14061600.000000 17109400.000000 17776000.000000 19331400.000000 26000000.000000]
TESTS = 20. L = -1, N = -1, S = 324.
scores      mean, stddev, stderr, min, q1, med, q3, max: [683045.750000 392644.165942 87797.904602 1.000000 486424.000000 594498.000000 944502.000000 1480342.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [8.200000 24.608129 5.502545 0.000000 0.000000 0.000000 0.000000 84.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [149980444.700000 63598951.403981 14221157.863701 54000000.000000 105496058.000000 152164320.000000 193913262.000000 276948766.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18271690.000000 3258603.735789 728645.946496 13109800.000000 16442800.000000 17998200.000000 19109200.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 361.
scores      mean, stddev, stderr, min, q1, med, q3, max: [551595.850000 323174.282080 72263.966331 1.000000 504956.000000 584334.000000 805993.000000 1145568.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [14.900000 30.207449 6.754591 0.000000 0.000000 0.000000 0.000000 91.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [168157159.400000 72823847.257998 16283907.285195 72750000.000000 109909456.000000 153788836.000000 187652358.000000 344579140.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [19564840.000000 3525610.236172 788350.415025 14443000.000000 17776000.000000 18553700.000000 20553500.000000 26000000.000000]
TESTS = 20. L = -1, N = -1, S = 400.
scores      mean, stddev, stderr, min, q1, med, q3, max: [652107.250000 271255.525529 60654.579436 1.000000 445605.000000 661548.000000 919414.000000 1130814.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [3.750000 16.345871 3.655048 0.000000 0.000000 0.000000 0.000000 75.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [150436217.800000 56208000.615106 12568491.025473 74000000.000000 100606216.000000 157116898.000000 216335906.000000 244098034.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18221175.000000 2308998.674507 516307.799615 14331900.000000 16665000.000000 18442600.000000 18998100.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 441.
scores      mean, stddev, stderr, min, q1, med, q3, max: [435357.900000 336260.393146 75190.109721 1.000000 1.000000 489067.000000 696286.000000 1262474.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [23.600000 36.669333 8.199512 0.000000 0.000000 0.000000 66.000000 97.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [209616883.500000 97252758.893276 21746377.988476 64000000.000000 131500000.000000 191822232.000000 281270912.000000 456928846.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [20197375.000000 3982725.187591 890564.425515 15109600.000000 17442700.000000 18775900.000000 25997400.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 484.
scores      mean, stddev, stderr, min, q1, med, q3, max: [522913.250000 316924.212808 70866.408355 1.000000 442014.000000 594591.000000 729345.000000 1125162.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [16.650000 33.786499 7.554891 0.000000 0.000000 0.000000 1.000000 96.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [196483152.200000 108369001.331089 24232045.363008 72000000.000000 129922150.000000 161127486.000000 250877450.000000 402837462.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [19669180.000000 3285390.858878 734635.729311 15998400.000000 17776000.000000 18331500.000000 20331300.000000 26000000.000000]
TESTS = 20. L = -1, N = -1, S = 529.
scores      mean, stddev, stderr, min, q1, med, q3, max: [528986.550000 284576.103997 63633.151331 1.000000 391541.000000 646621.000000 769585.000000 927374.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [13.200000 30.907281 6.911078 0.000000 0.000000 0.000000 1.000000 92.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [164609262.300000 65427557.588906 14630046.637058 88733334.000000 118590156.000000 138133144.000000 213169592.000000 366206468.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18971370.000000 3132401.278907 700426.219244 15442900.000000 16887200.000000 18109300.000000 19220300.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 576.
scores      mean, stddev, stderr, min, q1, med, q3, max: [551968.250000 291937.303053 65279.165479 1.000000 429571.000000 604968.000000 818971.000000 924944.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [13.400000 31.134226 6.961824 0.000000 0.000000 0.000000 1.000000 93.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [163321822.900000 72687399.375687 16253396.611171 78000000.000000 107433334.000000 149088666.000000 214359070.000000 344786154.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18716510.000000 3251580.847203 727075.580868 14875000.000000 16887200.000000 17887100.000000 18998100.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 625.
scores      mean, stddev, stderr, min, q1, med, q3, max: [484870.100000 261849.495588 58551.327201 1.000000 360776.000000 519061.000000 693467.000000 964026.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [8.300000 23.037144 5.151262 0.000000 0.000000 0.000000 3.000000 92.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [178132791.300000 71467114.605503 15980532.641367 86966668.000000 142379008.000000 161593124.000000 204535034.000000 371246064.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18747745.000000 2827163.201422 632172.910187 14998500.000000 17109400.000000 18250000.000000 19442500.000000 26000000.000000]
TESTS = 20. L = -1, N = -1, S = 676.
scores      mean, stddev, stderr, min, q1, med, q3, max: [453450.300000 307510.869777 68761.520864 1.000000 301971.000000 354414.000000 713429.000000 1228019.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [9.050000 22.200169 4.964109 0.000000 0.000000 2.000000 3.000000 76.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [170041913.500000 80601845.738512 18023120.618326 68000000.000000 121193256.000000 157572214.000000 172708128.000000 406908440.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18891445.000000 2854722.267135 638335.304620 13332000.000000 17998200.000000 18775900.000000 19553600.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 729.
scores      mean, stddev, stderr, min, q1, med, q3, max: [429136.200000 259056.131517 57926.712006 1.000000 257908.000000 424063.000000 686210.000000 1030209.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [8.700000 19.434763 4.345745 0.000000 1.000000 3.000000 4.000000 73.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [153944586.900000 85854178.944967 19197578.027338 64000000.000000 105500000.000000 131473506.000000 179089520.000000 458947438.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18224795.000000 3108596.786731 695103.372977 13554200.000000 16553900.000000 17887100.000000 19664700.000000 26000000.000000]
TESTS = 20. L = -1, N = -1, S = 784.
scores      mean, stddev, stderr, min, q1, med, q3, max: [245625.050000 198512.293491 44388.698262 1.000000 87569.000000 204293.000000 452931.000000 589457.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [14.650000 25.542660 5.711512 1.000000 2.000000 4.000000 10.000000 89.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [186917779.100000 55865848.296493 12491983.441165 104000000.000000 150854654.000000 179002296.000000 220428016.000000 305092234.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [19254635.000000 3047479.686606 681437.173930 16109500.000000 17331600.000000 18500000.000000 19553600.000000 26000000.000000]
TESTS = 20. L = -1, N = -1, S = 841.
scores      mean, stddev, stderr, min, q1, med, q3, max: [315111.000000 312483.535587 69873.442742 1.000000 49972.000000 154789.000000 615089.000000 1065546.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [9.450000 15.573937 3.482438 0.000000 1.000000 6.000000 10.000000 74.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [150986521.100000 55149357.957609 12331771.330868 64000000.000000 120749806.000000 138071436.000000 190820164.000000 309229216.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18395155.000000 2309529.282446 516426.447158 13998600.000000 17776000.000000 18375000.000000 18775900.000000 25997400.000000]
TESTS = 20. L = -1, N = -1, S = 900.
scores      mean, stddev, stderr, min, q1, med, q3, max: [261478.850000 277826.041357 62123.791439 1.000000 36759.000000 211092.000000 398896.000000 1070018.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [19.450000 31.292931 6.997312 1.000000 3.000000 6.000000 15.000000 98.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [165455374.800000 90654514.060935 20270965.590746 59000000.000000 116144676.000000 137688236.000000 214920164.000000 368194700.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18860955.000000 3208536.876128 717450.656334 15665100.000000 16776100.000000 18109300.000000 19442500.000000 25997400.000000]


With S_MARGIN=5, EXTRA_M=2
TESTS = 500. L = -1, N = -1, S = -1.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1579857.126000 3067409.523618 137178.724193 1.000000 552.000000 16704.000000 1748556.000000 19719714.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [21.382000 17.263490 0.772047 0.000000 5.000000 19.000000 33.000000 73.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [57729898.612000 39997815.760699 1788756.699849 3139526.000000 11774544.000000 67286924.000000 91500000.000000 158778802.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [15058397.600000 4466871.251262 199764.555291 310000.000000 14550900.000000 16399000.000000 17636400.000000 20916000.000000]
*/
