#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;
#define fi first
#define se second

#ifndef USING_TESTER
// avoid using virtual functions because they cause performance hit
struct Judge {
    const int L, N, S;
    Judge(int L, int N, int S) : L(L), N(N), S(S) {}

    void set_temperature(const vector<vector<int>>& temperature) {
        for (const vector<int>& row : temperature) {
            for (int i = 0; i < row.size(); i++) {
                cout << row[i] << (i+1 == row.size() ? "\n" : " ");
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
            cerr << "something went wrong. i=" << i << " y=" << y << " x=" << x << endl;
            exit(1);
        }
        return v;
    }

    void answer(const vector<int>& estimate) {
        cout << "-1 -1 -1\n";
        for (int e : estimate) {
            cout << e << '\n';
        }
        cout.flush();
    }
};
#else
using Judge=Tester::Judge;
#endif

struct Solver {
    const int L;
    const int N;
    const int S;
    const vector<pii> landing_pos;
    Judge judge;

    Solver(int L, int N, int S, const vector<pii>& landing_pos) : 
        L(L), N(N), S(S), landing_pos(landing_pos), judge(L, N, S) {
#ifdef USING_TESTER
            judge.set_landing_pos(landing_pos);
#endif
    }

    void solve() {
        const vector<vector<int>> temperature = create_temperature();
        judge.set_temperature(temperature);
        const vector<int> estimate = predict(temperature);
        judge.answer(estimate);
    }

    vector<vector<int>> create_temperature() {
        vector<vector<int>> temperature(L, vector<int>(L, 0));
        // set the temperature to i * 10 for i-th position
        for (int i = 0; i < N; i++) {
            temperature[landing_pos[i].first][landing_pos[i].second] = i * 10;
        }
        return temperature;
    }

    vector<int> predict(const vector<vector<int>>& temperature) {
        vector<int> estimate(N);
        for (int i_in = 0; i_in < N; i_in++) {
            int measured_value = judge.measure(i_in, 0, 0);
            // answer the position with the temperature closest to the measured value
            int min_diff = 9999;
            for (int i_out = 0; i_out < N; i_out++) {
                const pii& pos = landing_pos[i_out];
                int diff = abs(temperature[pos.first][pos.second] - measured_value);
                if (diff < min_diff) {
                    min_diff = diff;
                    estimate[i_in] = i_out;
                }
            }
        }
        return estimate;
    }
};

#ifndef USING_TESTER
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int L, N, S;
    cin >> L >> N >> S;
    vector<pii> landing_pos(N);
    for (int i = 0; i < N; i++) {
        cin >> landing_pos[i].first >> landing_pos[i].second;
    }

    Solver solver(L, N, S, landing_pos);
    solver.solve();
}
#endif

