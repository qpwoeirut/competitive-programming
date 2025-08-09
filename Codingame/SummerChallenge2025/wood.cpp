#include <iostream>
#include <map>

using namespace std;

bool chmn(int &a, int b) {
    return a > b ? a = b, true : false;
}

bool chmx(int &a, int b) {
    return a < b ? a = b, true : false;
}

int sign(int a) {
    return a > 0 ? 1 : a < 0 ? -1 : 0;
}

const int chr[] = {0, 1, 0, -1, 0};
const int chc[] = {1, 0, -1, 0, 0};

const int MAX_W = 100;
const int MAX_H = 100;
const int MAX_AGENT = 100;

const int EMPTY = 0;
const int LOW = 1;
const int HIGH = 2;

const int SPLASH_POWER = 30;

int my_id;
int W, H;
int n_agent;

int cover[MAX_AGENT][MAX_H][MAX_W];
int cover_at(int r, int c);
int splash_score(int r, int c);

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

    int find_cover(int& best_r, int& best_c) const {
        int best = 4 * MAX_AGENT;
        for (int d = 0; d < 5; ++d) {
            const int rr = r + chr[d];
            const int cc = c + chc[d];
            if (0 <= rr && rr < H && 0 <= cc && cc < W && G[rr][cc].tile_type == EMPTY) {
                if (chmn(best, cover_at(rr, cc))) {
                    best_r = rr;
                    best_c = cc;
                }
            }
        }
        return best;
    }

    int find_shot_target(const Agent A[], int& target) const {
        int best = 0;
        for (int i = 0; i < n_agent; ++i) {
            if (A[i].player != my_id && A[i].alive && A[i].dist(r, c) <= optimalRange) {
                if (chmx(best, cover[idx][A[i].r][A[i].c])) {
                    target = A[i].agentId;
                }
            }
        }
        return best;
    }

    int find_splash_target(const Agent A[], bool global, int& target_r, int& target_c) const {
        int best = 0;
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                if ((global || dist(r, c) <= 4) && chmx(best, splash_score(r, c))) {
                    target_r = r;
                    target_c = c;
                }
            }
        }
        return best;
    }
};


Agent A[MAX_AGENT];

void play() {
    // Objective 1
    // for (int i = 0; i < n_agent; ++i) {
    //     cout << A[i].agentId << ";MOVE 6 " << 1+i+i << endl;
    // }

    // Objective 2
    // int wettest_enemy = -1;
    // for (int i = 0; i < n_agent; ++i) {
    //     if (A[i].player != my_id && A[i].alive) {
    //         if (wettest_enemy == -1 || A[i].wetness > A[wettest_enemy].wetness) {
    //             wettest_enemy = i;
    //         }
    //     }
    // }
    // for (int i = 0; i < n_agent; ++i) {
    //     if (A[i].player == my_id && A[i].alive) {
    //         cout << A[i].agentId << ";SHOOT " << A[wettest_enemy].agentId << endl;
    //     }
    // }

    // Objective 3
    // for (int i = 0; i < n_agent; ++i) {
    //     if (A[i].player == my_id && A[i].alive) {
    //         int best_r = -1, best_c = -1;
    //         A[i].find_cover(best_r, best_c);
    //         int target = -1;
    //         A[i].find_shot_target(A, target);
    //         cout << A[i].agentId << ";MOVE " << best_c << " " << best_r << ";SHOOT " << target << endl;
    //     }
    // }

    // Objective 4
    for (int i = 0; i < n_agent; ++i) {
        if (A[i].player == my_id && A[i].alive) {
            int target_r = -1, target_c = -1;
            if (A[i].find_splash_target(A, true, target_r, target_c) > 0) {
                if (A[i].dist(target_r, target_c) <= 4) {
                    cout << A[i].agentId << ";THROW " << target_c << " " << target_r << endl;
                } else {
                    cout << A[i].agentId << ";MOVE " << target_c << " " << target_r << endl;
                }
            }
        }
    }
}

void calculate_cover() {
    for (int i = 0; i < n_agent; ++i) {
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                cover[i][r][c] = 4;
            }   
        }

        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                if (G[r][c].tile_type != EMPTY && A[i].dist(r, c) > 1) {
                    const int rr = r + sign(r - A[i].r);
                    const int cc = c + sign(c - A[i].c);
                    if (rr != r && 0 <= rr && rr < H && 0 <= c && c < W) {
                        chmn(cover[i][rr][c], 3 - G[r][c].tile_type);
                    }
                    if (cc != c && 0 <= cc && cc < W && 0 <= r && r < H) {
                        chmn(cover[i][r][cc], 3 - G[r][c].tile_type);
                    }
                }
            }
        }
    }
}

int cover_at(int r, int c) {
    int cover_here = 0;
    for (int i = 0; i < n_agent; ++i) {
        if (A[i].player != my_id && A[i].alive && A[i].dist(r, c) <= A[i].optimalRange) {
            cover_here += cover[i][r][c];
        }
    }
    return cover_here;
}

int splash_score(int r, int c) {
    int splash_here = 0;
    for (int i = 0; i < n_agent; ++i) {
        if (A[i].alive && A[i].adj(r, c)) {
            splash_here += A[i].player != my_id ? SPLASH_POWER : -SPLASH_POWER;
        }
    }
    return splash_here;
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

        calculate_cover();
        play();
    }
}
