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

const int EXTRA_M = 10;
const int MAX_CT = 10;
static_assert(EXTRA_M * MAX_N <= (1 << MAX_CT));
const int S_MARGIN = 3;

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
const chrono::milliseconds PATTERN_TIME = 3700ms;

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
    const int n_pattern;

    int G[MAX_L][MAX_L];
    pii best_pattern[MAX_CT];
    int estimate[MAX_N];

    int opt_pow[MAX_CT+1];

    Solver(int L, int N, int S, const array<pii, MAX_N>& landing_pos) : 
        pattern_end(chrono::high_resolution_clock::now() + PATTERN_TIME),
        L(L), N(N), S(S), landing_pos(landing_pos), judge(L, N, S),
        options(max(2, MAX_TEMP / (S_MARGIN * S))), n_pattern(ceil_log(EXTRA_M * N, options)) {
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
    void assign_temps() {
        const int jump = min(S_MARGIN * S, MAX_TEMP / (options - 1));
        const int offset = (MAX_TEMP - (options - 1) * jump) / 2;
        // opts[i] = offset + i * jump;

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
            for (int i = 0; i < n_pattern; ++i) {
                to_change[i] = cell_idx[shift_coord(landing_pos[dupe_idx].row, pattern[i].row - P_SIZE)][shift_coord(landing_pos[dupe_idx].col, pattern[i].col - P_SIZE)];
            }
            sort(to_change, to_change + n_pattern, [&](const int ia, const int ib) {
                return uses[ia].size() < uses[ib].size() || (uses[ia].size() == uses[ib].size() && ia < ib);
            });

            bool done = false;
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
                            done = true;
                            break;
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
                            done = true;
                            break;
                        }
                        for (int use: uses[to_change[i]]) {
                            counter.dec(G_val[use >> 8]);
                            G_val[use >> 8] -= opt_pow[use & 0xff] * (smaller_val - old_val);
                            counter.inc(G_val[use >> 8]);
                        }
                    }
                }
                if (done) break;
            }
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
                ret += square(grid[r][c] - grid[(r+1)%L][c]) + square(grid[r][c] - grid[r][(c+1)%L]);
            }
        }
        for (int i=0; i<n_pattern; ++i) {
            ret += (10000 / n_pattern) * 100 * (10 + abs(pattern[i].row - P_SIZE) + abs(pattern[i].col - P_SIZE));
        }
        return ret;
    }
    void create_temperature() {
        const int iters = n_pattern * 100;
        int iters_run = 0;
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
            for (int it=0; it<iters && chrono::high_resolution_clock::now() < pattern_end; ++it,++iters_run) {
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

                if (old_cost <= cur_cost) {
                    in[pattern[idx].row][pattern[idx].col] = false;
                    pattern[idx].row = (pattern[idx].row + MAX_P - chr[change]) % MAX_P;
                    pattern[idx].col = (pattern[idx].col + MAX_P - chc[change]) % MAX_P;
                    in[pattern[idx].row][pattern[idx].col] = true;
                }
            }
        }
        cout << "# iters run: " << iters_run << '\n';
    }

    void predict() {
        const int trials = min(10000 / (n_pattern * N), S_MARGIN * S);
        double measurements[n_pattern];
        for (int i_in = 0; i_in < N; ++i_in) {
            for (int j = 0; j < n_pattern; ++j) {
                measurements[j] = 0;
                for (int t = 0; t < trials; ++t) {
                    measurements[j] += judge.measure(i_in, pattern[j].row - P_SIZE, pattern[j].col - P_SIZE);
                }
                measurements[j] /= trials;
            }

            double min_diff = 1e12;
            for (int i_out = 0; i_out < N; ++i_out) {
                const pii& pos = landing_pos[i_out];
                double diff = 0;
                for (int j = 0; j < n_pattern; ++j) {
                    diff += square(measurements[j] - G[shift_coord(pos.row, pattern[j].row - P_SIZE)][shift_coord(pos.col, pattern[j].col - P_SIZE)]);
                }

                if (min_diff > diff) {
                    min_diff = diff;
                    estimate[i_in] = i_out;  // TODO move around replaced estimate
                }
            }
        }
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
pragmas on test with seed=0
iters run:
none: 7671
O3: 10352
O3, unroll: 8404
unroll: 6341
Ofast: 10324
O3, avx: 9639
O3, tune=native: 10353
tune=native: 7677

Local testing results (without pragmas)
TESTS = 500. L = -1, N = -1, S = -1.
scores      mean, stddev, stderr, min, q1, med, q3, max: [1764467.284000 3424314.137074 153139.983736 1.000000 8805.000000 124073.000000 2466867.000000 18512156.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [14.236000 14.257500 0.637615 0.000000 2.000000 11.000000 20.000000 67.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [62856632.100000 52952090.129885 2368089.461622 3836990.000000 8631750.000000 54649060.000000 111000000.000000 213905920.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [16259617.200000 4081127.715304 182513.579926 680400.000000 15916000.000000 17337600.000000 18333000.000000 22632000.000000]
*/
