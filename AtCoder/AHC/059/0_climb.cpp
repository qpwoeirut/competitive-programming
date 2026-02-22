#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <numeric>
 
using namespace std;

const int N = 20;
const int MAX = 200;
int G[N][N];
int position[MAX + 1][2];

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

inline int manhattan(int a, int b) {
    int ax = a / N, ay = a % N;
    int bx = b / N, by = b % N;
    return abs(ax - bx) + abs(ay - by);
}

int simulate(int order[]) {
    int cur = 0;
    int moves = 0;
    for (int i = 0; i < MAX; i++) {
        int x = order[i];
        int v = abs(x);
        assert(1 <= v && v <= MAX);
        int first = position[v][x > 0];
        int second = position[v][x < 0];
        moves += manhattan(cur, first) + manhattan(first, second);
        cur = second;
    }
    return N * N + 2 * N * N * N - moves;
}

string construct_answer(int order[]) {
    string out;
    out.reserve(20000);

    auto append_moves = [&](int from, int to) {
        int fx = from / N, fy = from % N;
        int tx = to / N, ty = to % N;
        while (fx < tx) { out += "D\n"; fx++; }
        while (fx > tx) { out += "U\n"; fx--; }
        while (fy < ty) { out += "R\n"; fy++; }
        while (fy > ty) { out += "L\n"; fy--; }
    };

    int cur = 0;
    for (int i = 0; i < MAX; i++) {
        int x = order[i];
        int v = abs(x);
        assert(1 <= v && v <= MAX);
        int first = position[v][x > 0];
        int second = position[v][x < 0];

        append_moves(cur, first);
        out += "Z\n";
        append_moves(first, second);
        out += "Z\n";
        cur = second;
    }

    return out;
}

XorShift64 rng;

// order is a list of values 1...MAX in some order, possibly negated
void mutate(int order[]) {
    int op = rng.next_int(0, 9);
    if (op <= 5) {
        int i = rng.next_int(0, MAX - 1);
        int j = rng.next_int(0, MAX - 1);
        swap(order[i], order[j]);
    } else if (op <= 8) {
        int l = rng.next_int(0, MAX - 1);
        int r = rng.next_int(0, MAX - 1);
        if (l > r) swap(l, r);
        reverse(order + l, order + r + 1);
    } else {
        int i = rng.next_int(0, MAX - 1);
        order[i] = -order[i];
    }
    if (rng.next_int(0, 3) == 0) {
        int i = rng.next_int(0, MAX - 1);
        order[i] = -order[i];
    }
}

auto STOP_TIME = chrono::steady_clock::now() + 1900ms;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    for (int v = 0; v <= MAX; v++) {
        position[v][0] = position[v][1] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> G[i][j];
            ++G[i][j];
            if (position[G[i][j]][0] == -1) {
                position[G[i][j]][0] = i * N + j;
            } else {
                position[G[i][j]][1] = i * N + j;
            }
        }
    }

    int best_order[MAX];
    iota(best_order, best_order + MAX, 1);
    int best_score = 0;
    while (chrono::steady_clock::now() < STOP_TIME) {
        int order[MAX];
        copy(best_order, best_order + MAX, order);
        mutate(order);

        const int score = simulate(order);
        if (score > best_score) {
            best_score = score;
            copy(order, order + MAX, best_order);
        }
    }

    cout << construct_answer(best_order) << endl;
    cerr << "Best score: " << best_score << endl;
}