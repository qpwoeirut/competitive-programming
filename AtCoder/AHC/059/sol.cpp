#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <cmath>
#include <cstdlib>
 
using namespace std;

const int N = 20;
const int MAX = 200;
const int MOVES = 5000;
int G[N][N];
const int LIMIT_OPS = 2 * N * N * N;

struct Params {
    double T0 = 200.0;
    double T1 = 1.0;
    double temp_alpha = 1.0;

    // Mutation chances (percent), must sum to 100.
    int p_swap = 30;
    int p_edit = 5;
    int p_insert = 5;
    int p_reverse = 40;
    int p_erase = 10;
    int p_pair_erase = 10;
};

static inline void normalize_probs(Params& p) {
    int sum = p.p_swap + p.p_edit + p.p_insert + p.p_reverse + p.p_erase + p.p_pair_erase;
    if (sum <= 0) {
        p = Params();
        return;
    }
    if (sum == 100) return;

    int raw[6] = {p.p_swap, p.p_edit, p.p_insert, p.p_reverse, p.p_erase, p.p_pair_erase};
    int scaled[6];
    int acc = 0;
    for (int i = 0; i < 6; i++) {
        scaled[i] = (raw[i] * 100) / sum;
        acc += scaled[i];
    }
    for (int k = 0; k < 100 - acc; k++) {
        int best = 0;
        for (int i = 1; i < 6; i++) if (raw[i] > raw[best]) best = i;
        scaled[best]++;
    }
    p.p_swap = scaled[0];
    p.p_edit = scaled[1];
    p.p_insert = scaled[2];
    p.p_reverse = scaled[3];
    p.p_erase = scaled[4];
    p.p_pair_erase = scaled[5];
}

static inline double temperature(const Params& p, double progress01) {
    double x = min(1.0, max(0.0, progress01));
    x = pow(x, p.temp_alpha);
    return p.T0 * pow(p.T1 / p.T0, x);
}

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
int mutate(const Params& p, int order[], int n_order) {
    if (n_order == 0) return n_order;

    // Probabilities are in percent and must sum to 100.
    int roll = rng.next_int(0, 99);
    int cut = 0;
    cut += p.p_swap;
    if (roll < cut) {
        int i = rng.next_int(0, n_order - 1);
        int j = rng.next_int(0, n_order - 1);
        swap(order[i], order[j]);
        return n_order;
    }
    cut += p.p_edit;
    if (roll < cut) {
        int i = rng.next_int(0, n_order - 1);
        int cell = rng.next_int(1, N * N);
        int sign = rng.next_int(0, 1) ? 1 : -1;
        order[i] = sign * cell;
        return n_order;
    }
    cut += p.p_insert;
    if (roll < cut) {
        if (n_order + 1 <= MOVES) {
            int i = rng.next_int(0, n_order - 1);
            int cell = rng.next_int(1, N * N);
            int sign = rng.next_int(0, 1) ? 1 : -1;
            n_order = insert(order, n_order, i, sign * cell);
        }
        return n_order;
    }
    cut += p.p_reverse;
    if (roll < cut) {
        int l = rng.next_int(0, n_order - 1);
        int rr = rng.next_int(0, n_order - 1);
        if (l > rr) swap(l, rr);
        reverse(order + l, order + rr + 1);
        return n_order;
    }
    cut += p.p_erase;
    if (roll < cut) {
        if (n_order > 1) {
            int idx = rng.next_int(0, n_order - 1);
            n_order = erase(order, n_order, idx);
        }
        return n_order;
    }

    // pair erase
    {
        int idx = rng.next_int(0, n_order - 1);
        int rev_idx = find(order, order + n_order, -order[idx]) - order;
        if (rev_idx < n_order) {
            if (idx > rev_idx) swap(idx, rev_idx);
            if (n_order > 2) {
                n_order = erase(order, n_order, idx);
                n_order = erase(order, n_order, rev_idx - 1);
            }
        }
    }
    return n_order;
}

const auto TIME_LIMIT = 1980ms;
const auto START_TIME = chrono::steady_clock::now();
const auto STOP_TIME = START_TIME + TIME_LIMIT;
int main(int argc, char** argv) {
    cin.tie(0)->sync_with_stdio(0);

    Params params;
    // Optional argv overrides:
    // argv[1]=T0 argv[2]=T1 argv[3]=temp_alpha
    // argv[4..9]=mutation probabilities (percent, should sum to 100)
    if (argc >= 2) params.T0 = atof(argv[1]);
    if (argc >= 3) params.T1 = atof(argv[2]);
    if (argc >= 4) params.temp_alpha = atof(argv[3]);
    if (argc >= 10) {
        params.p_swap = atoi(argv[4]);
        params.p_edit = atoi(argv[5]);
        params.p_insert = atoi(argv[6]);
        params.p_reverse = atoi(argv[7]);
        params.p_erase = atoi(argv[8]);
        params.p_pair_erase = atoi(argv[9]);
    }
    normalize_probs(params);

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

    int iter = 0, valid = 0;

    while (chrono::steady_clock::now() < STOP_TIME) {
        iter++;
        int cand_order[MOVES];
        int n_cand_order = n_cur_order;
        for (int i = 0; i < n_cur_order; i++) {
            cand_order[i] = cur_order[i];
        }
        n_cand_order = mutate(params, cand_order, n_cand_order);
        int cand_score = simulate(cand_order, n_cand_order);
        if (cand_score <= 0) continue;
        valid++;

        const double elapsed = chrono::duration<double>(chrono::steady_clock::now() - START_TIME).count();
        const double total = chrono::duration<double>(TIME_LIMIT).count();
        const double progress = min(1.0, elapsed / total);
        const double temp = temperature(params, progress);

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