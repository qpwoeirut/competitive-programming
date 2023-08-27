#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

const int MAXL = 50;
const int MAXN = 100;
const int MAX_TEMP = 1000;

#ifndef USING_TESTER
// avoid using virtual functions because they cause performance hit
struct Judge {
    const int L, N, S;
    Judge(int L, int N, int S) : L(L), N(N), S(S) {}

    void set_temperature(const int temperature[MAXL][MAXL]) {
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

    void answer(const int estimate[MAXN]) {
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

const int TEMP_ITERS = 10000;
const int TRIALS = 100;

struct Solver {
    const int L, N, S;
    const array<pii, MAXN> landing_pos;
    Judge judge;

    int G[MAXL][MAXL];
    bitset<MAXN> picked[MAXN];
    int estimate[MAXN];

    Solver(int L, int N, int S, const array<pii, MAXN>& landing_pos) : 
        L(L), N(N), S(S), landing_pos(landing_pos), judge(L, N, S) {
            for (int r = 0; r < L; ++r) {
                picked[r].reset();
                for (int c = 0; c < L; ++c) {
                    G[r][c] = 500;
                }
            }
            fill(estimate, estimate+N, 0);
#ifdef USING_TESTER
            judge.set_landing_pos(landing_pos);
#endif
    }

    void solve() {
        create_temperature();
        judge.set_temperature(G);
        predict();
        judge.answer(estimate);
    }

    void create_temperature() {
        const int spacing = MAX_TEMP / (N - 1);
        const int extra = MAX_TEMP % (N - 1);
        for (int i = 0; i < N; i++) {
            G[landing_pos[i].first][landing_pos[i].second] = S * 3 <= spacing ? i * S * 3 : i * spacing + (extra / 2);
            picked[landing_pos[i].first][landing_pos[i].second] = true;
        }

        for (int i=0; i<TEMP_ITERS; ++i) {
            bool changed = false;
            for (int r=0; r<L; ++r) {
                for (int c=0; c<L; ++c) {
                    if (!picked[r][c]) {
                        const int new_val = (G[(r+L-1)%L][c] + G[r][(c+L-1)%L] + G[(r+1)%L][c] + G[r][(c+1)%L] + 2) / 4;
                        if (G[r][c] != new_val) {
                            G[r][c] = new_val;
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

    void predict() {
        for (int i_in = 0; i_in < N; i_in++) {
            int measurement_sum = 0;
            for (int trials = 0; trials < TRIALS; ++trials) {
                measurement_sum += judge.measure(i_in, 0, 0);
            }
            const double measured_value = (double)(measurement_sum) / TRIALS;

            double min_diff = 1e9;
            for (int i_out = 0; i_out < N; i_out++) {
                const pii& pos = landing_pos[i_out];
                const double diff = abs(G[pos.first][pos.second] - measured_value);
                if (min_diff > diff) {
                    min_diff = diff;
                    estimate[i_in] = i_out;
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
    array<pii, MAXN> landing_pos;
    for (int i = 0; i < N; i++) {
        cin >> landing_pos[i].first >> landing_pos[i].second;
    }

    Solver solver(L, N, S, landing_pos);
    solver.solve();
}
#endif

/*
TESTS = 100000. L = -1, N = -1, S = -1.
scores      mean, stddev, stderr, min, q1, med, q3, max: [966578.165860 2455357.431046 7764.521952 1.000000 1.000000 4.000000 6642.000000 15653274.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [53.742390 31.449516 0.099452 0.000000 29.000000 63.000000 78.000000 100.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [15751289.715140 5097616.426240 16120.078545 288440.000000 12792766.000000 15436646.000000 18562166.000000 40763166.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [8003033.000000 1182889.471130 3740.624949 6000000.000000 7000000.000000 8000000.000000 9000000.000000 10000000.000000]

old
TESTS = 100000. L = -1, N = -1, S = -1.
scores      mean, stddev, stderr, min, q1, med, q3, max: [963733.263290 2591819.787929 8196.053815 1.000000 1.000000 5.000000 1792.000000 15653274.000000]
W           mean, stddev, stderr, min, q1, med, q3, max: [55.310390 30.220003 0.095564 0.000000 36.000000 63.000000 78.000000 100.000000]
placement   mean, stddev, stderr, min, q1, med, q3, max: [11524930.585920 6123740.322323 19364.967218 288440.000000 6664342.000000 10496728.000000 15613624.000000 40763166.000000]
measurement mean, stddev, stderr, min, q1, med, q3, max: [8003033.000000 1182889.471130 3740.624949 6000000.000000 7000000.000000 8000000.000000 9000000.000000 10000000.000000]
      128.29 real       127.90 user         0.11 sys
*/
