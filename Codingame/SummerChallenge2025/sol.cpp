#include <iostream>
#include <map>

using namespace std;

template <typename T>
bool chmn(T &a, T b) {
    return a > b ? a = b, true : false;
}

template <typename T>
bool chmx(T &a, T b) {
    return a < b ? a = b, true : false;
}

int sign(int a) {
    return a > 0 ? 1 : a < 0 ? -1 : 0;
}

const int chr[] = {0, 1, 0, -1, 0};
const int chc[] = {1, 0, -1, 0, 0};

const int MAX_W = 20;
const int MAX_H = 10;
const int MAX_AGENT = 10;

const int EMPTY = 0;
const int LOW = 1;
const int HIGH = 2;

const int MOVE = 0;
const int SHOOT = 1;
const int SPLASH = 2;
const int HUNKER_DOWN = 3;

const int SPLASH_POWER = 30;

const int INF = 1e9;

int my_id;
int W, H;
int n_agent;

int cover[MAX_H][MAX_W][MAX_H][MAX_W];

struct Move {
    int agentId;
    
    int move_r, move_c;

    int action;
    int target_id;
    int target_r, target_c;

    float score;

    Move(int a_id, int mr, int mc, int act, int t_id, int tr, int tc, float sc) : agentId(a_id), move_r(mr), move_c(mc), action(act), target_id(t_id), target_r(tr), target_c(tc), score(sc) {}

    friend ostream& operator<<(ostream& os, const Move& m) {
        if (m.action == HUNKER_DOWN) {
            os << m.agentId << ";HUNKER_DOWN";
        } else {
            os << m.agentId << ";MOVE " << m.move_c << " " << m.move_r;
            if (m.action == MOVE) os << ";HUNKER_DOWN";
            if (m.action == SHOOT) os << ";SHOOT " << m.target_id;
            if (m.action == SPLASH) os << ";THROW " << m.target_c << " " << m.target_r;
        }
        return os;
    }
};

struct Tile {
    int r, c;
    int tile_type;

    friend ostream &operator<<(ostream &os, const Tile &t) {
        os << "Tile (" << t.c << ", " << t.r << ", " << t.tile_type << ")";
        return os;
    }
};

Tile G[MAX_H][MAX_W];

struct Agent {
    int idx;
    int agentId;
    int player;

    int shootCooldown;
    int optimalRange;
    int soakingPower;

    int r, c;
    int cooldown;
    int splashBombs;
    int wetness;

    bool alive;

    friend ostream &operator<<(ostream &os, const Agent &a) {
        os << "Agent " << a.agentId << " (" << a.c << ", " << a.r << ", player=" << a.player << ", cooldown=" << a.cooldown << ", splashBombs=" << a.splashBombs << ", alive=" << a.alive << ", wetness=" << a.wetness << ")";
        return os;
    }

    int dist(int r, int c) const {
        return abs(this->r - r) + abs(this->c - c);
    }

    bool adj(int r, int c) const {
        return max(abs(this->r - r), abs(this->c - c)) == 1;
    }

    int dist_after_move(int r, int c) const {
        int best_dist = dist(r, c);
        for (int d = 0; d < 4; ++d) {
            const int rr = r + chr[d];
            const int cc = c + chc[d];
            if (0 <= rr && rr < H && 0 <= cc && cc < W && G[rr][cc].tile_type == EMPTY) {
                chmx(best_dist, dist(rr, cc));
            }
        }
        return best_dist;
    }

    float shot_score(int target_r, int target_c, int wetness, bool can_move, bool hunkered) const {
        if (cooldown > 0) return -INF;

        const int shot_dist = can_move ? dist_after_move(target_r, target_c) : dist(target_r, target_c);
        if (shot_dist > optimalRange * 2) return -INF;

        const float shot = (soakingPower / (shot_dist <= optimalRange ? 1.0 : 2.0)) * (cover[r][c][target_r][target_c] - hunkered) / 4;
        const float wet_score = wetness + shot >= 100 ? 5 : (wetness / 100);
        return shot + wet_score;
    }

    float splash_score(const Agent A[], int r, int c, bool can_move) const {
        if ((can_move ? dist_after_move(r, c) : dist(r, c)) > 4) return -INF;
        if (splashBombs == 0) return -INF;
        float score = 0;
        for (int i = 0; i < n_agent; ++i) {
            if (!A[i].alive) continue;
            if (A[i].r == r && A[i].c == c) {
                score += SPLASH_POWER * (A[i].player == player ? -2 : +1);
            }
            if (A[i].adj(r, c)) {
                score += SPLASH_POWER * (A[i].player == player ? -1 : +1) / 2.0;
            }
        }
        return score;
    }

    // TODO consider controlled territory
    float position_score(int r, int c) const {
        return 1.0 / (abs(r - H / 2) + abs(c - W / 2) + 1);
    }

    float danger_to(const Agent A[], int r, int c, int wetness, bool can_move, bool hunkered) const {
        return max({shot_score(r, c, wetness, can_move, hunkered), splash_score(A, r, c, can_move), 0.0f});
    }

    Move find_move(Agent A[]) {
        float hunker_danger = 0;
        float base_danger = 0;
        for (int i = 0; i < n_agent; ++i) {
            if (A[i].player != my_id && A[i].alive) {
                hunker_danger += A[i].danger_to(A, r, c, wetness, true, true);
                base_danger += A[i].danger_to(A, r, c, wetness, true, false);
                // TODO avoid multiple agents getting splashed at once
            }
        }

        cerr << agentId << " hunker " << hunker_danger << " base " << base_danger << endl;

        int r0 = r, c0 = c;
        Move best(agentId, r, c, HUNKER_DOWN, -1, -1, -1, position_score(r, c) - hunker_danger);
        for (int d0 = 0; d0 < 5; ++d0) {
            this->r = r0 + chr[d0];
            this->c = c0 + chc[d0];
            if (r < 0 || r >= H || c < 0 || c >= W || G[r][c].tile_type != EMPTY) continue;

            for (int i = 0; i < n_agent; ++i) {
                if (A[i].player == my_id || !A[i].alive) continue;

                float old_danger = A[i].danger_to(A, r0, c0, wetness, true, false);

                // Initialize assuming enemy is hunkered down
                float shot = shot_score(A[i].r, A[i].c, A[i].wetness, false, true) - (base_danger - old_danger);
                float splash = splash_score(A, A[i].r, A[i].c, false) - (base_danger - old_danger);

                int r1 = A[i].r, c1 = A[i].c;
                for (int d1 = 0; d1 < 5; ++d1) {
                    A[i].r = r1 + chr[d1];
                    A[i].c = c1 + chc[d1];
                    if (A[i].r < 0 || A[i].r >= H || A[i].c < 0 || A[i].c >= W || G[A[i].r][A[i].c].tile_type != EMPTY) continue;

                    float new_danger = A[i].danger_to(A, r, c, wetness, false, false);
                    float danger = base_danger - old_danger + new_danger;

                    float shot_sc = shot_score(A[i].r, A[i].c, A[i].wetness, false, false) - danger;
                    float splash_sc = splash_score(A, A[i].r, A[i].c, false) - danger;

                    chmn(shot, shot_sc);
                    chmn(splash, splash_sc);

                    cerr << agentId << ' ' << r << ' ' << c << " " << A[i].agentId << ' ' << A[i].r << ' ' << A[i].c << " shot " << shot_sc << " splash " << splash_sc << " move " << -danger << endl;
                }

                shot += position_score(r, c);
                splash += position_score(r, c);

                if (best.score < shot) {
                    best = Move(agentId, r, c, SHOOT, A[i].agentId, -1, -1, shot);
                }
                if (best.score < splash) {
                    best = Move(agentId, r, c, SPLASH, -1, A[i].r, A[i].c, splash);
                }

                cerr << agentId << ' ' << r << ' ' << c << " shot " << shot << " splash " << splash << " best " << best.score << endl;
            }
        }

        if (base_danger == 0 && best.score <= 1) {
            int nearest_dist = INF;
            int nearest_r = -1, nearest_c = -1;
            for (int i =0; i < n_agent; ++i) {
                if (A[i].player != my_id && A[i].alive && chmn(nearest_dist, A[i].dist(r, c))) {
                    nearest_r = A[i].r;
                    nearest_c = A[i].c;
                }
            }
            best = Move(agentId, nearest_r, nearest_c, MOVE, -1, -1, -1, position_score(nearest_r, nearest_c));
        }
        return best;
    }
};

Agent A[MAX_AGENT];

void play() {
    for (int i = 0; i < n_agent; ++i) {
        if (A[i].player == my_id && A[i].alive) {
            Move best = A[i].find_move(A);
            cout << best << endl;
        }
    }
}

void calculate_cover() {
    for (int r0 = 0; r0 < H; ++r0) {
        for (int c0 = 0; c0 < W; ++c0) {
            for (int r1 = 0; r1 < H; ++r1) {
                for (int c1 = 0; c1 < W; ++c1) {
                    cover[r0][c0][r1][c1] = 4;
                }
            }
            for (int r1 = 0; r1 < H; ++r1) {
                for (int c1 = 0; c1 < W; ++c1) {
                    const int dist = abs(r0 - r1) + abs(c0 - c1);
                    if (G[r1][c1].tile_type != EMPTY && dist > 1) {
                        const int rr = r1 + sign(r1 - r0);
                        const int cc = c1 + sign(c1 - c0);
                        if (rr != r1 && 0 <= rr && rr < H && 0 <= c1 && c1 < W) {
                            chmn(cover[r0][c0][rr][c1], 3 - G[r1][c1].tile_type);
                        }
                        if (cc != c1 && 0 <= cc && cc < W && 0 <= r1 && r1 < H) {
                            chmn(cover[r0][c0][r1][cc], 3 - G[r1][c1].tile_type);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    cin >> my_id;
    cin >> n_agent;

    map<int, int> id_map;

    for (int i = 0; i < n_agent; ++i) {
        A[i].idx = i;
        cin >> A[i].agentId >> A[i].player >> A[i].shootCooldown >> A[i].optimalRange >> A[i].soakingPower >> A[i].splashBombs;
        id_map[A[i].agentId] = i;
    }
    cin >> W >> H;
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            cin >> G[r][c].c >> G[r][c].r >> G[r][c].tile_type;
        }
    }

    calculate_cover();

    while (true) {
        for (int i = 0; i < n_agent; ++i) {
            A[i].alive = false;
        }
        int agent_count;
        cin >> agent_count;
        for (int i = 0; i < agent_count; ++i) {
            int agent_id;
            cin >> agent_id;
            int agent_idx = id_map[agent_id];
            A[agent_idx].alive = true;

            cin >> A[agent_idx].c >> A[agent_idx].r >> A[agent_idx].cooldown >> A[agent_idx].splashBombs >> A[agent_idx].wetness;
        }

        int my_agent_count;
        cin >> my_agent_count;

        play();
    }
}
