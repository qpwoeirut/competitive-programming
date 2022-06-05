//brute.cpp created at 05/27/22 21:41:31
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;

template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

constexpr int MN = 10;

int N, T;

using namespace boost::multiprecision;
using namespace chrono;

const auto start_time = system_clock::now();
inline bool time_up() {
    const auto cur_time = system_clock::now();
    return duration_cast<milliseconds>(cur_time - start_time).count() >= 2950;
}

using board_t = int512_t;

// top left is most significant bits
int get_val(const board_t& board, const int pos) {
    //assert(0 <= pos && pos < N*N);
    return static_cast<int>((board >> (pos << 2)) & 0xF);
}
void set_val(board_t& board, const int pos, const board_t val) {
    //assert(0 <= pos && pos < N*N);
    board |= board_t(0xF) << (pos << 2);
    board ^= board_t(0xF) << (pos << 2);
    board |= val << (pos << 2);
}

#define left_ok(x)  ((x % N) < N - 1)
#define up_ok(x)    (x + N < N * N)
#define right_ok(x) ((x % N) > 0)
#define down_ok(x)  (x >= N)

constexpr int BAD = -0xFFFF;

__int128 visited;
int dfs(const board_t& board, const int pos, const int par = -1) {
    if ((visited >> pos) & 1) return 0;
    visited |= __int128(1) << pos;

    int ret = 1;
    const int val = get_val(board, pos);
    if ((val & 1) && left_ok(pos)  && (get_val(board, pos + 1) & 4) && pos + 1 != par) ret += ((visited >> (pos + 1)) & 1) ? BAD : dfs(board, pos + 1, pos);
    if ((val & 2) && up_ok(pos)    && (get_val(board, pos + N) & 8) && pos + N != par) ret += ((visited >> (pos + N)) & 1) ? BAD : dfs(board, pos + N, pos);
    if ((val & 4) && right_ok(pos) && (get_val(board, pos - 1) & 1) && pos - 1 != par) ret += ((visited >> (pos - 1)) & 1) ? BAD : dfs(board, pos - 1, pos);
    if ((val & 8) && down_ok(pos)  && (get_val(board, pos - N) & 2) && pos - N != par) ret += ((visited >> (pos - N)) & 1) ? BAD : dfs(board, pos - N, pos);
    return ret;
}

int evaluate(const board_t& board) {
    visited = 0;
    int res = 0;
    for (int i=0; i<N*N; ++i) {
        chmx(res, dfs(board, i));
    }
    return res;
}

inline int hex_to_int(const char c) {
    return ('0' <= c && c <= '9') ? c - '0' : c - 'a' + 10;
}

bool move_ok(const int zero, const int move) {
    if (move == 0) return left_ok(zero);
    if (move == 1) return up_ok(zero);
    if (move == 2) return right_ok(zero);
    if (move == 3) return down_ok(zero);
    //assert(0);
}

void move_board(board_t& board, int& zero, const int move) {
    //assert(move_ok(zero, move));
    if (move == 0) {
        set_val(board, zero, get_val(board, zero + 1));
        set_val(board, zero + 1, 0);
        ++zero;
    } else if (move == 1) {
        set_val(board, zero, get_val(board, zero + N));
        set_val(board, zero + N, 0);
        zero += N;
    } else if (move == 2) {
        set_val(board, zero, get_val(board, zero - 1));
        set_val(board, zero - 1, 0);
        --zero;
    } else if (move == 3) {
        set_val(board, zero, get_val(board, zero - N));
        set_val(board, zero - N, 0);
        zero -= N;
    } //else assert(0);
}

board_t move_left(board_t board, const int zero) {
    //assert(left_ok(zero));
    set_val(board, zero, get_val(board, zero + 1));
    set_val(board, zero + 1, 0);
    return board;
}
board_t move_up(board_t board, const int zero) {
    //assert(up_ok(zero));
    set_val(board, zero, get_val(board, zero + N));
    set_val(board, zero + N, 0);
    return board;
}
board_t move_right(board_t board, const int zero) {
    //assert(right_ok(zero));
    set_val(board, zero, get_val(board, zero - 1));
    set_val(board, zero - 1, 0);
    return board;
}
board_t move_down(board_t board, const int zero) {
    //assert(down_ok(zero));
    set_val(board, zero, get_val(board, zero - N));
    set_val(board, zero - N, 0);
    return board;
}

map<board_t, int> cache;
int search_moves(const board_t& board, const int zero, const int depth, const int bad) {
    if (depth == 0) return evaluate(board);
    auto it = cache.find(board);
    if (it != cache.end() && it->second >= depth) return 0;  // that possibility has already been taken into account

    int best = evaluate(board) << (depth << 1);
    if (time_up()) return best;
    if (bad != 0 && left_ok(zero))  chmx(best, (search_moves(move_left (board, zero), zero + 1, depth - 1, 2) << 2)    );
    if (bad != 1 && up_ok(zero))    chmx(best, (search_moves(move_up   (board, zero), zero + N, depth - 1, 3) << 2) | 1);
    if (bad != 2 && right_ok(zero)) chmx(best, (search_moves(move_right(board, zero), zero - 1, depth - 1, 0) << 2) | 2);
    if (bad != 3 && down_ok(zero))  chmx(best, (search_moves(move_down (board, zero), zero - N, depth - 1, 1) << 2) | 3);
    if (depth > 1) cache[board] = depth;
    return best;
}

//template<typename Number> string to_hex(const Number& x) {
//    stringstream stream;
//    stream << hex << x;
//    return stream.str();
//}

const string MOVES = "LURD";
int DEPTH = 8;

string climb(board_t& board, int zero) {
    string answer = "";
    int bad_move = -1;

    set<board_t> vis;

    int move = -1;
    for (int i=0; i<T; ++i) {
        const int cur_eval = evaluate(board);
        int val = search_moves(board, zero, DEPTH, bad_move);
        //debug(i, cur_eval, val >> (DEPTH << 1), zero);
        if ((val >> (DEPTH << 1)) <= cur_eval) break;

        for (int j=6; j<=N; ++j) {
            if (!move_ok(zero, val & 3)) break;
            move = val & 3; val >>= 2;
            move_board(board, zero, move);
            answer += MOVES[move];

            if (vis.insert(board).second == false) return answer;  // stop going in circles
        }
        //assert(move != -1);

        //debug(answer, evaluate(board));
        //for (int i=0; i<N; ++i) { cerr << to_hex(board).substr(i*N, N) << endl; }

        if (time_up()) break;

        bad_move = (move + 2) & 3;
        cache.clear();
    }
    return answer;
}

// https://stackoverflow.com/questions/1640258/need-a-fast-random-generator-for-c
unsigned int g_seed = 8;
inline int fastrand() { 
    g_seed = (214013 * g_seed + 2531011); 
    return (g_seed >> 16) & 3;
} 

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T;
    const int t = (T * 3) >> 2;
    T -= t;
    
    board_t start_board = 0;
    int start_zero = -1;
    for (int i=N*N-1; i>=0; --i) {
        char c;
        cin >> c;
        set_val(start_board, i, hex_to_int(c));
        if (c == '0') start_zero = i;
    }
    //assert(start_zero != -1);

    string ans = "";
    int best_eval = 0;
    //int ct = 0;
    while (!time_up()) {
        board_t cur_board = start_board;
        int cur_zero = start_zero;
        string cur_moves = "";
        int prev_move = -1;
        for (int i=0; i<t; ++i) {
            int move = fastrand();
            while (((move + 2) & 3) != prev_move && !move_ok(cur_zero, move)) move = fastrand();
            move_board(cur_board, cur_zero, move);
            cur_moves += MOVES[move];
            prev_move = move;
        }

        cur_moves += climb(cur_board, cur_zero);
        if (chmx(best_eval, evaluate(cur_board))) ans = cur_moves;
        //cerr << "ct=" << (++ct) << ' ' << cur_moves << ' ' << evaluate(cur_board) << endl;
    }

    cout << ans << '\n';
}

/*
notes
it's very hard to utilize all T moves
    (done) use the first few to scramble position, similar to random-restart hill climbing
(done) complete search in chains; search to a depth of D, execute M moves, repeat until maxima found
(done) add a cache for already-visited states; will require storing the depth; investigate persisting cache for entire search chain
change evaluation to account for # of "open" edges in the largest component
*/
