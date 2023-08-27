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
With full PATTERN_TIME
TESTS = 20. L = -1, N = -1, S = 1.
scores      mean, stddev, stderr, min, q1, med, q3, max: [19033367.950000 2097418.571571 468997.050330 15969508.000000 17399899.000000 19391533.000000 20912435.000000 22987502.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5044999.600000 581892.872614 130115.201879 4103190.000000 4550098.000000 4924846.000000 5741284.000000 5966634.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [173880.000000 26534.894008 5933.382678 128100.000000 153300.000000 186900.000000 197400.000000 212100.000000]
TESTS = 20. L = -1, N = -1, S = 4.
scores      mean, stddev, stderr, min, q1, med, q3, max: [19287922.500000 2251519.344386 503455.030670 15803017.000000 18167252.000000 19524364.000000 21048963.000000 24090697.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [4937383.900000 601772.597689 134560.443543 3895580.000000 4523508.000000 4796710.000000 5638020.000000 5933906.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [219030.000000 40558.280289 9069.107178 153300.000000 193200.000000 226800.000000 252000.000000 294000.000000]
TESTS = 20. L = -1, N = -1, S = 9.
scores      mean, stddev, stderr, min, q1, med, q3, max: [17696607.250000 2416289.452723 540298.746960 14285588.000000 15944087.000000 17360322.000000 19638595.000000 24333589.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5374665.800000 710587.958206 158892.297854 3782746.000000 4782490.000000 5526014.000000 6008752.000000 6547262.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [273315.000000 40862.541221 9137.141990 218400.000000 243600.000000 264600.000000 315000.000000 352800.000000]
TESTS = 20. L = -1, N = -1, S = 16.
scores      mean, stddev, stderr, min, q1, med, q3, max: [17928536.600000 1880534.926742 420500.393026 14780892.000000 16133253.000000 18469657.000000 19527642.000000 21798689.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [5180512.000000 558327.635368 124845.854640 4212232.000000 4712996.000000 5032686.000000 5793970.000000 6220692.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [360200.000000 64018.427035 14314.955466 243200.000000 313600.000000 352000.000000 425700.000000 459000.000000]
TESTS = 20. L = -1, N = -1, S = 25.
scores      mean, stddev, stderr, min, q1, med, q3, max: [14774193.300000 1555242.590480 347762.815382 12386742.000000 13489797.000000 14985387.000000 15947066.000000 18063167.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [6253993.100000 614609.118454 137430.776846 5070000.000000 5817146.000000 6331758.000000 6696278.000000 7224348.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [487455.000000 149858.231255 33509.319207 303600.000000 353600.000000 489600.000000 604800.000000 836400.000000]
TESTS = 20. L = -1, N = -1, S = 36.
scores      mean, stddev, stderr, min, q1, med, q3, max: [11658704.700000 1874806.444050 419219.465355 8532907.000000 10196225.000000 12050882.000000 13193956.000000 15655470.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [7976747.500000 1257889.234087 281272.583558 5878144.000000 7033238.000000 8051442.000000 8932612.000000 10609536.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [720395.000000 156387.165314 34969.233245 409400.000000 620100.000000 691200.000000 843700.000000 1009800.000000]
TESTS = 20. L = -1, N = -1, S = 49.
scores      mean, stddev, stderr, min, q1, med, q3, max: [8311631.850000 1661777.812476 371584.815220 5736693.000000 7283967.000000 7964853.000000 9444949.000000 12623471.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [11513245.700000 2136032.329049 477631.348989 7093752.000000 10072722.000000 12008410.000000 12718708.000000 16146648.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [868805.000000 227814.227991 50940.810003 541500.000000 714000.000000 897000.000000 1109600.000000 1360000.000000]
TESTS = 20. L = -1, N = -1, S = 64.
scores      mean, stddev, stderr, min, q1, med, q3, max: [7194474.050000 2262130.622454 505827.784579 4349269.000000 5582542.000000 6822108.000000 8533088.000000 13000521.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [13894874.100000 4019505.692295 898788.796392 6760000.000000 11362660.000000 14027876.000000 17485360.000000 21302372.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [1168535.000000 260301.621729 58205.212084 739500.000000 939300.000000 1195400.000000 1364000.000000 1590000.000000]
TESTS = 20. L = -1, N = -1, S = 81.
scores      mean, stddev, stderr, min, q1, med, q3, max: [5092699.050000 2487865.814122 556303.707927 2584628.000000 3345996.000000 4593513.000000 5783414.000000 11917281.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [21126019.600000 8072718.594131 1805114.753970 7018176.000000 15129000.000000 19783834.000000 28058458.000000 36109700.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2002680.000000 493699.819323 110394.635649 1118600.000000 1455200.000000 2187900.000000 2366000.000000 2739000.000000]
TESTS = 20. L = -1, N = -1, S = 100.
scores      mean, stddev, stderr, min, q1, med, q3, max: [2829791.350000 1123254.928473 251167.437613 334313.000000 2291744.000000 2754006.000000 3234623.000000 5852158.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.400000 1.743560 0.389872 0.000000 0.000000 0.000000 0.000000 8.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [35314112.600000 10319330.877947 2307472.532540 15429014.000000 29177806.000000 35690078.000000 45416024.000000 57701590.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2301560.000000 701196.038494 156792.200763 1504900.000000 1720500.000000 2460000.000000 2552100.000000 4651200.000000]
TESTS = 20. L = -1, N = -1, S = 121.
scores      mean, stddev, stderr, min, q1, med, q3, max: [2138788.350000 817844.916486 182875.682832 1326929.000000 1563746.000000 2110100.000000 2432005.000000 5105897.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [49208321.400000 13646175.580354 3051377.623057 17860800.000000 39415980.000000 51505640.000000 61867646.000000 72678016.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2227580.000000 323166.445659 72262.214054 1624400.000000 2011100.000000 2227800.000000 2383800.000000 2946300.000000]
TESTS = 20. L = -1, N = -1, S = 144.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1818345.450000 762865.079516 170581.817546 951950.000000 1127609.000000 1768709.000000 2327610.000000 3917721.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [62481426.800000 24364293.308165 5448021.606080 24178750.000000 41274396.000000 57030314.000000 88547556.000000 102540560.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2041930.000000 439771.786385 98335.960894 1246300.000000 1601600.000000 2243600.000000 2433600.000000 2715000.000000]
TESTS = 20. L = -1, N = -1, S = 169.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1182262.800000 476603.931166 106571.878843 683503.000000 908426.000000 992585.000000 1425746.000000 2551802.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [92888165.600000 28186739.554080 6302746.570700 37570000.000000 68517086.000000 98352784.000000 113723132.000000 143437228.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2220040.000000 467994.057014 104646.652455 1192600.000000 2008600.000000 2257600.000000 2573000.000000 3150000.000000]
TESTS = 20. L = -1, N = -1, S = 196.
scores      mean, stddev, stderr, min, q1, med, q3, max: [926802.300000 414930.002473 92781.169143 180571.000000 681393.000000 748321.000000 1165038.000000 1929225.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.250000 1.089725 0.243670 0.000000 0.000000 0.000000 0.000000 5.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [118616483.900000 38693523.657496 8652134.918716 50451700.000000 84985182.000000 131812406.000000 147023196.000000 174725960.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2378200.000000 1098956.530078 245734.150557 1282600.000000 1736000.000000 2387000.000000 2640600.000000 6642900.000000]
TESTS = 20. L = -1, N = -1, S = 225.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1028599.400000 350565.213346 78388.764759 463181.000000 729582.000000 1008500.000000 1309937.000000 1787790.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [107278309.300000 40289070.678051 9008910.078641 53750000.000000 82446840.000000 97864206.000000 140278280.000000 211869174.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [2693440.000000 597101.837545 133516.029824 1781200.000000 2282000.000000 2430000.000000 3128000.000000 3929400.000000]
TESTS = 20. L = -1, N = -1, S = 256.
scores      mean, stddev, stderr, min, q1, med, q3, max: [912358.050000 336449.724072 75232.445404 565540.000000 690498.000000 750372.000000 1104343.000000 1901286.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [117394254.000000 33493088.377586 7489282.238869 50000000.000000 87517428.000000 128849166.000000 141701134.000000 172169586.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [3975420.000000 647107.033341 144697.531527 2496000.000000 3770100.000000 4029000.000000 4532600.000000 4905100.000000]
TESTS = 20. L = -1, N = -1, S = 289.
scores      mean, stddev, stderr, min, q1, med, q3, max: [913485.150000 395542.401801 88445.969841 315313.000000 702504.000000 842244.000000 1086096.000000 2024243.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.100000 0.435890 0.097468 0.000000 0.000000 0.000000 0.000000 2.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [120051651.200000 42982134.159391 9611097.379842 46000000.000000 90813470.000000 125983666.000000 159016122.000000 211236896.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [4689395.000000 942378.068757 210722.142225 3228900.000000 4203900.000000 4645500.000000 5292300.000000 6716100.000000]
TESTS = 20. L = -1, N = -1, S = 324.
scores      mean, stddev, stderr, min, q1, med, q3, max: [960897.000000 459977.908854 102854.187235 375564.000000 597888.000000 847180.000000 1219295.000000 2105698.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.050000 0.217945 0.048734 0.000000 0.000000 0.000000 0.000000 1.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [119622194.700000 49638849.694675 11099584.224219 44000000.000000 78479730.000000 114524028.000000 161839622.000000 215564520.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [5457870.000000 1173496.485338 262401.791257 3390200.000000 4519800.000000 5490100.000000 6429600.000000 7820000.000000]
TESTS = 20. L = -1, N = -1, S = 361.
scores      mean, stddev, stderr, min, q1, med, q3, max: [864451.750000 426715.582973 95416.505059 508725.000000 591355.000000 692532.000000 1027463.000000 1771392.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.050000 0.217945 0.048734 0.000000 0.000000 0.000000 0.000000 1.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [130478615.800000 46405778.566211 10376647.542285 46000000.000000 113677578.000000 137998108.000000 170942134.000000 189247968.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [6269120.000000 1153439.633271 257916.942794 4293500.000000 5530800.000000 6532200.000000 7220900.000000 8384800.000000]
TESTS = 20. L = -1, N = -1, S = 400.
scores      mean, stddev, stderr, min, q1, med, q3, max: [771787.750000 232875.942097 52072.643685 451936.000000 587905.000000 770707.000000 919597.000000 1420002.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [133660953.800000 38665980.891429 8645976.168994 65732060.000000 102306782.000000 130262308.000000 165812144.000000 212142434.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [7002520.000000 981648.988998 219503.386944 4590400.000000 6302400.000000 7252200.000000 7691600.000000 9028000.000000]
TESTS = 20. L = -1, N = -1, S = 441.
scores      mean, stddev, stderr, min, q1, med, q3, max: [877603.150000 377794.252255 84477.362955 224430.000000 603722.000000 886425.000000 1256708.000000 1653642.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.350000 0.792149 0.177130 0.000000 0.000000 0.000000 0.000000 3.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [119559070.500000 49471464.660321 11062155.792696 54000000.000000 80216670.000000 107135790.000000 157340062.000000 218249102.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [7414825.000000 1615469.797884 361230.028367 4771200.000000 6372600.000000 7760000.000000 8633200.000000 10754800.000000]
TESTS = 20. L = -1, N = -1, S = 484.
scores      mean, stddev, stderr, min, q1, med, q3, max: [812650.250000 275780.967248 61666.498967 383939.000000 601028.000000 893659.000000 1047246.000000 1281723.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.250000 0.433013 0.096825 0.000000 0.000000 0.000000 1.000000 1.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [125061850.000000 49196843.014813 11000748.525951 61250000.000000 88332298.000000 103735594.000000 167755154.000000 220950848.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [7859375.000000 1401610.918149 313409.729099 5674200.000000 6645600.000000 8361900.000000 9315000.000000 9552000.000000]
TESTS = 20. L = -1, N = -1, S = 529.
scores      mean, stddev, stderr, min, q1, med, q3, max: [920765.100000 333311.009201 74530.607422 371226.000000 700816.000000 827136.000000 1285232.000000 1561276.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.150000 0.357071 0.079844 0.000000 0.000000 0.000000 0.000000 1.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [110953934.300000 42186572.894164 9433204.472910 56000000.000000 81410450.000000 106190388.000000 147049104.000000 205855038.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [8697240.000000 1418479.547050 317181.669190 5359500.000000 7950200.000000 8700700.000000 10020600.000000 10773000.000000]
TESTS = 20. L = -1, N = -1, S = 576.
scores      mean, stddev, stderr, min, q1, med, q3, max: [868560.300000 301789.391809 67482.159497 413934.000000 690994.000000 867646.000000 1129791.000000 1651296.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.400000 0.489898 0.109545 0.000000 0.000000 0.000000 1.000000 1.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [108328549.400000 37397490.015596 8362332.986274 42000000.000000 84762736.000000 104505758.000000 131060974.000000 180428306.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [10191420.000000 1987598.122257 444440.451332 5697400.000000 9285300.000000 9954200.000000 11850100.000000 13558200.000000]
TESTS = 20. L = -1, N = -1, S = 625.
scores      mean, stddev, stderr, min, q1, med, q3, max: [827501.450000 335793.957682 75085.811581 205684.000000 628489.000000 767790.000000 1111737.000000 1714949.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [0.500000 1.024695 0.229129 0.000000 0.000000 0.000000 1.000000 4.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [110826881.700000 36797078.108045 8228076.802296 48000000.000000 78582546.000000 114553576.000000 142283108.000000 183002088.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [13726190.000000 2318421.965454 518414.911528 10210800.000000 11384800.000000 13201400.000000 16039200.000000 18032000.000000]
TESTS = 20. L = -1, N = -1, S = 676.
scores      mean, stddev, stderr, min, q1, med, q3, max: [682984.350000 305685.371855 68353.327120 248276.000000 483204.000000 701127.000000 805866.000000 1445369.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [1.000000 1.000000 0.223607 0.000000 0.000000 1.000000 2.000000 3.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [117909002.700000 42430266.741915 9487696.073837 54000000.000000 98633342.000000 112287158.000000 143518942.000000 237346954.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17757340.000000 1602410.461586 358309.871996 15086500.000000 16782600.000000 17799600.000000 19092000.000000 20331300.000000]
TESTS = 20. L = -1, N = -1, S = 729.
scores      mean, stddev, stderr, min, q1, med, q3, max: [724303.550000 388800.959429 86938.537500 30536.000000 361146.000000 839818.000000 1109595.000000 1282142.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [2.100000 2.998333 0.670448 0.000000 0.000000 1.000000 3.000000 12.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [105580023.500000 45923198.202978 10268739.292605 48000000.000000 66750000.000000 99823868.000000 152635016.000000 205570032.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17774265.000000 1788069.863925 399824.576425 14295600.000000 16508800.000000 18156000.000000 19215000.000000 20553500.000000]
TESTS = 20. L = -1, N = -1, S = 784.
scores      mean, stddev, stderr, min, q1, med, q3, max: [461942.750000 387848.932122 86725.657723 36694.000000 172980.000000 427714.000000 666754.000000 1518075.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [4.800000 3.722902 0.832466 0.000000 2.000000 5.000000 6.000000 12.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [104500671.600000 50502816.367991 11292773.045402 46000000.000000 62000000.000000 89686888.000000 152982186.000000 215033224.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17604940.000000 1795787.990382 401550.401967 14776300.000000 15772900.000000 18109300.000000 19197500.000000 20331300.000000]
TESTS = 20. L = -1, N = -1, S = 841.
scores      mean, stddev, stderr, min, q1, med, q3, max: [377456.300000 382508.822551 85531.572922 31359.000000 83237.000000 275334.000000 662485.000000 1454879.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [6.050000 3.955692 0.884520 1.000000 2.000000 6.000000 10.000000 13.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [116116733.800000 47912031.311689 10713455.895303 40000000.000000 79000000.000000 104624434.000000 178236118.000000 200817626.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [17780080.000000 1440874.195619 322189.264843 14220800.000000 17125000.000000 18553700.000000 18775900.000000 19775800.000000]
TESTS = 20. L = -1, N = -1, S = 900.
scores      mean, stddev, stderr, min, q1, med, q3, max: [165478.950000 186824.765232 41775.287494 692.000000 33216.000000 96779.000000 302453.000000 654910.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [11.100000 6.624953 1.481384 3.000000 6.000000 12.000000 14.000000 29.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [122821720.200000 48295954.483146 10799303.726255 46000000.000000 88833334.000000 119143062.000000 160774396.000000 206031458.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [18046865.000000 1438736.081523 321711.167997 14443000.000000 17442700.000000 17998200.000000 19442500.000000 20442400.000000]
*/

