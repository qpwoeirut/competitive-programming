#include <iostream>
#include <algorithm>
//#include <cassert>
#include "pieces.h"
#include "table.h"
#include "zobrist.h"

const int W_MOVE = 1;
const int B_MOVE = 2;

const int MAX_H = 20;
const int W = 8;

struct Square {
    int row, col;

    Square() : row(0), col(0) {}
    Square(const int _row, const int _col) : row(_row), col(_col) {}

    friend std::ostream& operator<<(std::ostream& os, const Square& square) {
        os << square.row << ' ' << square.col;
        return os;
    }

    int hash() const {
        return (row << 3) | col;
    }
};

struct Move {
    int r1, c1;
    int r2, c2;
    char piece;
    char target;

    Move() : r1(0), c1(0), r2(0), c2(0), piece(INVALID), target(INVALID) {}
    Move(const int r, const int c, const int dr, const int dc, const char _piece, const char _target) : r1(r), c1(c), r2(r + dr), c2(c + dc), piece(_piece), target(_target) {}
    Move(const Square& p, const int dr, const int dc, const char _piece, const char _target) : Move(p.row, p.col, dr, dc, _piece, _target) {}

    const bool operator<(const Move& o) const {
        return (target != EMPTY) < (o.target != EMPTY);
    }
    const bool operator==(const Move& o) const {
        return r1 == o.r1 && c1 == o.c1 && r2 == o.r2 && c2 == o.c2 && piece == o.piece && target == o.target;
    }

    friend std::ostream& operator<<(std::ostream& os, const Move& move) {
        os << move.r1 << ' ' << move.c1 << ' ' << move.r2 << ' ' << move.c2;
        return os;
    }

    int hash() const {  // ONLY WORKS FOR PAWN MOVES
        //assert(piece == W_PAWN);
        return (r1 < 0 || r1 >= 20 || r2 < 0 || r2 >= 20 || c1 < 0 || c1 >= W || c2 < 0 || c2 >= W) ? -1 : ((c1 < c2) ? 160 : 0) + ((r1 << 3) | c1);
    }
};

struct Board {
    const int H;

    int turn;

    char G[MAX_H + 4][W + 4];
    int defs[MAX_H + 4][W + 4];

    float danger;
    float material;
    uint64_t hash;
    SmallTable<Square, 160> white, black;
    SmallTable<Move, 160> advance, promote;
    SmallTable<Move, 320> capture;

    Board(const int _H) : H(_H), white(), black(), advance(), promote(), capture() {
        turn = 0;
        for (int r = 0; r < H + 4; ++r) {
            for (int c = 0; c < W + 4; ++c) {
                G[r][c] = INVALID;
                defs[r][c] = 0;
            }
        }
        danger = 0;
        material = 0;
        hash = 0;
    }

    friend std::istream& operator>>(std::istream& is, Board& board) {
        for (int r = 0; r < board.H; ++r) {
            for (int c = 0; c < W; ++c) {
                board.set_square(r, c, EMPTY);
            }
        }
        for (int r = 0; r < board.H; ++r) {
            for (int c = 0; c < W; ++c) {
                char ch;
                is >> ch;
                board.set_square(r, c, ch);
            }
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& board) {
        os << "hash = " << board.hash << ". white = " << board.advance.size << ',' << board.capture.size << ',' << board.promote.size << ". black = " << board.black.size << std::endl;
        for (int r = 0; r < board.H + 2; ++r) {
            for (int c = 0; c < W + 2; ++c) {
                os << board.G[r + 1][c + 1];
            }
            os << std::endl;
        }
        return os;
    }

    void add_advance_from(const int r, const int c) {
        if (r + 2 >= H) promote.emplace(r, c, 1, 0, W_PAWN, EMPTY);
        else advance.emplace(r, c, 1, 0, W_PAWN, EMPTY);
    }
    void delete_advance_from(const int r, const int c) {
        if (r + 2 >= H) promote.erase(Move(r, c, 1, 0, W_PAWN, EMPTY));
        else advance.erase(Move(r, c, 1, 0, W_PAWN, EMPTY));
    }

    void set_square(const int r, const int c, const char val) {
        const char old_val = G[r + 2][c + 2];
        material += material_of(val) - material_of(old_val);
        if (old_val == W_PAWN) {
            --defs[r + 3][c + 1];
            --defs[r + 3][c + 3];
            danger -= DANGER[H - r - 1];
        }

        // Remove all related pawn moves
        delete_advance_from(r - 1, c);
        delete_advance_from(r, c);
        capture.erase(Move(r, c, 1, -1, W_PAWN, get_square(r + 1, c - 1)));
        capture.erase(Move(r, c, 1, +1, W_PAWN, get_square(r + 1, c + 1)));
        capture.erase(Move(r - 1, c - 1, 1, +1, W_PAWN, old_val));
        capture.erase(Move(r - 1, c + 1, 1, -1, W_PAWN, old_val));

        //std::cerr << r << ' ' << c << ' ' << old_val << ' ' << val << std::endl;
        hash ^= zobrist(r, c, old_val) ^ zobrist(r, c, val);
        G[r + 2][c + 2] = val;

        const Square square(r, c);
        if (val == EMPTY) {
            white.erase(square);
            black.erase(square);
            if (get_square(r - 1, c) == W_PAWN) add_advance_from(r - 1, c);
        } else if (val == W_PAWN) {
            white.insert(square);
            black.erase(square);
            ++defs[r + 3][c + 1];
            ++defs[r + 3][c + 3];
            danger += DANGER[H - r - 1];

            if (get_square(r + 1, c) == EMPTY) {
                add_advance_from(r, c);
            }
            if (color(r + 1, c - 1) == W_MOVE) {
                capture.emplace(r, c, 1, -1, W_PAWN, get_square(r + 1, c - 1));
            }
            if (color(r + 1, c + 1) == W_MOVE) {
                capture.emplace(r, c, 1, +1, W_PAWN, get_square(r + 1, c + 1));
            }
        } else {
            if (get_square(r - 1, c - 1) == W_PAWN) {
                capture.emplace(r - 1, c - 1, 1, +1, W_PAWN, val);
            }
            if (get_square(r - 1, c + 1) == W_PAWN) {
                capture.emplace(r - 1, c + 1, 1, -1, W_PAWN, val);
            }
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

    inline bool vulnerable(const int r, const int c) const {
        if (attackers(r, c) == 0) return true;
        if (attackers(r, c) >= 2) return false;
        return attackers(r, c) == 0 || (attackers(r, c) == 1 && (
            (get_square(r - 1, c - 1) == W_PAWN && get_square(r, c - 1) == EMPTY && attackers(r, c - 1) > 0) ||
            (get_square(r - 1, c + 1) == W_PAWN && get_square(r, c + 1) == EMPTY && attackers(r, c + 1) > 0)
        ));
    }

    int white_moves(Move moves[], bool quiescence) const {
        if (promote.size) return -1;

        int n = 0;
        // TODO: consider making forks active moves. the qsearch should be enough to cover it, but looking further ahead would be nice
        if (quiescence || capture.size) {
            n = std::copy(capture.items, capture.items + capture.size, moves) - moves;
            //assert(n == capture.size);
        } else {
            //assert(capture.size == 0);
            int state = 0;  // advance, advance while defended, defend. capture/promote already handled
            for (int i = 0; i < advance.size; ++i) {
                const Move move = advance.items[i];
                if (defenders(move.r2 + 1, move.c2 - 1) == 0 || defenders(move.r2 + 1, move.c2 + 1) == 0) {
                    if (state < 2) state = 2, n = 0;
                    moves[n++] = move;
                } else if (state <= 1 && defenders(move.r2, move.c2) > 0) {
                    if (state < 1) state = 1, n = 0;
                    moves[n++] = move;
                } else if (state <= 0) {
                    moves[n++] = move;
                }
            }
        }
        return n;
    }

    int black_moves(Move moves[], bool quiescence) const {
        int n = 0;

        const auto add_move_if_valid = [&](const Square& p, const int dr, const int dc) {
            const char target = get_square(p.row + dr, p.col + dc);
            if ((!quiescence && target == EMPTY) || target == W_PAWN) {
                moves[n++] = Move(p, dr, dc, get_square(p.row, p.col), target);
            }
            return target == EMPTY;
        };
        for (int i = 0; i < black.size; ++i) {
            const Square& bp = black.items[i];
            const char piece = get_square(bp.row, bp.col);
            if (piece == B_PAWN) {
                if (get_square(bp.row - 1, bp.col) == EMPTY && !quiescence) {
                    // Don't deal with promotion, very unlikely and probably inefficient anyway
                    // We'll just pretend the pawn gets stuck on the row rank
                    moves[n++] = Move(bp, -1, 0, B_PAWN, EMPTY);
                }
                if (color(bp.row - 1, bp.col - 1) == B_MOVE) {
                    moves[n++] = Move(bp, -1, -1, B_PAWN, get_square(bp.row - 1, bp.col - 1));
                }
                if (color(bp.row - 1, bp.col + 1) == B_MOVE) {
                    moves[n++] = Move(bp, -1, +1, B_PAWN, get_square(bp.row - 1, bp.col + 1));
                }
            } else if (piece == B_KNIGHT) {
                add_move_if_valid(bp, -2, -1);
                add_move_if_valid(bp, -2, +1);
                add_move_if_valid(bp, -1, -2);
                add_move_if_valid(bp, -1, +2);
                add_move_if_valid(bp, +1, -2);
                add_move_if_valid(bp, +1, +2);
                add_move_if_valid(bp, +2, -1);
                add_move_if_valid(bp, +2, +1);
            } else if (piece == B_KING) {
                add_move_if_valid(bp, -1, -1);
                add_move_if_valid(bp, -1, +0);
                add_move_if_valid(bp, -1, +1);
                add_move_if_valid(bp, +0, -1);
                add_move_if_valid(bp, +0, +1);
                add_move_if_valid(bp, +1, -1);
                add_move_if_valid(bp, +1, +0);
                add_move_if_valid(bp, +1, +1);
            } else if (piece == B_BISHOP || piece == B_QUEEN) {
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
        }
        return n;
    }
};

