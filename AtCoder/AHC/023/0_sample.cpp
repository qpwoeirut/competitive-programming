#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int T, K, H, W, i0;
vector<int> S, D;
vector<vector<bool>> h, v;

void read_input() {
    cin >> T >> H >> W >> i0;
    h.resize(H - 1, vector(W, false));
    for (int i = 0; i < H - 1; ++i) {
        string s; cin >> s;
        for (int j = 0; j < W; ++j) if (s[j] == '1') h[i][j] = true;
    }
    v.resize(H, vector(W - 1, false));
    for (int i = 0; i < H; ++i) {
        string s; cin >> s;
        for (int j = 0; j < W - 1; ++j) if (s[j] == '1') v[i][j] = true;
    }
    cin >> K;
    S.resize(K);
    D.resize(K);
    for (int i = 0; i < K; ++i) cin >> S[i] >> D[i];
}

struct Work {
    int k, i, j, s;
};

bool reachable(int i, int j, const vector<vector<vector<pair<int, int>>>> &adj, const vector<vector<bool>> &used) {
    if (used[i][j] || used[i0][0]) {
        return false;
    } else if (i == i0 && j == 0) {
        return true;
    }
    queue<pair<int, int>> q;
    q.emplace(i0, 0);
    vector visited(H, vector(W, false));
    visited[i0][0] = true;
    while (!q.empty()) {
        const auto [i1, j1] = q.front();
        q.pop();
        for (const auto &[i2, j2] : adj[i1][j1]) {
            if (i2 == i && j2 == j) {
                return true;
            } else if (!used[i2][j2] && !visited[i2][j2]) {
                visited[i2][j2] = true;
                q.emplace(i2, j2);
            }
        }
    }

    return false;
}
                    
bool is_valid_plan(const vector<Work> &plan, const vector<vector<vector<pair<int, int>>>> &adj) {
    vector<vector<Work>> plant_list(T + 1), harvest_list(T + 1);
    for (const Work &w : plan) {
        plant_list[w.s].push_back(w);
        harvest_list[D[w.k]].push_back(w);
    }

    vector used(H, vector(W, false));
    for (int t = 1; t <= T; ++t) {
        // planting phase
        for (const Work &w : plant_list[t]) {
            if (!reachable(w.i, w.j, adj, used)) {
                return false;
            }
        }
        for (const Work &w : plant_list[t]) {
            if (used[w.i][w.j]) {
                return false;
            } else {
                used[w.i][w.j] = true;
            }
        }

        // harvesting phase
        for (const Work &w : harvest_list[t]) {
            used[w.i][w.j] = false;
        }
        for (const Work &w : harvest_list[t]) {
            if (!reachable(w.i, w.j, adj, used)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    read_input();

    // construct a graph
    vector adj(H, vector(W, vector<pair<int, int>>()));
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (i + 1 < H && !h[i][j]) {
                // no waterway between (i, j) and (i + 1, j)
                adj[i][j].emplace_back(i + 1, j);
                adj[i + 1][j].emplace_back(i, j);
            }
            if (j + 1 < W && !v[i][j]) {
                // no waterway between (i, j) and (i, j + 1)
                adj[i][j].emplace_back(i, j + 1);
                adj[i][j + 1].emplace_back(i, j);
            }
        }
    }

    vector<Work> plan;
    for (int k = 0; k < min(K, 10); ++k) {
        // try to plant crop k
        bool found = false;
        for (int i = 0; i < H && !found; ++i) {
            for (int j = 0; j < W && !found; ++j) {
                plan.push_back({k, i, j, S[k]});
                if (!is_valid_plan(plan, adj)) {
                    plan.pop_back();
                } else {
                    found = true;
                }
            }
        }
    }

    // write output
    cout << plan.size() << '\n';
    for (const Work &w : plan) {
        cout << w.k + 1 << ' ' << w.i << ' ' << w.j << ' ' << w.s << '\n';
    }
}
