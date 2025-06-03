#include <iostream>
#include <unordered_set>
#include <utility>

const char EMPTY = '.';
const char INVALID = '#';
const char W_PAWN = 'E';
const char B_PAWN = 'P';
const char B_KNIGHT = 'N';
const char B_BISHOP = 'B';
const char B_ROOK = 'R';
const char B_KING = 'K';
const char B_QUEEN = 'Q';

const int W_MOVE = 1;
const int B_MOVE = 2;

const int MAX_H = 20;
const int W = 8;

struct Move {
    int r1, c1;
    int r2, c2;
    char piece;
    char target;

    Move() {}
    Move(const std::pair<int, int>& p, const int dr, const int dc, const char _piece, const char _target) : r1(p.first), c1(p.second), r2(p.first + dr), c2(p.second + dc), piece(_piece), target(_target) {}

    friend std::ostream& operator<<(std::ostream& os, const Move& move) {
        os << move.r1 << ' ' << move.c1 << ' ' << move.r2 << ' ' << move.c2;
        return os;
    }
};

struct pair_hash {
    int operator()(const std::pair<int, int>& p) const {
        return (p.first << 10) | p.second;
    }
};

struct Board {
    const int H;

    char G[MAX_H + 4][W + 4];
    int defs[MAX_H + 4][W + 4];
    std::unordered_set<std::pair<int, int>, pair_hash> white, black;

    Board(const int _H) : H(_H) {
        for (int r = 0; r < H + 4; ++r) {
            for (int c = 0; c < W + 4; ++c) {
                G[r][c] = INVALID;
                defs[r][c] = 0;
            }
        }
        white.clear();
        black.clear();
    }

    void read_in(std::istream& in) {
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                char ch;
                in >> ch;
                set_square(r, c, ch);
            }
        }
    }

    void set_square(const int r, const int c, const char val) {
        if (G[r + 2][c + 2] == W_PAWN) {
            --defs[r + 3][c + 1];
            --defs[r + 3][c + 3];
        }
        G[r + 2][c + 2] = val;

        const std::pair<int, int> square(r, c);
        if (val == EMPTY) {
            white.erase(square);
            black.erase(square);
        } else if (val == W_PAWN) {
            white.insert(square);
            black.erase(square);
            ++defs[r + 3][c + 1];
            ++defs[r + 3][c + 3];
        } else {
            white.erase(square);
            black.insert(square);
        }
    }

    inline char get_square(const int r, const int c) const {
        return G[r + 2][c + 2];
    }

    inline int color(const int r, const int c) const {
        return G[r + 2][c + 2] == EMPTY ? W_MOVE | B_MOVE : (
            G[r + 2][c + 2] == INVALID ? 0 : (
                G[r + 2][c + 2] == W_PAWN ? B_MOVE : W_MOVE
            )
        );
    }

    inline int defenders(const int r, const int c) const {
        return G[r + 2][c + 2] == W_PAWN ? defs[r + 2][c + 2] : -1;
    }
    inline int attackers(const int r, const int c) const {
        return defs[r + 2][c + 2];
    }

    inline void make_move(const int r1, const int c1, const int r2, const int c2) {
        set_square(r2, c2, get_square(r1, c1));
        set_square(r1, c1, EMPTY);
    }

    inline void make_move(const Move& move) {
        set_square(move.r1, move.c1, EMPTY);
        set_square(move.r2, move.c2, move.piece);
    }

    inline void undo_move(const Move& move) {
        set_square(move.r1, move.c1, move.piece);
        set_square(move.r2, move.c2, move.target);
    }

    int white_moves(Move moves[]) const {
        int state = 0;  // Advance, advance while defended, defend, capture, promote
        int n = 0;
        for (const std::pair<int, int>& wp: white) {
            if (get_square(wp.first + 1, wp.second) == EMPTY) {
                if (wp.first + 2 >= H) {
                    return -1;
                }

                if (state <= 2 && (defenders(wp.first + 2, wp.second - 1) || defenders(wp.first + 2, wp.second + 1))) {
                    if (state < 2) state = 2, n = 0;
                    moves[n++] = Move(wp, 1, 0, W_PAWN, EMPTY);
                } else if (state <= 1 && defenders(wp.first + 1, wp.second) == 0) {
                    if (state < 1) state = 1, n = 0;
                    moves[n++] = Move(wp, 1, 0, W_PAWN, EMPTY);
                } else if (state <= 0) {
                    moves[n++] = Move(wp, 1, 0, W_PAWN, EMPTY);
                }
            }
            if (color(wp.first + 1, wp.second - 1) == W_MOVE) {
                if (wp.first + 2 == H) {
                    return -1;
                }
                if (state < 3) state = 3, n = 0;
                moves[n++] = Move(wp, 1, -1, W_PAWN, get_square(wp.first + 1, wp.second - 1));
            }
            if (color(wp.first + 1, wp.second + 1) == W_MOVE) {
                if (wp.first + 2 == H) {
                    return -1;
                }
                if (state < 3) state = 3, n = 0;
                moves[n++] = Move(wp, 1, 1, W_PAWN, get_square(wp.first + 1, wp.second + 1));
            }
        }
        return n;
    }

    int black_moves(Move moves[]) const {
        int n = 0;

        const auto add_move_if_valid = [&](const std::pair<int, int>& p, const int dr, const int dc) {
            const char target = get_square(p.first + dr, p.second + dc);
            if (target == EMPTY || target == W_PAWN) {
                moves[n++] = Move(p, dr, dc, get_square(p.first, p.second), target);
            }
            return target == EMPTY;
        };
        for (const std::pair<int, int> & bp: black) {
            const char piece = get_square(bp.first, bp.second);
            if (piece == B_PAWN) {
                if (get_square(bp.first - 1, bp.second) == EMPTY && bp.first > 0) {
                    // Don't deal with promotion, very unlikely and probably inefficient anyway
                    // We'll just pretend the pawn gets stuck on the first rank
                    moves[n++] = Move(bp, -1, 0, B_PAWN, EMPTY);
                }
                if (color(bp.first - 1, bp.second - 1) == B_MOVE) {
                    moves[n++] = Move(bp, -1, -1, B_PAWN, get_square(bp.first - 1, bp.second - 1));
                }
                if (color(bp.first - 1, bp.second + 1) == B_MOVE) {
                    moves[n++] = Move(bp, -1, 1, B_PAWN, get_square(bp.first - 1, bp.second + 1));
                }
            }
            if (piece == B_KNIGHT) {
                add_move_if_valid(bp, -2, -1);
                add_move_if_valid(bp, -2, +1);
                add_move_if_valid(bp, -1, -2);
                add_move_if_valid(bp, -1, +2);
                add_move_if_valid(bp, +1, -2);
                add_move_if_valid(bp, +1, +2);
                add_move_if_valid(bp, +2, -1);
                add_move_if_valid(bp, +2, +1);
            }
            if (piece == B_BISHOP || piece == B_QUEEN) {
                for (int d = 1; add_move_if_valid(bp, -d, -d); ++d);
                for (int d = 1; add_move_if_valid(bp, -d, +d); ++d);
                for (int d = 1; add_move_if_valid(bp, +d, -d); ++d);
                for (int d = 1; add_move_if_valid(bp, +d, +d); ++d);
            }
            if (piece == B_ROOK || piece == B_QUEEN) {
                for (int d = 1; add_move_if_valid(bp, -d, +0); ++d);
                for (int d = 1; add_move_if_valid(bp, +0, -d); ++d);
                for (int d = 1; add_move_if_valid(bp, +d, +0); ++d);
                for (int d = 1; add_move_if_valid(bp, +0, +d); ++d);
            }
            if (piece == B_KING) {
                add_move_if_valid(bp, -1, -1);
                add_move_if_valid(bp, -1, +0);
                add_move_if_valid(bp, -1, +1);
                add_move_if_valid(bp, +0, -1);
                add_move_if_valid(bp, +0, +1);
                add_move_if_valid(bp, +1, -1);
                add_move_if_valid(bp, +1, +0);
                add_move_if_valid(bp, +1, +1);
            }
        }
        return n;
    }
};

