//peaks.cpp created at 02/22/21 20:28:34

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

struct Item {
    int dist;
    int node;
    int src;

    Item(const int _dist, const int _node, const int _src) {
        dist = _dist;
        node = _node;
        src = _src;
    }

    inline const bool operator<(const Item& o) const {
        return dist < o.dist;
    }
};

const int MN = 2005;
const int MX = 100005;

int N, M;
int G[MN][MN];

int par[MX];
int sz[MX];

int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
void join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return;

    if (sz[ru] < sz[rv]) swap(ru, rv);
    sz[ru] += sz[rv];

    par[rv] = ru;
}

set<int> adj[MX];
bool peak[MX];
int ans[MX];

const int chr[8] = {-1, -1, -1,  0,  1,  1,  1,  0};
const int chc[8] = {-1,  0,  1,  1,  1,  0, -1, -1};

vector<int> H[1001001];

int par2[MX], sz2[MX], height[MX];
set<pii> unanswered[MX];
int root2(const int u) {
    return u == par2[u] ? u : par2[u] = root2(par2[u]);
}
void join2(const int u, const int v) {
    int ru = root2(u), rv = root2(v);
    if (ru == rv) return;

    if (sz2[ru] < sz2[rv]) swap(ru, rv);
    sz2[ru] += sz2[rv];
    par2[rv] = ru;
    if (unanswered[ru].size() < unanswered[rv].size()) swap(unanswered[ru], unanswered[rv]);
    unanswered[ru].insert(unanswered[rv].begin(), unanswered[rv].end());

    height[ru] = max(height[ru], height[rv]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
            par[i * M + j] = i * M + j;
            sz[i * M + j] = 1;
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            for (int k=0; k<8; ++k) {
                const int r = i + chr[k], c = j + chc[k];
                if (0 <= r && r < N && 0 <= c && c < M && G[r][c] == G[i][j]) join(r * M + c, i * M + j);
            }
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            const int rt = root(i * M + j);

            if (rt == i * M + j) {
                H[G[i][j]].push_back(i * M + j);
            }

            for (int k=0; k<8; ++k) {
                const int r = i + chr[k], c = j + chc[k];
                if (0 <= r && r < N && 0 <= c && c < M && G[r][c] != G[i][j]) {
                    const int rt2 = root(r * M + c);
                    if (rt != rt2) {
                        adj[rt].insert(rt2);
                        adj[rt2].insert(rt);
                    }
                }
            }
        }
    }
    
    for (int i=0; i<N*M; ++i) {
        if (root(i) == i) {
            int tallest = 0;
            for (const int v: adj[i]) {
                tallest = max(tallest, G[v / M][v % M]);
            }
            if (tallest < G[i / M][i % M]) {
                peak[i] = true;
            } else {
                peak[i] = false;
            }
        }
    }

    for (int i=0; i<N*M; ++i) {
        int r = root(i);
        par2[i] = r;
        height[i] = G[r / M][r % M];
    }
    for (int i=0; i<N*M; ++i) {
        if (peak[i]) unanswered[root2(i)].emplace(height[i], i);
    }

    for (int i=1e6; i>0; --i) {
        for (const int u: H[i]) {
            for (const int v: adj[u]) {
                if (G[u / M][u % M] < G[v / M][v % M]) {
                    join2(u, v);
                    const int ru = root2(u);
                    for (auto it = unanswered[ru].begin(); it!=unanswered[ru].end(); ) {
                        //cerr << ru << ' ' << *it << ' ' << height[ru] << ' ' << G[*it / M][*it % M] << endl;
                        if (height[ru] > G[it->se / M][it->se % M]) {
                            ans[it->se] = i;
                            it = unanswered[ru].erase(it);
                        } else break;
                    }
                }
            }
        }
    }

    vector<pii> answer;
    for (int i=0; i<N*M; ++i) {
        if (peak[i]) {
            answer.emplace_back(G[i/M][i%M], ans[i]);
        }
    }
    sort(answer.begin(), answer.end(), greater<pii>());

    cout << answer.size() << '\n';
    for (const pii& p: answer) {
        cout << p.fi << ' ' << p.se << '\n';
    }
}

/*
6 6
21 16 9 11 6 7
21 21 10 14 15 9
18 20 8 9 13 14
11 10 9 9 8 13
8 12 12 14 13 8
7 13 12 9 5 1
*/
