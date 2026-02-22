#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <cmath>
 
using namespace std;

const int N = 20;
const int MAX = 200;
const int MOVES = 5000;
int G[N][N];
const int LIMIT_OPS = 2 * N * N * N;

struct XorShift64 {
    uint64_t x = 88172645463393265ull;
    inline uint64_t next_u64() { x ^= x << 7; x ^= x >> 9; return x; }
    inline uint32_t next_u32() { return (uint32_t)next_u64(); }
    inline int next_int(int lo, int hi) {
        return lo + (int)(next_u32() % (uint32_t)(hi - lo + 1));
    }
    inline double next_double01() {
        uint64_t r = next_u64();
        r = (r >> 11) | 1ULL; 
        return (double)r * (1.0 / 9007199254740992.0);
    }
};

inline int insert(int arr[], int n, int pos, int val) {
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = val;
    return n + 1;
}

inline int erase(int arr[], int n, int pos) {
    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    return n - 1;
}

inline int find_value(int a[][N], int val) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (a[i][j] == val) {
                return i * N + j;
            }
        }
    }
    return -1;
}

inline int manhattan(int a, int b) {
    int ax = a / N, ay = a % N;
    int bx = b / N, by = b % N;
    return abs(ax - bx) + abs(ay - by);
}

int initial_solution(int order[]) {
    int pos[MAX][2];
    for (int i = 0; i < MAX; i++) {
        pos[i][0] = -1;
        pos[i][1] = -1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (pos[G[i][j] - 1][0] == -1) {
                pos[G[i][j] - 1][0] = i * N + j;
            } else {
                pos[G[i][j] - 1][1] = i * N + j;
            }
        }
    }
    
    int n = 0;
    for (int i = 0; i < MAX; i++) {
        order[n++] = pos[i][0] + 1;
        order[n++] = pos[i][1] + 1;
    }
    return n;
}

const int INVALID = -1000000000;
int simulate(int order[], int n_order) {
    int A[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = G[i][j];
        }
    }

    int deck[N * N];
    int n_deck = 0;

    int cur = 0;
    int moves = 0;

    for (int t = 0; t < n_order; t++) {
        int act = order[t];
        if (act == 0) {
            if (n_deck == 0) return INVALID;
            act = find_value(A, deck[n_deck - 1]) + 1;
            if (act == 0) return INVALID;
        }
        int cell = abs(act);
        assert(1 <= cell && cell <= N * N);

        int pos = cell - 1;
        int r = pos / N;
        int c = pos % N;

        moves += manhattan(cur, pos);
        cur = pos;

        if (act > 0) {
            if (A[r][c] == 0) return INVALID;
            deck[n_deck++] = A[r][c];
            A[r][c] = 0;
            if (n_deck >= 2 && deck[n_deck - 1] == deck[n_deck - 2]) {
                n_deck -= 2;
            }
        } else {
            if (A[r][c] != 0) return INVALID;
            if (n_deck == 0) return INVALID;
            A[r][c] = deck[--n_deck];
        }
    }

    int X = n_deck;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != 0) X++;
        }
    }

    if (X == 0) return N * N + LIMIT_OPS - moves;
    return N * N - X;
}

string construct_answer(int order[], int n_order) {
    int A[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = G[i][j];
        }
    }

    string out;
    out.reserve(2 * LIMIT_OPS);

    auto append_moves = [&](int from, int to) {
        int fr = from / N, fc = from % N;
        int tr = to / N, tc = to % N;
        while (fr < tr) { out += "D\n"; fr++; }
        while (fr > tr) { out += "U\n"; fr--; }
        while (fc < tc) { out += "R\n"; fc++; }
        while (fc > tc) { out += "L\n"; fc--; }
    };

    int deck[N * N];
    int n_deck = 0;
    int cur = 0;
    for (int t = 0; t < n_order; t++) {
        int act = order[t];
        if (act == 0) {
            assert(n_deck > 0);
            act = find_value(A, deck[n_deck - 1]) + 1;
            assert(act > 0);
        }
        int cell = abs(act);
        assert(1 <= cell && cell <= N * N);
        int pos = cell - 1;

        int r = pos / N;
        int c = pos % N;

        append_moves(cur, pos);
        if (act > 0) {
            assert(A[r][c] != 0);
            deck[n_deck++] = A[r][c];
            A[r][c] = 0;
            if (n_deck >= 2 && deck[n_deck - 1] == deck[n_deck - 2]) {
                n_deck -= 2;
            }
        } else {
            assert(A[r][c] == 0);
            A[r][c] = deck[--n_deck];
        }
        out += (act > 0 ? "Z\n" : "X\n");
        cur = pos;
    }

    return out;
}

XorShift64 rng;

// order is a list of actions (+cell = pick, -cell = place), cell in 1..N*N
int mutate(int order[], int n_order) {
    int op = n_order == 0 ? 35 : rng.next_int(0, 99);
    if (op < 15) {
        int i = rng.next_int(0, n_order - 1);
        int j = rng.next_int(0, n_order - 1);
        swap(order[i], order[j]);
    } else if (op < 18) {
        int i = rng.next_int(0, n_order - 1);
        int cell = rng.next_int(1, N * N);
        int sign = rng.next_int(0, 1) ? 1 : -1;
        order[i] = sign * cell;
    } else if (op < 26) {
        int i = rng.next_int(0, n_order - 1);
        int cell = rng.next_int(1, N * N);
        int sign = rng.next_int(0, 1) ? 1 : -1;
        n_order = insert(order, n_order, i, sign * cell);
    } else if (op < 74) {
        int l = rng.next_int(0, n_order - 1);
        int r = rng.next_int(0, n_order - 1);
        if (l > r) swap(l, r);
        reverse(order + l, order + r + 1);
    } else if (op < 94) {
        int idx = rng.next_int(0, n_order - 1);
        n_order = erase(order, n_order, idx);
    } else {
        int idx = rng.next_int(0, n_order - 1);
        int rev_idx = find(order, order + n_order, -order[idx]) - order;
        if (rev_idx < n_order) {
            if (idx > rev_idx) swap(idx, rev_idx);
            n_order = erase(order, n_order, idx);
            n_order = erase(order, n_order, rev_idx - 1);
        }
    }
    return n_order;
}

const auto TIME_LIMIT = 1980ms;
const auto START_TIME = chrono::steady_clock::now();
const auto STOP_TIME = START_TIME + TIME_LIMIT;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> G[i][j];
            G[i][j]++;
        }
    }

    int cur_order[MOVES];
    int n_cur_order = initial_solution(cur_order);
    int cur_score = simulate(cur_order, n_cur_order);
    
    int best_order[MOVES];
    int n_best_order = n_cur_order;
    int best_score = cur_score;

    const double T0 = 150.0;
    const double T1 = 1.0;
    int iter = 0, valid = 0;

    while (chrono::steady_clock::now() < STOP_TIME) {
        iter++;
        int cand_order[MOVES];
        int n_cand_order = n_cur_order;
        for (int i = 0; i < n_cur_order; i++) {
            cand_order[i] = cur_order[i];
        }
        n_cand_order = mutate(cand_order, n_cand_order);
        int cand_score = simulate(cand_order, n_cand_order);
        if (cand_score <= 0) continue;
        valid++;

        const double elapsed = chrono::duration<double>(chrono::steady_clock::now() - START_TIME).count();
        const double total = chrono::duration<double>(TIME_LIMIT).count();
        const double progress = min(1.0, elapsed / total);
        const double temp = T0 * pow(T1 / T0, progress);

        const int delta = cand_score - cur_score;
        bool accept = false;
        if (delta >= 0) {
            accept = true;
        } else {
            const double prob = exp((double)delta / temp);
            accept = (rng.next_double01() < prob);
        }

        if (accept) {
            copy(cand_order, cand_order + n_cand_order, cur_order);
            n_cur_order = n_cand_order;
            cur_score = cand_score;
        }

        if (cand_score > best_score) {
            best_score = cand_score;
            copy(cand_order, cand_order + n_cand_order, best_order);
            n_best_order = n_cand_order;
        }
    }

    cout << construct_answer(best_order, n_best_order) << endl;
    cerr << "Best score: " << best_score << " (iter=" << iter << ", valid=" << valid << ")" << endl;
}