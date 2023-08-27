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
        ll ret = (N - counter.total) * 1'000'000'000'000'000LL;  // have as few duplicates as possible
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
                }
            }
        }
        //debug1(best_pattern, n_pattern);
        //debug(best_cost);
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
scores      mean, stddev, stderr, min, q1, med, q3, max: [17470524.350000 2362648.766767 528304.324945 14259595.000000 15760124.000000 17015126.000000 19335613.000000 22940263.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5045205.100000 705815.124762 157825.059852 3637548.000000 4550098.000000 5096724.000000 5727766.000000 6123222.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [679560.000000 95697.347926 21398.577523 504000.000000 613200.000000 714000.000000 772800.000000 806400.000000]
TESTS = 20. L = -1, N = -1, S = 4.
scores      mean, stddev, stderr, min, q1, med, q3, max: [18138450.250000 2157470.434683 482425.055140 14348113.000000 16533512.000000 18419178.000000 19853450.000000 22277620.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [4840640.600000 648084.814038 144916.169937 3876410.000000 4407708.000000 4650192.000000 5367276.000000 6107032.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [653940.000000 102682.054907 22960.405484 512400.000000 571200.000000 646800.000000 747600.000000 840000.000000]
TESTS = 20. L = -1, N = -1, S = 9.
scores      mean, stddev, stderr, min, q1, med, q3, max: [17475242.300000 2749127.530708 614723.603748 13789524.000000 15001132.000000 17372029.000000 19558786.000000 24935082.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5076615.400000 814338.804838 182091.692433 3364414.000000 4417240.000000 5055472.000000 5835364.000000 6353882.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [682080.000000 99765.693502 22308.287249 504000.000000 613200.000000 697200.000000 781200.000000 840000.000000]
TESTS = 20. L = -1, N = -1, S = 16.
scores      mean, stddev, stderr, min, q1, med, q3, max: [15121596.300000 1437911.064423 321526.688565 12877097.000000 14459159.000000 15120573.000000 16019013.000000 19052315.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5269337.700000 506865.091962 113338.480105 4124706.000000 5064776.000000 5214576.000000 5833958.000000 6015726.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [1301875.000000 174395.805210 38996.087544 1024000.000000 1184000.000000 1280000.000000 1440000.000000 1650000.000000]
TESTS = 20. L = -1, N = -1, S = 25.
scores      mean, stddev, stderr, min, q1, med, q3, max: [12048520.500000 1793210.563790 400974.071860 9923286.000000 10552308.000000 11159771.000000 13926665.000000 16000850.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [6339316.000000 630177.316602 140911.931780 4847668.000000 5799470.000000 6524432.000000 6833954.000000 7127308.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2036460.000000 648496.112864 145008.139151 1281000.000000 1326600.000000 2091000.000000 2763600.000000 2940000.000000]
TESTS = 20. L = -1, N = -1, S = 36.
scores      mean, stddev, stderr, min, q1, med, q3, max: [9415288.050000 1320296.759141 295227.330391 7478032.000000 8207863.000000 9591212.000000 10291355.000000 12115503.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [7623026.500000 1197482.207786 267765.161846 5458888.000000 6973344.000000 7564442.000000 8833152.000000 9699704.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [3108805.000000 476628.826735 106577.445662 2268000.000000 2730000.000000 3192000.000000 3486000.000000 4204200.000000]
TESTS = 20. L = -1, N = -1, S = 49.
scores      mean, stddev, stderr, min, q1, med, q3, max: [6405236.750000 1523460.029303 340656.018653 4348958.000000 5032096.000000 6662926.000000 7588218.000000 10541943.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [11509968.200000 2464886.714297 551165.425000 6613918.000000 10030872.000000 11486144.000000 13355276.000000 16259288.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [4842240.000000 1411956.681488 315723.112109 2635200.000000 3848000.000000 5264000.000000 5920000.000000 7216800.000000]
TESTS = 20. L = -1, N = -1, S = 64.
scores      mean, stddev, stderr, min, q1, med, q3, max: [5151919.450000 1120544.212715 250561.303143 3638548.000000 4290250.000000 5140846.000000 5616224.000000 7493257.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [13794445.300000 3116661.213484 696906.633619 7182500.000000 12449962.000000 14179212.000000 16118468.000000 18276606.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [6367950.000000 1274399.475635 284964.385801 4240800.000000 5728500.000000 6256800.000000 6993000.000000 9253800.000000]
TESTS = 20. L = -1, N = -1, S = 81.
scores      mean, stddev, stderr, min, q1, med, q3, max: [3387702.150000 1043560.215263 233347.157994 1385855.000000 2731729.000000 3300141.000000 4148724.000000 6385207.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.150000 0.476970 0.106654 0.000000 0.000000 0.000000 0.000000 2.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [18913756.600000 5970815.118259 1335114.848551 8741200.000000 14072584.000000 19851736.000000 24538902.000000 30274492.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [11901960.000000 2605087.587472 582515.293293 6820000.000000 10350000.000000 11869000.000000 14703000.000000 16587000.000000]
TESTS = 20. L = -1, N = -1, S = 100.
scores      mean, stddev, stderr, min, q1, med, q3, max: [2435147.850000 1063087.891112 237713.679058 432178.000000 1847508.000000 2237072.000000 3115941.000000 4652386.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.250000 1.089725 0.243670 0.000000 0.000000 0.000000 0.000000 5.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [33026119.100000 13629539.758219 3047657.740141 13771350.000000 21800392.000000 32944332.000000 46005128.000000 56585684.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [13497685.000000 3349023.963676 748864.524105 7623000.000000 11979000.000000 13556400.000000 16176600.000000 19135000.000000]
TESTS = 20. L = -1, N = -1, S = 121.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1571083.500000 751838.739160 168116.252888 144718.000000 1298676.000000 1467245.000000 1715150.000000 3474491.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.750000 2.299456 0.514174 0.000000 0.000000 0.000000 0.000000 9.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [51045897.800000 15966717.748303 3570266.626276 17860800.000000 45314312.000000 54774490.000000 62009652.000000 76535370.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [15410665.000000 2015593.103103 450700.319352 10820400.000000 14541600.000000 16202400.000000 16422000.000000 19747200.000000]
TESTS = 20. L = -1, N = -1, S = 144.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1436800.150000 599202.068171 133985.655669 158997.000000 1116469.000000 1414201.000000 1616508.000000 2850945.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.350000 1.525615 0.341138 0.000000 0.000000 0.000000 0.000000 7.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [61618252.600000 25935280.552840 5799305.033168 25230000.000000 46255000.000000 56152744.000000 74826624.000000 122798826.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [15554375.000000 2334998.602757 522121.560313 9746100.000000 14458600.000000 16099200.000000 17459000.000000 18775900.000000]
TESTS = 20. L = -1, N = -1, S = 169.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1035450.950000 412008.125684 92127.817631 340712.000000 846068.000000 997794.000000 1249462.000000 2001811.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.200000 0.600000 0.134164 0.000000 0.000000 0.000000 0.000000 2.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [90198718.600000 35469859.998738 7931301.810958 35944376.000000 66998474.000000 90244530.000000 102488878.000000 169188546.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [16647930.000000 1937212.484241 433173.880162 12936000.000000 15069600.000000 17553800.000000 18345600.000000 19220300.000000]
TESTS = 20. L = -1, N = -1, S = 196.
scores      mean, stddev, stderr, min, q1, med, q3, max: [798464.400000 321090.644953 71798.050905 121559.000000 603429.000000 851875.000000 1068444.000000 1260815.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.550000 1.465435 0.327681 0.000000 0.000000 0.000000 0.000000 6.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [116243301.800000 44532252.208824 9957714.313010 63792294.000000 78377428.000000 108010594.000000 163819218.000000 213092158.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17095180.000000 2422809.471585 541756.667499 12060000.000000 16331700.000000 17664900.000000 19109200.000000 20886800.000000]
TESTS = 20. L = -1, N = -1, S = 225.
scores      mean, stddev, stderr, min, q1, med, q3, max: [842803.800000 311253.294741 69598.352526 469892.000000 622877.000000 828403.000000 1061468.000000 1573740.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [116504776.600000 44440287.152654 9937150.301294 48000000.000000 84651194.000000 111961008.000000 160712884.000000 194050474.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17719020.000000 1359330.187850 303955.470390 14331900.000000 16998300.000000 18268800.000000 18775900.000000 19553600.000000]
TESTS = 20. L = -1, N = -1, S = 256.
scores      mean, stddev, stderr, min, q1, med, q3, max: [753319.300000 418553.129749 93591.325031 49598.000000 530164.000000 661323.000000 894233.000000 1789665.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.500000 2.179449 0.487340 0.000000 0.000000 0.000000 0.000000 10.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [135218469.000000 49356711.901077 11036496.295668 42000000.000000 111585004.000000 138734166.000000 181781326.000000 215160246.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17742035.000000 2285988.218315 511162.505192 12185600.000000 17998200.000000 18331500.000000 19442500.000000 20664600.000000]
TESTS = 20. L = -1, N = -1, S = 289.
scores      mean, stddev, stderr, min, q1, med, q3, max: [756993.500000 178509.274591 39915.887260 507729.000000 623889.000000 755963.000000 862143.000000 1245008.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [121001342.200000 29516080.250845 6599996.187023 66000000.000000 99089156.000000 119671448.000000 153675574.000000 177524246.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17920565.000000 1492629.107406 333762.014935 14220800.000000 17442700.000000 17998200.000000 19109200.000000 20331300.000000]
TESTS = 20. L = -1, N = -1, S = 324.
scores      mean, stddev, stderr, min, q1, med, q3, max: [733829.300000 371657.783411 83105.206807 110890.000000 516477.000000 644382.000000 854086.000000 1814932.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.300000 1.307670 0.292404 0.000000 0.000000 0.000000 0.000000 6.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [138397981.100000 54712075.848839 12233992.078813 40000000.000000 101689690.000000 139787828.000000 173992356.000000 256477954.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18135445.000000 1756285.988521 392717.485826 13554200.000000 17442700.000000 19109200.000000 19553600.000000 19886900.000000]
TESTS = 20. L = -1, N = -1, S = 361.
scores      mean, stddev, stderr, min, q1, med, q3, max: [707407.050000 230261.011811 51487.927498 128706.000000 558527.000000 725673.000000 897457.000000 1149592.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.350000 1.152172 0.257633 0.000000 0.000000 0.000000 0.000000 5.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [127868327.400000 38786882.494066 8673010.589203 72000000.000000 94216672.000000 131489366.000000 158500110.000000 234608870.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18449040.000000 1520530.874202 340001.039660 14887400.000000 17887100.000000 18553700.000000 19520000.000000 20997900.000000]
TESTS = 20. L = -1, N = -1, S = 400.
scores      mean, stddev, stderr, min, q1, med, q3, max: [833583.850000 385231.948937 86140.482493 416135.000000 566489.000000 700473.000000 956461.000000 1653576.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.050000 0.217945 0.048734 0.000000 0.000000 0.000000 0.000000 1.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [121640579.600000 46417463.145909 10379260.293734 46000000.000000 92084150.000000 135760780.000000 157539194.000000 222208742.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17600555.000000 1943880.472528 434664.887671 13250000.000000 17553800.000000 18442600.000000 18887000.000000 19553600.000000]
TESTS = 20. L = -1, N = -1, S = 441.
scores      mean, stddev, stderr, min, q1, med, q3, max: [846937.200000 318484.792017 71215.364475 135423.000000 720012.000000 790421.000000 990225.000000 1796810.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.300000 1.307670 0.292404 0.000000 0.000000 0.000000 0.000000 6.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [107006339.300000 31764433.252020 7102743.201827 42000000.000000 89714106.000000 109259344.000000 126477772.000000 175809340.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18217985.000000 1466276.138139 327869.311866 13554200.000000 17664900.000000 18664800.000000 19220300.000000 20000000.000000]
TESTS = 20. L = -1, N = -1, S = 484.
scores      mean, stddev, stderr, min, q1, med, q3, max: [751798.950000 313615.932947 70126.654490 266876.000000 492034.000000 687198.000000 1020541.000000 1413124.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.250000 0.536190 0.119896 0.000000 0.000000 0.000000 0.000000 2.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [129680082.600000 51214376.476408 11451882.722651 56000000.000000 89679180.000000 129465114.000000 183063892.000000 221380572.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17469175.000000 1604330.720542 358739.254952 14665200.000000 15887300.000000 17887100.000000 18664800.000000 19998000.000000]
TESTS = 20. L = -1, N = -1, S = 529.
scores      mean, stddev, stderr, min, q1, med, q3, max: [673495.650000 161167.021588 36038.041600 397727.000000 557871.000000 703744.000000 802867.000000 960178.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.050000 0.217945 0.048734 0.000000 0.000000 0.000000 0.000000 1.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [136927220.800000 38387488.276198 8583703.327105 85382662.000000 107997630.000000 125891732.000000 171776934.000000 212458144.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18853860.000000 835640.807644 186854.965066 17750000.000000 17998200.000000 18887000.000000 19553600.000000 20775700.000000]
TESTS = 20. L = -1, N = -1, S = 576.
scores      mean, stddev, stderr, min, q1, med, q3, max: [747600.700000 346695.540476 77523.479600 184165.000000 497631.000000 809989.000000 1108531.000000 1382729.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.850000 1.275735 0.285263 0.000000 0.000000 0.000000 2.000000 4.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [118980625.600000 50188548.814513 11222500.684132 48000000.000000 80000000.000000 105804680.000000 174099800.000000 209131350.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17445055.000000 1640005.174832 366716.305438 13776400.000000 16109500.000000 17887100.000000 18775900.000000 19886900.000000]
TESTS = 20. L = -1, N = -1, S = 625.
scores      mean, stddev, stderr, min, q1, med, q3, max: [575408.350000 331354.721783 74093.168257 159595.000000 336807.000000 525569.000000 735953.000000 1579263.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [1.200000 1.435270 0.320936 0.000000 0.000000 1.000000 2.000000 5.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [146611505.500000 53212673.114807 11898715.434918 48000000.000000 99288832.000000 150252134.000000 199848902.000000 237330130.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18345765.000000 1343805.027255 300483.938945 15220700.000000 17442700.000000 18331500.000000 19442500.000000 20553500.000000]
TESTS = 20. L = -1, N = -1, S = 676.
scores      mean, stddev, stderr, min, q1, med, q3, max: [551666.250000 252885.251537 56546.861294 117985.000000 421359.000000 511198.000000 720783.000000 1248078.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [1.700000 1.676305 0.374833 0.000000 0.000000 1.000000 3.000000 6.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [127222703.100000 41494616.024512 9278478.213106 50000000.000000 97298824.000000 132824062.000000 161902930.000000 203197810.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18173280.000000 1461515.412030 326804.781146 13998600.000000 17553800.000000 18664800.000000 19220300.000000 19886900.000000]
TESTS = 20. L = -1, N = -1, S = 729.
scores      mean, stddev, stderr, min, q1, med, q3, max: [597807.500000 372221.048615 83231.156736 68917.000000 352461.000000 562222.000000 1042062.000000 1264223.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [2.350000 2.797767 0.625600 0.000000 0.000000 1.000000 4.000000 9.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [119665473.900000 41194820.786007 9211441.959843 50000000.000000 89654616.000000 125855914.000000 153932864.000000 201495880.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18208765.000000 1254463.679536 280506.606275 15442900.000000 17776000.000000 18553700.000000 19220300.000000 20775700.000000]
TESTS = 20. L = -1, N = -1, S = 784.
scores      mean, stddev, stderr, min, q1, med, q3, max: [375969.250000 302098.285240 67551.230168 3442.000000 113047.000000 359462.000000 654830.000000 969166.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [5.550000 5.239036 1.171484 0.000000 2.000000 3.000000 10.000000 22.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [136553633.900000 51582003.624321 11534086.651962 64000000.000000 89000000.000000 151199384.000000 181219608.000000 225534226.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17901355.000000 1610496.230196 360117.904823 14443000.000000 16665000.000000 17750000.000000 19500000.000000 20886800.000000]
TESTS = 20. L = -1, N = -1, S = 841.
scores      mean, stddev, stderr, min, q1, med, q3, max: [237523.550000 205179.649972 45879.564494 13477.000000 65395.000000 170445.000000 353154.000000 786080.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [6.500000 3.694591 0.826136 2.000000 4.000000 6.000000 10.000000 16.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [139107395.000000 38683344.059148 8649858.691327 63816670.000000 117403434.000000 153144218.000000 172707552.000000 208025364.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18710800.000000 1184540.011566 264871.198793 16109500.000000 17998200.000000 18775900.000000 19553600.000000 20886800.000000]
TESTS = 20. L = -1, N = -1, S = 900.
scores      mean, stddev, stderr, min, q1, med, q3, max: [216313.700000 223155.907723 49899.177925 5358.000000 44482.000000 103327.000000 400760.000000 715512.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [9.150000 6.052066 1.353283 1.000000 4.000000 9.000000 15.000000 20.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [126419701.000000 44498213.091134 9950102.934905 64000000.000000 94265394.000000 122944680.000000 144645466.000000 236658568.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18102635.000000 1274015.877168 284878.610576 14998500.000000 17442700.000000 18442600.000000 18998100.000000 20220200.000000]
*/
