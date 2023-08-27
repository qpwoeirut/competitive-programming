#include <bits/stdc++.h>

using namespace std;

#include "qpwoeirut/debug.h"

using pii=pair<int,int>;
using ll=long long;

namespace Tester {
    mt19937 rng(8);

    const int MIN_L = 10, MAX_L = 50;
    const int MIN_N = 60, MAX_N = 100;
    const int MIN_S = 1, MAX_S = 900;
    const int MIN_TEMP = 0, MAX_TEMP = 1000;

    const int STARTING = 0;
    const int SET_TEMP = 1;
    const int MEASURED = 2;
    const int ANSWERED = 3;

    struct Result {
        int W;
        ll placement;
        ll measurement;
        ll measures;

        Result() {
            W = placement = measurement = measures = 0;
        }

        ll score() const {
            long double numer = 1e14;
            for (int i=0; i<W; ++i) numer *= 0.8;
            return ceil(numer / (placement + measurement + 1e5));
        }
    };

    int square(const int x) { return x * x; }

    struct Judge {
        int step;

        const int L, N, S;
        pii exit_cells[MAX_N];
        int G[MAX_L][MAX_L];

        normal_distribution<double> distrib;
        int secret[MAX_N];

        Result result;

        Judge(int L, int N, int S) : L(L), N(N), S(S), distrib(0, S) {
            assert(MIN_L <= L && L <= MAX_L);
            assert(MIN_N <= N && N <= MAX_N);
            assert(MIN_S <= S && S <= MAX_S);

            for (int i=0; i<N; ++i) secret[i] = i;
            shuffle(secret, secret+N, rng);

            step = STARTING;
        }

        void set_landing_pos(const array<pii, MAX_N>& landing_pos) {
            assert(step == STARTING);
            copy(landing_pos.begin(), landing_pos.end(), exit_cells);
        }

        void set_temperature(const int temperature[MAX_L][MAX_L]) {
            assert(step == STARTING);
            for (int r=0; r<L; ++r) {
                for (int c=0; c<L; ++c) {
                    G[r][c] = temperature[r][c];
                    assert(MIN_TEMP <= G[r][c] && G[r][c] <= MAX_TEMP);
                }
            }
            step = SET_TEMP;

            for (int r=0; r<L; ++r) {
                for (int c=0; c<L; ++c) {
                    result.placement += square(G[r][c] - G[(r+L-1)%L][c]) + square(G[r][c] - G[r][(c+L-1)%L]);
                }
            }
        }

        int measure(int i, int dr, int dc) {
            assert(0 <= i && i < N);
            assert(-L < dr && dr < L);
            assert(-L < dc && dc < L);

            ++result.measures;
            assert(result.measures <= 10000);

            assert(step == SET_TEMP || step == MEASURED);
            step = MEASURED;

            const int end_r = (exit_cells[secret[i]].first + dr + L) % L;
            const int end_c = (exit_cells[secret[i]].second + dc + L) % L;
            const int val = G[end_r][end_c] + round(distrib(rng));

            result.measurement += 100 * (10 + abs(dr) + abs(dc));
            return max(MIN_TEMP, min(val, MAX_TEMP));
        }

        void answer(const int estimate[MAX_N]) {
            assert(step == SET_TEMP || step == MEASURED);
            step = ANSWERED;

            result.W = 0;
            for (int i=0; i<N; ++i) {
                result.W += secret[i] != estimate[i];
            }
        }

        Result results() {
            assert(step == ANSWERED);
            return result;
        }
    };
}

#define USING_TESTER
#include "sol.cpp"

namespace Tester {
    const int TESTS = 10;

    pii all_landing_pos[MAX_L * MAX_L];
    array<pii, MAX_N> landing_pos;
    Result run_test(int L, int N, int S, int temp_range, int s_margin) {
        for (int r=0; r<L; ++r) {
            for (int c=0; c<L; ++c) {
                all_landing_pos[r*L+c] = pii(r, c);
            }
        }
        shuffle(all_landing_pos, all_landing_pos + L*L, rng);
        copy(all_landing_pos, all_landing_pos + N, landing_pos.begin());

        if (temp_range != -1 || s_margin != -1) {
            assert(1 <= temp_range && temp_range <= 1000);
            assert(1 <= s_margin);
            if (L < 11) {
                Solver<4> solver(L, N, S, landing_pos, temp_range, s_margin);
                solver.solve();
                return solver.judge.results();
            } else if (L < 13) {
                Solver<5> solver(L, N, S, landing_pos, temp_range, s_margin);
                solver.solve();
                return solver.judge.results();
            } else if (L < 15) {
                Solver<6> solver(L, N, S, landing_pos, temp_range, s_margin);
                solver.solve();
                return solver.judge.results();
            } else if (L < 17) {
                Solver<7> solver(L, N, S, landing_pos, temp_range, s_margin);
                solver.solve();
                return solver.judge.results();
            } else {
                Solver<8> solver(L, N, S, landing_pos, temp_range, s_margin);
                solver.solve();
                return solver.judge.results();
            }
        } else {
            if (L < 11) {
                Solver<4> solver(L, N, S, landing_pos);
                solver.solve();
                return solver.judge.results();
            } else if (L < 13) {
                Solver<5> solver(L, N, S, landing_pos);
                solver.solve();
                return solver.judge.results();
            } else if (L < 15) {
                Solver<6> solver(L, N, S, landing_pos);
                solver.solve();
                return solver.judge.results();
            } else if (L < 17) {
                Solver<7> solver(L, N, S, landing_pos);
                solver.solve();
                return solver.judge.results();
            } else {
                Solver<8> solver(L, N, S, landing_pos);
                solver.solve();
                return solver.judge.results();
            }
        }
    }

    uniform_int_distribution<> L_dist(MIN_L, MAX_L);
    uniform_int_distribution<> N_dist(MIN_N, MAX_N);
    uniform_int_distribution<> sqrtS_dist(1, 30);

    struct ResultList {
        array<int, TESTS> W;
        array<ll, TESTS> placement, measurement, measures;
        array<ll, TESTS> score;
        int n;
        ResultList() {
            W = array<int, TESTS>();
            placement = array<ll, TESTS>();
            measurement = array<ll, TESTS>();
            measures = array<ll, TESTS>();
            score = array<ll, TESTS>();

            n = 0;
        }

        void add_result(const Result& res) {
            W[n] = res.W;
            placement[n] = res.placement;
            measurement[n] = res.measurement;
            measures[n] = res.measures;
            score[n] = res.score();

            ++n;
        }

        template <class T> array<long double, 8> stats_of(const array<T, TESTS> arr) {
            long double sum = 0;
            for (const T x: arr) sum += x;
            long double mean = sum / n;

            long double variance = 0;
            for (const T x: arr) {
                variance += (x - mean) * (x - mean);
            }
            long double stddev = sqrt(variance / n);
            long double stderror = sqrt(variance) / n;

            array<T, TESTS> tmp(arr);
            sort(tmp.begin(), tmp.end());
            // quartiles are approximate, should be good enough
            return {mean, stddev, stderror, *min_element(arr.begin(), arr.end()), tmp[TESTS / 4], tmp[TESTS / 2], tmp[3 * TESTS / 4], *max_element(arr.begin(), arr.end())};
        }

        void print_stats(int L, int N, int S, int temp_range, int s_margin) {
            cout << "TESTS = " + to_string(TESTS) + ". L = " + to_string(L) + ", N = " + to_string(N) + ", S = " + to_string(S) + ", temp_range = " + to_string(temp_range) + ", s_margin = " + to_string(s_margin) + ".\n";
            cout << "scores      mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(score)) << endl;
            cout << "W           mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(W)) << endl;
            cout << "placement   mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(placement)) << endl;
            cout << "measurement mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(measurement)) << endl;
            cout << "measures    mean, stddev, stderr, min, q1, med, q3, max: " << to_string(stats_of(measures)) << endl;
        }
    };

    double stats(int L, int N, int S, int temp_range = -1, int s_margin = -1) {
        ResultList results;
        for (int t=1; t<=TESTS; ++t) {
            //if (t * 10 % TESTS == 0) cout << t << endl;
            const int l = (L == -1) ? L_dist(rng) : L;
            const int n = (N == -1) ? N_dist(rng) : N;
            const int s = (S == -1) ? square(sqrtS_dist(rng)) : S;

            assert(MIN_L <= l && l <= MAX_L);
            assert(MIN_N <= n && n <= MAX_N);
            assert(MIN_S <= s && s <= MAX_S);

            results.add_result(run_test(l, n, s, temp_range, s_margin));
        }
        results.print_stats(L, N, S, temp_range, s_margin);

        return results.stats_of(results.score)[0];
    }
}

const int TR = 15;
const int temps[TR] = {
    50, 75, 100, 125, 150,
    175, 200, 300, 400, 500,
    600, 700, 800, 900, 1000
};
const int MIN_SM = 1;
const int MAX_SM = 4;
double grid[TR][MAX_SM + 1];
void tuning_grid(int S) {
    for (int t = 0; t < TR; ++t) {
        for (int sm = MIN_SM; sm <= MAX_SM; ++sm) {
            grid[t][sm] = ((S * sm <= temps[t] || temps[t] >= 800) && S * 31000 >= square(temps[t]) ? Tester::stats(-1, -1, S, temps[t], sm) : -1);
        }
    }

    ofstream fout("tuning/" + to_string(S) + ".csv");
    assert(fout.is_open());
    fout << fixed << setprecision(3);
    fout << "tr";
    for (int sm = MIN_SM; sm <= MAX_SM; ++sm) {
        fout << ',' << sm;
    }
    fout << '\n';
    for (int t = 0; t < TR; ++t) {
        fout << temps[t];
        for (int sm = MIN_SM; sm <= MAX_SM; ++sm) {
            fout << ',' << grid[t][sm];
        }
        fout << '\n';
    }
    fout.close();
}

void finetuning() {
    assert(Tester::TESTS == 100);

    Tester::stats(-1, -1, 1, 75, 5);
    Tester::stats(-1, -1, 1, 100, 5);
    Tester::stats(-1, -1, 1, 100, 6);  // best
    Tester::stats(-1, -1, 1, 100, 7);
    Tester::stats(-1, -1, 1, 125, 5);
    Tester::stats(-1, -1, 1, 125, 6);
    Tester::stats(-1, -1, 1, 125, 7);
    Tester::stats(-1, -1, 1, 150, 6);
    Tester::stats(-1, -1, 1, 150, 7);

    Tester::stats(-1, -1, 4, 125, 5);
    Tester::stats(-1, -1, 4, 150, 5);
    Tester::stats(-1, -1, 4, 150, 6);
    Tester::stats(-1, -1, 4, 175, 5);
    Tester::stats(-1, -1, 4, 175, 6);
    Tester::stats(-1, -1, 4, 200, 5);  // best
    Tester::stats(-1, -1, 4, 200, 6);

    Tester::stats(-1, -1, 9, 175, 5);
    Tester::stats(-1, -1, 9, 200, 4);
    Tester::stats(-1, -1, 9, 200, 5);
    Tester::stats(-1, -1, 9, 300, 4);  // best
    Tester::stats(-1, -1, 9, 300, 5);

    Tester::stats(-1, -1, 16, 175, 2);
    Tester::stats(-1, -1, 16, 200, 2);
    Tester::stats(-1, -1, 16, 300, 2);  // best
    Tester::stats(-1, -1, 16, 300, 3);
    Tester::stats(-1, -1, 16, 300, 4);
    Tester::stats(-1, -1, 16, 400, 2);
    Tester::stats(-1, -1, 16, 400, 3);

    Tester::stats(-1, -1, 25, 300, 2);  // best
    Tester::stats(-1, -1, 25, 400, 2);
    Tester::stats(-1, -1, 25, 500, 2);

    Tester::stats(-1, -1, 36, 300, 2);  // best
    Tester::stats(-1, -1, 36, 400, 2);
    Tester::stats(-1, -1, 36, 500, 2);

    Tester::stats(-1, -1, 49, 400, 2);
    Tester::stats(-1, -1, 49, 500, 2);  // best
    Tester::stats(-1, -1, 49, 600, 2);

    Tester::stats(-1, -1, 64, 400, 2);
    Tester::stats(-1, -1, 64, 500, 2);
    Tester::stats(-1, -1, 64, 600, 2);  // best
    Tester::stats(-1, -1, 64, 700, 2);

    Tester::stats(-1, -1, 81, 500, 2);
    Tester::stats(-1, -1, 81, 600, 2);  // best

    Tester::stats(-1, -1, 100, 600, 2);
    Tester::stats(-1, -1, 100, 700, 2);
    Tester::stats(-1, -1, 100, 800, 2);  // best
    Tester::stats(-1, -1, 100, 900, 2);
    Tester::stats(-1, -1, 100, 1000, 2);

    Tester::stats(-1, -1, 121, 800, 2);  // best
    Tester::stats(-1, -1, 121, 900, 2);

    Tester::stats(-1, -1, 144, 400, 2);
    Tester::stats(-1, -1, 144, 500, 2);
    Tester::stats(-1, -1, 144, 600, 2);  // best
    Tester::stats(-1, -1, 144, 700, 2);
    Tester::stats(-1, -1, 144, 800, 2);
    Tester::stats(-1, -1, 144, 900, 2);
    Tester::stats(-1, -1, 144, 1000, 1);
    Tester::stats(-1, -1, 144, 1000, 2);

    Tester::stats(-1, -1, 169, 800, 2);  // best

    Tester::stats(-1, -1, 196, 400, 2);
    Tester::stats(-1, -1, 196, 500, 2);
    Tester::stats(-1, -1, 196, 600, 2);
    Tester::stats(-1, -1, 196, 700, 1);
    Tester::stats(-1, -1, 196, 700, 2);
    Tester::stats(-1, -1, 196, 800, 1);
    Tester::stats(-1, -1, 196, 800, 2);  // best
    Tester::stats(-1, -1, 196, 900, 1);
    Tester::stats(-1, -1, 196, 900, 2);
    Tester::stats(-1, -1, 196, 1000, 1);
    Tester::stats(-1, -1, 196, 1000, 2);
}

int main() {
    for (int i = 4; i <= 30; ++i) tuning_grid(i * i);
}

