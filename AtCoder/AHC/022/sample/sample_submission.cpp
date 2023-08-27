#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Pos {
    int y, x;
};

struct Judge {
    void set_temperature(const vector<vector<int>>& temperature) {
        for (const vector<int>& row : temperature) {
            for (int i = 0; i < row.size(); i++) {
                cout << row[i] << (i == row.size() - 1 ? "\n" : " ");
            }
        }
        cout.flush();
    }

    int measure(int i, int y, int x) {
        cout << i << " " << y << " " << x << endl; // endl does flush
        int v;
        cin >> v;
        if (v == -1) {
            cerr << "something went wrong. i=" << i << " y=" << y << " x=" << x << endl;
            exit(1);
        }
        return v;
    }

    void answer(const vector<int>& estimate) {
        cout << "-1 -1 -1" << endl;
        for (int e : estimate) {
            cout << e << endl;
        }
    }
};

struct Solver {
    const int L;
    const int N;
    const int S;
    const vector<Pos> landing_pos;
    Judge judge;

    Solver(int L, int N, int S, const vector<Pos>& landing_pos) : 
        L(L), N(N), S(S), landing_pos(landing_pos), judge() {
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
            temperature[landing_pos[i].y][landing_pos[i].x] = i * 10;
        }
        return temperature;
    }

    vector<int> predict(const vector<vector<int>>& temperature) {
        vector<int> estimate(N);
        for (int i_in = 0; i_in < N; i_in++) {
            // you can output comment
            cout << "# measure i=" << i_in << " y=0 x=0" << endl;

            int measured_value = judge.measure(i_in, 0, 0);
            // answer the position with the temperature closest to the measured value
            int min_diff = 9999;
            for (int i_out = 0; i_out < N; i_out++) {
                const Pos& pos = landing_pos[i_out];
                int diff = abs(temperature[pos.y][pos.x] - measured_value);
                if (diff < min_diff) {
                    min_diff = diff;
                    estimate[i_in] = i_out;
                }
            }
        }
        return estimate;
    }
};

int main() {
    int L, N, S;
    cin >> L >> N >> S;
    vector<Pos> landing_pos(N);
    for (int i = 0; i < N; i++) {
        cin >> landing_pos[i].y >> landing_pos[i].x;
    }

    Solver solver(L, N, S, landing_pos);
    solver.solve();
}
