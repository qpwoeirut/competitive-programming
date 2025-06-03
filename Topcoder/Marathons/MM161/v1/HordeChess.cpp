#pragma GCC optimize("O3,unroll-loops")

#include <iostream>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <unordered_map>
#include "board.cpp"
#include "pieces.h"

using namespace std;

const int Q_CUTOFF = 9000;
const int TIME_LIMIT = 9900;
const int MAX_WHITE_MOVES = 10 * 8;
const int MAX_BLACK_MOVES = 8 * 3 + 8 * (7 + 19 + 7 + 7);

bitset<8 * 20> threatened;
Move eval_moves[MAX_BLACK_MOVES];
float evaluate(const Board& board) {
    threatened.reset();

    float progress_score = 8 * 20 - (int)(board.white.size()) - board.danger;
    progress_score += max(progress_score - 150, 0.0f) * 10;

    const int n_b = board.black_moves(eval_moves, true);
    float active_score = 0;
    for (int i = 0; i < n_b; ++i) {
        if (!threatened[eval_moves[i].r2 * 8 + eval_moves[i].c2]) {
            threatened[eval_moves[i].r2 * 8 + eval_moves[i].c2] = true;
            active_score += board.vulnerable(eval_moves[i].r2, eval_moves[i].c2) ? 0.5 : 0.001;
        }
    }

    return progress_score + board.material + active_score;
}

const float MIN_SCORE = -1000000;

const int DEPTH = 1;
const int Q_DEPTH = 0;  // TODO: this makes the bot perform worse?
unordered_map<uint64_t, float> table_w[DEPTH + Q_DEPTH + 1], table_b[DEPTH + Q_DEPTH + 1];

int elapsed;
float search(Board& board, int depth, const float cur_best) {
    const int d_idx = depth + Q_DEPTH;
    auto it = table_w[d_idx].find(board.hash);
    if (it != table_w[d_idx].end()) {
        return it->second;
    }
    Move moves_w[MAX_WHITE_MOVES], moves_b[MAX_BLACK_MOVES];
    const int n_w = board.white_moves(moves_w, depth <= 0);
    if (depth <= -Q_DEPTH || (depth <= 0 && (n_w == 0 || elapsed >= Q_CUTOFF)) || elapsed >= TIME_LIMIT) {
        return table_w[d_idx][board.hash] = evaluate(board);
    }

    if (n_w == -1) return -(board.H * 8 * ((int)(board.white.size()) - 1) - depth);
    if (n_w == 0) return evaluate(board) + (board.white.empty() ? 1000 - board.turn : -8 * board.H * (int)(board.white.size()));

    float score = 0;
    for (int i_w = 0; i_w < n_w; ++i_w) {
        board.make_move(moves_w[i_w]);

        auto it = table_b[d_idx].find(board.hash);
        if (it != table_b[d_idx].end()) {
            score += it->second;
        } else {
            const int n_b = board.black_moves(moves_b, depth <= 0);
            sort(moves_b, moves_b + n_b);
            float best_score = evaluate(board);
            for (int i_b = 0; i_b < n_b; ++i_b) {
                board.make_move(moves_b[i_b]);
                best_score = max(best_score, search(board, depth - 1, best_score));
                board.undo_move(moves_b[i_b]);
            }
            score += best_score;

            table_b[d_idx][board.hash] = best_score;
        }

        board.undo_move(moves_w[i_w]);

        if (score + (1.5f + score / (i_w + 1)) * (n_w - i_w - 1) < cur_best * n_w) {
            return table_w[d_idx][board.hash] = score / (i_w + 1);
        }
    }
    score /= n_w;

    return table_w[d_idx][board.hash] = score;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    if (Q_DEPTH) {
        table_w[0].reserve(2000000);
        table_w[1].reserve(5000000);
        table_w[2].reserve(25000);
        table_b[1].reserve(50000);
        table_b[2].reserve(25000);
    } else {
        table_w[0].reserve(2500000);
        table_w[1].reserve(15000);
        table_b[1].reserve(80000);
    }

    int H;
    cin >> H;
    Board board(H);
    cin >> board;

    Move moves_w[MAX_WHITE_MOVES], moves_b[MAX_BLACK_MOVES];

    while (true) {
        cin >> elapsed;
        //cerr << elapsed << ' ' << evaluate(board) << endl;

        if (board.white_moves(moves_w, false) == 0) {
            break;
        }

        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        board.make_move(r1, c1, r2, c2);
        ++board.turn;

        Move best_move;
        float best_score = MIN_SCORE;
        
        const float eval = evaluate(board);  // Assume we cannot be in zugzwang
        const int n_b = board.black_moves(moves_b, false);
        sort(moves_b, moves_b + n_b);
        for (int i = 0; i < n_b; ++i) {
            board.make_move(moves_b[i]);
            const float score = search(board, DEPTH, eval);
            //cerr << "score = " << score << ". " << board << endl;
            board.undo_move(moves_b[i]);
            if (best_score < score) {
                best_score = score;
                best_move = moves_b[i];
            }
        }

        if (best_score == MIN_SCORE) {
            cout << "0\n";
            cout.flush();
            break;
        }
        board.make_move(best_move);
        ++board.turn;

        //cerr << best_move << ' ' << best_move.piece << ' ' << best_move.target << ' ' << best_score << endl;
        //cerr << table_w[0].size() << ' ' << table_w[1].size() << ' ' << table_b[0].size() << ' ' << table_b[1].size() << endl;
        cout << best_move << '\n';
        cout.flush();
    }
}
