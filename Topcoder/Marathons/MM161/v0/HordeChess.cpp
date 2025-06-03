#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
#include "board.cpp"

using namespace std;

Move moves[8 * (3 + 19 + 7 + 7)];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int H;
    cin >> H;
    Board board(H);
    board.read_in(cin);

    mt19937 rng(8);

    // TODO: implement actual score based on board and searching
    const auto score = [&board, &H](const Move& move) {
        int s = 0;
        if (board.attackers(move.r1, move.c1)) s += move.piece == 'P' ? 50 : 100;
        if (board.attackers(move.r2, move.c2)) s -= move.piece == 'P' ? 50 : 100;
        if (board.get_square(move.r2, move.c2) == 'E') s += 5 * max(1, (move.r2 - H + 23));
        if ((move.piece == 'R' || move.piece == 'Q' || move.piece == 'K') && (move.c2 == 0 || move.c2 == 7)) s += move.r1 - move.r2 + 1;

        return s;
    };

    while (true) {
        int elapsed;
        cin >> elapsed;

        if (board.white_moves(moves) == 0) {
            int status;
            cin >> status;
            assert(status == 0);
            break;
        }

        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        board.make_move(r1, c1, r2, c2);

        const int n_b = board.black_moves(moves);
        if (n_b == 0) {
            cout << "0\n";
            break;
        }
        sort(moves, moves+n_b, [&score](const Move& a, const Move& b) {
            return score(a) > score(b);
        });
        const Move move = moves[0];
        board.make_move(move);

        //cerr << move << ' ' << move.piece << ' ' << move.target << ' ' << score(move) << endl;
        cout << move << '\n';
        cout.flush();
    }
}
