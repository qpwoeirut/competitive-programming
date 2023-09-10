//shift.cpp created at 09/09/23 23:06:35

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;

const int N_ARR[17] = {0, 2, 8, 12, 14, 26, 33, 44, 50, 75, 97, 112, 140, 173, 200, 240, 255};
const int REGISTERS = 9;

int max_le(const array<int, REGISTERS>& arr, const int x) {
    int idx = -1;
    int val = -1;
    for (int i = 0; i < arr.size(); ++i) {
        if (val < arr[i] && arr[i] <= x) {
            val = arr[i];
            idx = i;
        }
    }
    return idx;
}
int min_gt(const array<int, REGISTERS>& arr, const int x) {
    int idx = -1;
    int val = x + 1;
    for (int i = 0; i < arr.size(); ++i) {
        if (val > arr[i] && arr[i] > x) {
            val = arr[i];
            idx = i;
        }
    }
    return idx;
}

bool try_spacing(const int N, const int target, array<int, REGISTERS>& initial, vector<pii>& answer) {
    cerr << N << ' ' << target << endl;
    initial.fill(-1);
    answer.clear();

    array<int, REGISTERS> tom;
    bool ok = true;

    int ops_left = 0;
    int extra = 0;
    const auto s_op = [&](const int i, const int j) {
        tom[j] = tom[i] + 1;
        answer.emplace_back(i, j);
        --ops_left;
        if (ops_left < 0) ok = false;
    };
    const auto p_op = [&](const int i) {
        answer.emplace_back(-1, i);
        extra += ops_left;
        ops_left = target;
    };

    initial[0] = N;
    initial[1] = 0;
    tom[0] = N;
    tom[1] = 0;
    for (int n = N; n >= 0 && ok; --n) {
        int idx = max_le(initial, n);
        assert(0 <= idx);
        if (n - tom[idx] > target) {
            int neg = find(initial.begin(), initial.end(), -1) - initial.begin();
            if (neg < REGISTERS) {
                initial[neg] = tom[neg] = n - target;
            } else {
                ok = false;
                break;
            }
            idx = neg;
        }
        if (tom[idx] == n) {
            p_op(idx);
            continue;
        }
        if (tom[0] > n || tom[0] < tom[idx]) {
            s_op(idx, 0);
        }
        while (tom[0] < n) {
            s_op(0, 0);
        }
        p_op(0);
    }
    return ok;
}
void solve(const int N, array<int, REGISTERS>& initial, vector<pii>& answer) {
    int lo = 1, hi = N;
    while (lo < hi) {
        const int mid = (lo + hi) / 2;
        if (try_spacing(N, mid, initial, answer)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    try_spacing(N, lo, initial, answer);
}

int main() {
    for (int test = 1; test <= 16; ++test) {
        cerr << "test = " << test << endl;

        const int N = N_ARR[test];
        const string FILENAME = (test < 10 ? "0" : "") + to_string(test) + ".out";
        ofstream fout("out/" + FILENAME);
        assert(fout.is_open());

        array<int, REGISTERS> initial;
        vector<pii> answer;

        solve(N, initial, answer);

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
}

