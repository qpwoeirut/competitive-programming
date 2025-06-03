#ifndef PIECES_H
#define PIECES_H
const char EMPTY = '.';
const char INVALID = '#';
const char W_PAWN = 'E';
const char B_PAWN = 'P';
const char B_KNIGHT = 'N';
const char B_BISHOP = 'B';
const char B_ROOK = 'R';
const char B_KING = 'K';
const char B_QUEEN = 'Q';

const float DANGER[20] = {
    10000, 100, 20, 5, 1,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};

// TODO: tune these
float material_of(const char piece) {
    if (piece == EMPTY || piece == INVALID || piece == W_PAWN) return 0;
    if (piece == B_PAWN) return 0.9;
    if (piece == B_KNIGHT) return 8;
    if (piece == B_BISHOP) return 10;
    if (piece == B_ROOK) return 20;
    if (piece == B_QUEEN) return 50;
    if (piece == B_KING) return 15;
    std::cerr << piece << std::endl;
    assert(0);
}
#endif  // PIECES_H
