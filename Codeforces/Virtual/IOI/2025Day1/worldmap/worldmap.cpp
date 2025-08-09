#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;

const int MN = 40;
const int INIT = 9999;

vi adj[MN];
int dist[MN];
bitset<MN> vis;

void dfs(const int u, vi& path) {
    vis[u] = true;
    path.push_back(u);
    for (const int v: adj[u]) {
        if (!vis[v]) {
            dfs(v, path);
            path.push_back(u);
        }
    }
}


vi find_path() {
    vis.reset();
    vi path;
    dfs(0, path);
    while (path.size() > 0) {
        if (count(path.begin(), path.end(), path.back()) > 1) {
            path.pop_back();
        } else {
            break;
        }
    }
    return path;
}

vector<vi> create_map(const int N, const int M, const vi A, const vi B) {
    for (int i=0; i<N; ++i) adj[i].clear();
    for (int i=0; i<M; ++i) {
        adj[A[i] - 1].push_back(B[i] - 1);
        adj[B[i] - 1].push_back(A[i] - 1);
    }

    vi path = find_path();

    bitset<MN> seen;
    seen[path[0]] = true;
    int h = N % 2 ? 2 : 3;
    int w = N % 2 ? 2 : 1;
    bool parity = false;
    for (int i=1; i<path.size(); ++i) {
        if (seen[path[i]]) {
            ++h;
            ++w;
        } else {
            seen[path[i]] = true;
            h += parity ? 3 : 1;
            w += parity ? 1 : 3;
            parity = !parity;
        }
    }
    assert(h == w);

    seen.reset();
    vector<vi> grid(h, vi(w, INIT));
    for (int i=0; i<path.size(); ++i) {
        for (int r=0; r<h; ++r) {
            for (int c=0; c<w; ++c) {
                grid[r][c] = path[i];
            }
        }

        if (!seen[path[i]]) {
            seen[path[i]] = true;
            int z = 0;
            for (const int v: adj[path[i]]) {
                if (find(path.begin(), path.begin() + i, v) == path.begin() + i) {
                    if (seen.count() % 2) {
                        grid[h - 2][z] = v;
                    } else {
                        grid[z][w - 2] = v;
                    }
                    z += 2;
                }
            }

            h -= seen.count() % 2 ? 3 : 1;
            w -= seen.count() % 2 ? 1 : 3;
        } else {
            --h;
            --w;
        }
    }

    for (int r=0; r<grid.size(); ++r) {
        for (int c=0; c<grid[r].size(); ++c) {
            ++grid[r][c];
        }
    }
    return grid;
}

