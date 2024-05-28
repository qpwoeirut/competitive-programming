#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

// stolen from https://atcoder.jp/contests/ahc031/submissions/51940007
using uint = unsigned int;
using ull = unsigned long long;
class rngen {
public:
    rngen() {}

    // to avoid bugs
    rngen(const rngen&) = delete;

    rngen& operator=(const rngen&&) = delete;

    rngen(int s) {
        seed(s);
    }

    void seed(int s) {
        state = s + INCR;
        next32();
    }

    int next_int() {
        return next31();
    }

    int next_int(int mod) {
        assert(mod > 0);
        return (int) ((ull) next31() * mod >> 31);
    }

    int next_int(int min, int max) {
        return min + next_int(max - min + 1);
    }

private:
    static constexpr ull MULT = 0x8b46ad15ae59daadull;
    static constexpr ull INCR = 0xf51827be20401689ull;
    ull state = (ull) chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();

    uint next32() {
        uint r = (uint) (state >> 59);
        state = state * MULT + INCR;
        state ^= state >> 18;
        uint t = (uint) (state >> 27);
        return t >> r | t << (-r & 31);
    }

    int next31() {
        return (int) (next32() & 0x7fffffff);
    }
};

const int N = 5;

using pii = pair<int,int>;
using move_t = array<char, N>;

const int MAX_TURNS = 1000;  // 40 turns per container. TODO: tighten this bound.

int A[N][N];
string ans[N];

const int EMPTY = -1;
struct Crane {
    int r, c;
    int box;
    bool bombed;
    bool small;

    Crane(): r(0), c(0), box(EMPTY), bombed(false), small(false) {}
    Crane(const int _r, const int _c, const bool _small): r(_r), c(_c), box(EMPTY), bombed(false), small(_small) {}

    const pii position() const {
        return pii(r, c);
    }
};

namespace Game {
    const int MISSING = 1000000;
    const int MISMATCH = 10000;
    const int MISORDER = 100;

    int i_row[N];
    int grid[N][N];
    int score;
    int penalty;  // TODO: early stopping.
    int turns;
    bool active;

    Crane crane[N];
    int dispatched;  // Mask storing all dispatched containers.
    int matched;  // Mask storing containers dispatched to correct gate.
    int pending[N];

    int n_answer;
    move_t answer[MAX_TURNS + 1];

    void receive_containers();

    void init() {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                grid[i][j] = EMPTY;
            }
        }
        for (int i=0; i<N; ++i) {
            i_row[i] = 0;
            crane[i] = Crane(i, 0, i > 0);

            pending[i] = N * i;
        }

        score = N * N * MISSING;
        penalty = 0;
        turns = 0;

        dispatched = 0;
        matched = 0;

        n_answer = 0;
        active = true;

        receive_containers();
    }

    void receive_containers() {
        int blocked_by_crane = 0;
        for (int i=0; i<N; ++i) {
            if (crane[i].c == 0 && crane[i].box != EMPTY) blocked_by_crane |= 1 << crane[i].r;
        }
        for (int r=0; r<N; ++r) {
            if (grid[r][0] == EMPTY && i_row[r] < N && ((blocked_by_crane >> r) & 1) == 0) {
                grid[r][0] = A[r][i_row[r]++];
            }
        }
    }

    void move_cranes(const array<char, N>& moves) {
        pii old_pos[N];
        for (int i=0; i<N; ++i) {
            old_pos[i] = crane[i].position();
            if (crane[i].bombed) {
                assert(moves[i] == '.');
                continue;
            }
            switch (moves[i]) {
                case 'P':
                    //assert(crane[i].box == EMPTY);
                    if (crane[i].box != EMPTY) {
                        score += N * N * MISSING;
                        active = false;
                    }
                    //assert(grid[crane[i].r][crane[i].c] != EMPTY);
                    if (grid[crane[i].r][crane[i].c] == EMPTY) {
                        score += N * N * MISSING;
                        active = false;
                    }
                    crane[i].box = grid[crane[i].r][crane[i].c];
                    grid[crane[i].r][crane[i].c] = EMPTY;
                    break;
                case 'Q':
                    //assert(crane[i].box != EMPTY);
                    if (crane[i].box == EMPTY) {
                        score += N * N * MISSING;
                        active = false;
                    }
                    //assert(grid[crane[i].r][crane[i].c] == EMPTY);
                    if (grid[crane[i].r][crane[i].c] != EMPTY) {
                        score += N * N * MISSING;
                        active = false;
                    }
                    grid[crane[i].r][crane[i].c] = crane[i].box;
                    crane[i].box = EMPTY;
                    break;
                case 'U':
                    assert(crane[i].r > 0);
                    --crane[i].r;
                    break;
                case 'D':
                    assert(crane[i].r + 1 < N);
                    ++crane[i].r;
                    break;
                case 'L':
                    assert(crane[i].c > 0);
                    --crane[i].c;
                    break;
                case 'R':
                    assert(crane[i].c + 1 < N);
                    ++crane[i].c;
                    break;
                case 'B':
                    assert(crane[i].box == EMPTY);
                    crane[i].bombed = true;
                    crane[i].r = crane[i].c = i + N;
                    break;
                case '.':
                    break;
                default:
                    debug(moves);
                    assert(false);
                    break;
            }

        }
        for (int i=0; i<N; ++i) {
            if (i != 0 && crane[i].box != EMPTY) {
                assert(grid[crane[i].r][crane[i].c] == EMPTY);
            }
            for (int j=i+1; j<N; ++j) {
                assert(crane[i].position() != crane[j].position());
                assert(crane[i].position() != old_pos[j] || crane[j].position() != old_pos[i]);
            }
        }
    }

    void dispatch_containers() {
        for (int r=0; r<N; ++r) {
            if (grid[r][N - 1] != EMPTY) {
                score -= MISSING;

                const int value = grid[r][N - 1];

                for (int i=value; i<N * (r + 1); ++i) {
                    if ((matched >> i) & 1) {
                        score += MISORDER;
                        penalty += MISORDER;
                    }
                }

                dispatched |= 1 << value;
                while (pending[r] < N * (r + 1) && (dispatched >> pending[r]) & 1) ++pending[r];

                if (N * r <= value && value < N * (r + 1)) {
                    matched |= 1 << value;
                } else {
                    score += MISMATCH;
                    penalty += MISMATCH;
                }

                grid[r][N - 1] = EMPTY;
            }
        }
    }

    void turn(const move_t& moves) {
        move_cranes(moves);
        dispatch_containers();
        receive_containers();

        //debug(moves);
        //debug2(grid, N, N);
        //debug(n_answer);
        answer[n_answer++] = moves;

        ++score;
        ++penalty;
        ++turns;

        if (turns >= MAX_TURNS) {
            active = false;
        }
        if (dispatched == (1 << (N * N)) - 1) {
            active = false;
        }

    }

    bool is_pending(const int box) {
        //assert(box != EMPTY);
        return pending[box / N] == box;
    }
    bool is_pending(const int r, const int c) {
        assert(grid[r][c] != EMPTY);
        return pending[grid[r][c] / N] == grid[r][c];
    }
}

using order_t = array<int, N * N>;
using pic = pair<int, char>;

int n_answer;
move_t answer[MAX_TURNS];
namespace Solver {
    const auto STOP_TIME = chrono::system_clock::now() + 2900ms;

    void shuffle(order_t& order, rngen& rng) {
        for (int i = 1; i < N * N; ++i) {
            swap(order[i], order[rng.next_int(i + 1)]);
        }
    }

    array<pii, N> target;
    bool target_free(const pii& pos) {
        for (int i=0; i<N; ++i) {
            if (target[i] == pos) return false;
        }
        return true;
    }

    pii pick_temp_spot(const int grid_val) {
        if (grid_val / N == N / 2) {
            for (int c=N-2; c>1; --c) {
                if (Game::grid[2][c] == EMPTY && target_free(pii(2, c))) return pii(2, c);
            }
            for (int c=N-2; c>1; --c) {
                if (Game::grid[0][c] == EMPTY && target_free(pii(0, c))) return pii(0, c);
                if (Game::grid[4][c] == EMPTY && target_free(pii(4, c))) return pii(4, c);
            }
            for (int c=N-2; c>1; --c) {
                if (Game::grid[1][c] == EMPTY && target_free(pii(1, c))) return pii(1, c);
                if (Game::grid[3][c] == EMPTY && target_free(pii(3, c))) return pii(3, c);
            }
        } else {
            array<int, N> row;
            if (grid_val / N < 2) {
                row = {0, 2, 4, 1, 3};
            } else {
                row = {4, 2, 0, 3, 1};
            }
            for (int i=0; i<N; ++i) {
                for (int c=N-2; c>1; --c) {
                    if (Game::grid[row[i]][c] == EMPTY && target_free(pii(row[i], c))) return pii(row[i], c);
                }
            }
        }

        // Fallback by just dispatching the box.
        return pii(grid_val / N, N - 1);
    }

    bool find_nearest_pending(int i) {
        const pii position = target[i];
        int best_dist = N * N;
        for (int r=0; r<N; ++r) {
            for (int c=1; c<N; ++c) {
                if (Game::grid[r][c] != EMPTY && Game::is_pending(r, c)) {
                    if (best_dist > abs(position.first - r) + abs(position.second - c) && target_free(pii(r, c))) {
                        best_dist = abs(position.first - r) + abs(position.second - c);
                        target[i] = pii(r, c);
                    }
                }
            }
        }
        return best_dist < N * N;
    }

    const int INVALID = 100000;
    const int chr[5] = {0, 1, 0, -1, 0};
    const int chc[5] = {1, 0, -1, 0, 0};
    int score_of(const int dir, const Crane& crane, const pii& tar) {
        const int r = crane.r + chr[dir];
        const int c = crane.c + chc[dir];
        const int orig_dist = abs(crane.r - tar.first) + abs(crane.c - tar.second);
        const int new_dist = abs(r - tar.first) + abs(c - tar.second);
        const bool empty_lane = (crane.box != EMPTY && crane.small) || c < tar.second;
        const bool switch_lane = c > 0 && (empty_lane ^ (r % 2));
        
        if (r < 0 || r >= N || c < 0 || c >= N) return INVALID;
        if (crane.small && Game::grid[r][c] != EMPTY && crane.box != EMPTY) return INVALID;
        return 100 * (new_dist - orig_dist) + switch_lane;
    }

    array<pii, N> calculate_new_positions(const array<pic, 5> options[N], array<int, N>& i_opt) {
        array<pii, N> new_pos;
        for (int i=0; i<N; ++i) {
            if (options[i][i_opt[i]].first >= INVALID) i_opt[i] = 4;

            new_pos[i] = Game::crane[i].position();
            if (options[i][i_opt[i]].second == 'R') ++new_pos[i].second;
            else if (options[i][i_opt[i]].second == 'D') ++new_pos[i].first;
            else if (options[i][i_opt[i]].second == 'L') --new_pos[i].second;
            else if (options[i][i_opt[i]].second == 'U') --new_pos[i].first;
        }
        return new_pos;
    }

    void set_moves(move_t& move) {
        array<pic, 5> options[N];
        array<int, N> i_opt;
        i_opt.fill(0);
        for (int i=0; i<N; ++i) {
            options[i] = { pic(INVALID, 'R'), pic(INVALID, 'D'), pic(INVALID, 'L'), pic(INVALID, 'U'), pic(INVALID, '.') };
            if (move[i] != 'M') {
                i_opt[i] = 4;
                continue;
            }
            
            for (int d=0; d<5; ++d) {
                options[i][d].first = score_of(d, Game::crane[i], target[i]);
            }
            sort(options[i].begin(), options[i].begin() + 4);
        }

        bool ok = true;
        do {
            ok = true;
            const array<pii, N> new_pos = calculate_new_positions(options, i_opt);
            for (int i=0; i<N; ++i) {
                //debug(new_pos, i_opt);
                if (i != 0 && Game::crane[i].box != EMPTY && Game::grid[new_pos[i].first][new_pos[i].second] != EMPTY) {
                    assert(i_opt[i] < 4);
                    ++i_opt[i];
                    ok = false;
                    break;
                }
                for (int j=i+1; j<N; ++j) {
                    if (new_pos[i] == new_pos[j]) {
                        if (i_opt[j] < 4) {
                            ++i_opt[j];
                        } else {
                            assert(i_opt[i] < 4);
                            ++i_opt[i];
                        }
                        ok = false;
                        break;
                    }
                    if (Game::crane[i].position() == new_pos[j] && Game::crane[j].position() == new_pos[i]) {
                        assert(i_opt[i] < 4 && i_opt[j] < 4);
                        if (options[i][i_opt[i] + 1].first < options[i][i_opt[j] + 1].first) ++i_opt[i];
                        else ++i_opt[j];
                        ok = false;
                        break;
                    }
                }
            }
        } while (!ok);

        for (int i=0; i<N; ++i) {
            if (move[i] == 'M') move[i] = options[i][i_opt[i]].second;
        }
    }

    int best_score = N * N * 1000000;
    const pii TO_BOMB(N, N);
    void solve_order(const order_t& order) {
        Game::init();
        
        int i_order = 0;
        for (; i_order<N; ++i_order) {
            target[i_order] = pii(order[i_order], 0);
        }

        move_t move;
        while (Game::active) {
            move.fill('.');
            for (int i=0; i<N; ++i) {
                //debug(target[i], Game::crane[i].position(), Game::crane[i].box);
                if (Game::crane[i].bombed) {
                    move[i] = '.';
                    continue;
                }
                if (target[i] == TO_BOMB) {
                    move[i] = 'B';
                    continue;
                }
                if (Game::turns >= 50 + i && i > 0 && Game::crane[i].box != EMPTY && Game::crane[i].c > 0 && Game::grid[Game::crane[i].r][Game::crane[i].c] == EMPTY) {
                    target[i] = TO_BOMB;
                    move[i] = 'Q';
                    continue;
                }
                if (Game::crane[i].box != EMPTY && Game::is_pending(Game::crane[i].box) && target[i].second != N - 1) {
                    target[i] = pii(Game::crane[i].box / N, N - 1);
                }
                if (Game::crane[i].position() == target[i]) {
                    const int grid_val = Game::grid[Game::crane[i].r][Game::crane[i].c];
                    //debug(i, Game::crane[i].box, target[i], grid_val);
                    if (Game::crane[i].box == EMPTY) {
                        move[i] = 'P';
                        if (Game::is_pending(grid_val)) {
                            target[i] = pii(grid_val / N, N - 1);
                        } else {
                            target[i] = pick_temp_spot(grid_val);
                        }
                    } else {
                        move[i] = 'Q';
                        if (!find_nearest_pending(i)) {
                            if (i_order == N * N) target[i] = TO_BOMB;
                            else target[i] = pii(order[i_order++], 0);
                        }
                    }
                } else if (Game::crane[i].bombed == false) {
                    move[i] = 'M';
                }
            }

            set_moves(move);
            Game::turn(move);
        }
    }

    void solve() {
        rngen rng(8);
        array<int, N * N> order;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                order[5 * i + j] = i;
            }
        }

        while (chrono::system_clock::now() < STOP_TIME) {
            shuffle(order, rng);
            sort(order.begin(), order.begin() + 5);
            solve_order(order);
            debug(order, best_score, Game::score);
            if (best_score >= Game::score) {
                best_score = Game::score;
                n_answer = Game::n_answer;
                copy(Game::answer, Game::answer + n_answer, answer);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _N;
    cin >> _N;
    assert(_N == N);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> A[i][j];
        }
    }

    Solver::solve();

    for (int i=0; i<N; ++i) {
        string s(n_answer, '.');
        for (int j=0; j<n_answer; ++j) {
            s[j] = answer[j][i];
        }
        cout << s << '\n';
    }
}

/*
5
0 1 2 3 4
5 6 7 8 9
10 11 12 13 14
15 16 17 18 19
20 21 22 23 24
*/
