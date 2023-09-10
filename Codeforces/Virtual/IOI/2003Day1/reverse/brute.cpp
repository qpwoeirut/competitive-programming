//brute.cpp created at 09/09/23 19:49:20

#include <bits/stdc++.h>

#pragma GCC optimize("O3,unroll-loops")

using namespace std;

const int INF = 2e9;
const int REGISTERS = 8;  // last register holds 0

//n: {2, 8, 12, 14}
//states: {256, 16777216, 429981696, 1475789056}
//npow
// 2: {1, 2, 4, 8, 16, 32, 64, 128}
// 8: {1, 8, 64, 512, 4096, 32768, 262144, 2097152}
// 12: {1, 12, 144, 1728, 20736, 248832, 2985984, 35831808}
// 14: {1, 14, 196, 2744, 38416, 537824, 7529536, 105413504}

const int N = 2;
const int STATES = 256;
const int NPOW[REGISTERS] = {1, 2, 4, 8, 16, 32, 64, 128};
int cost[N + 1][STATES];
int parent[N][STATES];

int tom[REGISTERS];
int tom_cpy[REGISTERS + 1];
void recurse(const int n, const int reg, const int state) {
        for (int i = 0; i < REGISTERS; ++i) {
            if (tom[i] == N - n - 1) {
                cost[n + 1][state] = 0;
                parent[n + 1][state] = state;
                return;
            }
        }
        if (cost[n][state] >= max_cost)
        for (int i = 0; i <= REGISTERS; ++i) {  // assume 0 is in R+1'th register
            for (int j = 0; j < REGISTERS; ++j) {
                tom_cpy[0] = tom[0];
                tom_cpy[1] = tom[1];
                tom_cpy[2] = tom[2];
                tom_cpy[3] = tom[3];
                tom_cpy[4] = tom[4];
                tom_cpy[5] = tom[5];
                tom_cpy[6] = tom[6];
                tom_cpy[7] = tom[7];
                
                tom_cpy[j] = tom_cpy[i] + 1;
                for (int k = j; k + 1 < REGISTERS && tom_cpy[k] > tom_cpy[k + 1]; ++k) swap(tom_cpy[k], tom_cpy[k + 1]);
                for (int k = j; k > 0 && tom_cpy[k - 1] > tom_cpy[k]; ++k) swap(tom_cpy[k - 1], tom_cpy[k]);

                const int new_state = 
                    tom_cpy[0] * NPOW[0] +
                    tom_cpy[1] * NPOW[1] +
                    tom_cpy[2] * NPOW[2] +
                    tom_cpy[3] * NPOW[3] +
                    tom_cpy[4] * NPOW[4] +
                    tom_cpy[5] * NPOW[5] +
                    tom_cpy[6] * NPOW[6] +
                    tom_cpy[7] * NPOW[7];
                if (cost[n][new_state] > cost[n][state] + 1) {
                    cost[n][new_state] = cost[n][state] + 1;
                    parent[n][new_state] = state;
                }
            }
        }
        return;
}

bool check_max_cost(const int max_cost) {
    for (int i = 0; i <= N; ++i) {
        fill(cost[i], cost[i]+STATES, i == 0 ? 0 : INF);
    }
    for (int state = 0; state < STATES; ++state) {
        parent[0][state] = state;
    }

    for (int n = 0; n < N; ++n) {
        recurse(n, max_cost, 0, 0);
    }
    int state = min_element(cost[N], cost[N] + STATES) - cost[N];
    return cost[N][state] < INF;
}

int arr1[REGISTERS], arr2[REGISTERS];
int arr_tmp[REGISTERS + 1];
int find_add(int old_state, int new_state) {
    for (int i = 0; i < REGISTERS; ++i) {
        arr1[i] = old_state % N;
        arr2[i] = new_state % N;
        old_state /= N;
        new_state /= N;
    }
    for (int i = 0; i <= REGISTERS; ++i) {
        for (int j = 0; j < REGISTERS; ++j) {
            copy(arr1, arr1 + REGISTERS, arr_tmp);
            arr_tmp[j] = arr_tmp[i] + 1;
            sort(arr_tmp, arr_tmp + REGISTERS);
            if (equal(arr_tmp, arr_tmp + REGISTERS, arr2)) {
                return i * N + j;
            }
        }
    }
    assert(0);
}

int main() {
    int lo = 1, hi = (N + 7) / 8;
    while (lo < hi) {
        const int max_cost = (lo + hi + 1) / 2;
        if (find_answer(max_cost)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    const bool success = check_max_cost(lo);
    assert(success);

    vector<int> answer;
    for (int n = N; n >= 0; --n) {
        while (parent[n][state] != state) {
            answer.push_back(find_add(parent[n][state], state));
            state = parent[n][state];
        }
        if (n > 0) answer.push_back(-find_print(state, N - n));
        else answer.push_back(-REGISTERS);
    }
    reverse(answer.begin(), answer.end());
    
    for (int i = 0; i <= REGISTERS; ++i) {
        cout << state % N << ' ';
        state /= N;
    }
    cout << "0\n";

    for (const int action: answer) {
        if (action < 0) {
            cout << "S " << -action + 1 << '\n';
        } else {
            const int i = action / N;
            const int j = action % N;
            cout << "P " << i + 1 << ' ' << j + 1 << '\n';
        }
    }
}

