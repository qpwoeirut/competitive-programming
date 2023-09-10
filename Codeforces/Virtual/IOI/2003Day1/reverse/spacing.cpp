//spacing.cpp created at 09/09/23 22:37:37

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;

const int N_ARR[17] = {0, 2, 8, 12, 14, 26, 33, 44, 50, 75, 97, 112, 140, 173, 200, 240, 255};
const int REGISTERS = 9;

int initial[REGISTERS];
int tom[REGISTERS];

void s_op(const int i, const int j, vector<pii>& answer) {
    tom[j] = tom[i] + 1;
    answer.emplace_back(i, j);
}
void p_op(const int i, vector<pii>& answer) {
    answer.emplace_back(-1, i);
}

void solve(int TEST) {
    cerr << "TEST = " << TEST << endl;

    const int N = N_ARR[TEST];

    const string FILENAME = (TEST < 10 ? "0" : "") + to_string(TEST) + ".out";
    ofstream fout("out/" + FILENAME);
    assert(fout.is_open());

    for (int i = 0; i < REGISTERS; ++i) {
        initial[i] = tom[i] = i * N / (REGISTERS - 1);
    }

    vector<pii> answer;
    for (int n = N; n >= 0; --n) {
        const int idx = (upper_bound(tom, tom + REGISTERS - 1, n) - tom) - 1;
        assert(0 <= idx);
        if (tom[idx] == n) {
            p_op(idx, answer);
            continue;
        }
        if (tom[REGISTERS - 1] > n || tom[REGISTERS - 1] < tom[idx]) {
            s_op(idx, REGISTERS - 1, answer);
        }
        while (tom[REGISTERS - 1] < n) {
            s_op(REGISTERS - 1, REGISTERS - 1, answer);
        }
        p_op(REGISTERS - 1, answer);
    }

    for (int i = 0; i < REGISTERS; ++i) {
        if (i) fout << ' ';
        fout << initial[i];
    }
    fout << '\n';
    for (const pii& p: answer) {
        if (p.first == -1) {
            fout << "P " << p.second + 1 << '\n';
        } else {
            fout << "S " << p.first + 1 << ' ' << p.second + 1 << '\n';
        }
    }
    fout.close();
}

int main() {
    for (int i = 1; i <= 16; ++i) {
        solve(i);
    }
}

