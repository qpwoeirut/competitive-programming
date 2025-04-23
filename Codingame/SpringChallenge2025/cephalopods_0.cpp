#pragma GCC target("tune=native")
#pragma GCC optimize("Ofast,omit-frame-pointer")

#include <iostream>
#include <array>
#include <bit>
#include <unordered_map>

using namespace std;

const int N_TRIPLE = 4;
const int N_QUAD = 11;
const int MASK = 0x3fffffff;

uint32_t solve(int, int);

consteval array<int, 1 << 6> calculate_double_moves() {
    array<int, 1 << 6> moves({});
    for (int val_a = 0; val_a <= 6; ++val_a) {
        for (int val_b = 0; val_b <= 6; ++val_b) {
            const int val = (val_a << 3) | val_b;
            if (val_a > 0 && val_b > 0 && val_a + val_b <= 6) {
                moves[val] = (val_a + val_b) << 6;
            } else {
                moves[val] = (1 << 6) | (val_a << 3) | val_b;
            }
        }
    }
    return moves;
}
constexpr const array<int, 1 << 6> double_moves = calculate_double_moves();

uint32_t double_move(const int old, const int x, const int a, const int b, const int depth) {
    if ((old >> x) & 7) return 0;
    const int val_a = (old >> a) & 7;
    const int val_b = (old >> b) & 7;
    const int move = double_moves[(val_a << 3) | val_b];
    return solve(
        (old ^ (val_a << a) ^ (val_b << b)) | 
        (((move >> 6)    ) << x) |
        (((move >> 3) & 7) << a) |
        (( move       & 7) << b),
        depth - 1
    );
}

consteval array<array<int, N_TRIPLE>, 1 << 9> calculate_triple_moves() {
    array<array<int, N_TRIPLE>, 1 << 9> moves({});
    for (int val_a = 0; val_a <= 6; ++val_a) {
        for (int val_b = 0; val_b <= 6; ++val_b) {
            for (int val_c = 0; val_c <= 6; ++val_c) {
                const int val = (val_a << 6) | (val_b << 3) | val_c;
                moves[val].fill(-1);

                const array<int, 3> vals({val_a, val_b, val_c});
                int i = 0;
                for (unsigned mask = 0; mask < (1 << 3); ++mask) {
                    if (popcount(mask) < 2) continue;
                    int sum = 0; for (int j = 0; j < 3; ++j) if ((mask >> j) & 1) sum += vals[j] == 0 ? 7 : vals[j];
                    if (sum <= 6) {
                        moves[val][i] = sum << 9;
                        for (int j = 0; j < 3; ++j) if (((mask >> j) & 1) == 0) moves[val][i] |= vals[j] << (3 * (2 - j));
                        ++i;
                    }
                }
                if (i == 0) {
                    moves[val][i++] = (1 << 9) | (val_a << 6) | (val_b << 3) | val_c;
                }
            }
        }
    }
    return moves;
}
constexpr const array<array<int, N_TRIPLE>, 1 << 9> triple_moves = calculate_triple_moves();

uint32_t triple_move(const int old, const int x, const int a, const int b, const int c, const int depth) {
    if ((old >> x) & 7) return 0;
    const int val_a = (old >> a) & 7;
    const int val_b = (old >> b) & 7;
    const int val_c = (old >> c) & 7;
    const int val = (val_a << 6) | (val_b << 3) | val_c;
    const int cleared_board = old ^ (val_a << a) ^ (val_b << b) ^ (val_c << c);

    uint32_t sum = 0;
    for (int i = 0; i < N_TRIPLE; ++i) {
        const int move = triple_moves[val][i];
        if (move == -1) break;
        sum += solve(
            cleared_board | 
            (((move >> 9)    ) << x) |
            (((move >> 6) & 7) << a) |
            (((move >> 3) & 7) << b) |
            (( move       & 7) << c),
            depth - 1
        );
    }
    return sum;
}

consteval array<array<int, N_QUAD>, 1 << 12> calculate_quad_moves() {
    array<array<int, N_QUAD>, 1 << 12> moves({});
    for (int val_a = 0; val_a <= 6; ++val_a) {
        for (int val_b = 0; val_b <= 6; ++val_b) {
            for (int val_c = 0; val_c <= 6; ++val_c) {
                for (int val_d = 0; val_d <= 6; ++val_d) {
                    const int val = (val_a << 9) | (val_b << 6) | (val_c << 3) | val_d;
                    moves[val].fill(-1);
    
                    const array<int, 4> vals({val_a, val_b, val_c, val_d});
                    int i = 0;
                    for (unsigned mask = 0; mask < (1 << 4); ++mask) {
                        if (popcount(mask) < 2) continue;
                        int sum = 0; for (int j = 0; j < 4; ++j) if ((mask >> j) & 1) sum += vals[j] == 0 ? 7 : vals[j];
                        if (sum <= 6) {
                            moves[val][i] = sum << 12;
                            for (int j = 0; j < 4; ++j) if (((mask >> j) & 1) == 0) moves[val][i] |= vals[j] << (3 * (3 - j));
                            ++i;
                        }
                    }
                    if (i == 0) {
                        moves[val][i++] = (1 << 12) | (val_a << 9) | (val_b << 6) | (val_c << 3) | val_d;
                    }
                }
            }
        }
    }
    return moves;
}

constexpr const array<array<int, N_QUAD>, 1 << 12> quad_moves = calculate_quad_moves();

uint32_t quad_move(const int old, const int x, const int a, const int b, const int c, const int d, const int depth) {
    if ((old >> x) & 7) return 0;
    const int val_a = (old >> a) & 7;
    const int val_b = (old >> b) & 7;
    const int val_c = (old >> c) & 7;
    const int val_d = (old >> d) & 7;
    const int val = (val_a << 9) | (val_b << 6) | (val_c << 3) | val_d;
    const int cleared_board = old ^ (val_a << a) ^ (val_b << b) ^ (val_c << c) ^ (val_d << d);

    uint32_t sum = 0;
    for (int i = 0; i < N_QUAD; ++i) {
        const int move = quad_moves[val][i];
        if (move == -1) break;
        sum += solve(
            cleared_board | 
            (((move >> 12)    ) << x) |
            (((move >>  9) & 7) << a) |
            (((move >>  6) & 7) << b) |
            (((move >>  3) & 7) << c) |
            (( move        & 7) << d),
            depth - 1
        );
    }
    return sum;
}

unordered_map<int, uint32_t> table[41];

uint32_t solve(const int board, const int depth) {
    //cerr << depth << '\n' << dump(board) << endl;
    if (depth == 0 || (
        ((board >> 24)    ) > 0 && ((board >> 21) & 7) > 0 && ((board >> 18) & 7) > 0 &&
        ((board >> 15) & 7) > 0 && ((board >> 12) & 7) > 0 && ((board >>  9) & 7) > 0 &&
        ((board >>  6) & 7) > 0 && ((board >>  3) & 7) > 0 && ( board        & 7) > 0
    )) {
        return
            ((board >> 24)    ) * 100000000 +
            ((board >> 21) & 7) * 10000000 +
            ((board >> 18) & 7) * 1000000 +
            ((board >> 15) & 7) * 100000 +
            ((board >> 12) & 7) * 10000 +
            ((board >>  9) & 7) * 1000 +
            ((board >>  6) & 7) * 100 +
            ((board >>  3) & 7) * 10 +
             (board        & 7);
    }
    const auto it = table[depth].find(board);
    if (it != table[depth].end()) {
        return it->second;
    }

    return table[depth][board] = (
        double_move(board, 0, 3, 9, depth) +
        double_move(board, 6, 3, 15, depth) +
        double_move(board, 18, 9, 21, depth) +
        double_move(board, 24, 15, 21, depth) +
        triple_move(board, 3, 0, 6, 12, depth) +
        triple_move(board, 9, 0, 12, 18, depth) +
        triple_move(board, 15, 6, 12, 24, depth) +
        triple_move(board, 21, 12, 18, 24, depth) +
        quad_move(board, 12, 3, 9, 15, 21, depth)
    ) & MASK;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int d = 1; d <= 30; ++d) {
        table[d].reserve(100000);
    }

    int depth;
    cin >> depth;

    int board = 0;
    for (int i = 0; i < 9; i++) {
        int value;
        cin >> value;
        board = (board << 3) | value;
    }

    cout << solve(board, depth) << '\n';
}

