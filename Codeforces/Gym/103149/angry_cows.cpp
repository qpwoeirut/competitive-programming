//angry_cows.cpp created at 09/05/21 21:33:39

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define eb emplace_back

using ll=long long;
using pll=pair<ll,ll>;

const int MN = 300005;
const ll INF = 2e18;
const short COW = 1;
const short HIKE = 2;

ll N, M;
ll A[MN];

vector<pll> adj[MN];

ll dist[MN];
ll ndist[MN];
void calc_dist() {
    fill(dist, dist+N, INF);

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for (int i=0; i<N; ++i) {
        if (A[i] == 1) {
            dist[i] = 0;
            pq.emplace(dist[i], i);
        }
    }
    while (pq.size() > 0) {
        const pll p = pq.top(); pq.pop();
        if (dist[p.se] < p.fi) continue;
        for (const pll& e: adj[p.se]) {
            if (dist[e.fi] > p.fi + e.se) {
                dist[e.fi] = p.fi + e.se;
                pq.emplace(dist[e.fi], e.fi);
            }
        }
    }
    for (int i=0; i<N; ++i) {
        if (A[i] == -1) {
            ndist[i] = INF;
            continue;
        }
        for (const pll& e: adj[i]) {
            if (A[e.fi] == -1) {
                ndist[i] = INF;
            } else ndist[i] = max(ndist[i], dist[e.fi]);
        }
    }
}

short reach[MN];
void dfs(const int u, const int val, const int r) {
    reach[u] |= r;
    for (const pll& e: adj[u]) {
        if ((reach[e.fi] & r) == r || A[e.fi] == -val) continue;
        dfs(e.fi, val, r);
    }
}
void simplify_unused() {
    for (int i=0; i<N; ++i) {
        if (A[i] == -1) dfs(i, -1, COW);
        else if (A[i] == 1) dfs(i, 1, HIKE);
    }
    for (int i=0; i<N; ++i) {
        if (reach[i] == COW) A[i] = -1;
        else if (reach[i] == HIKE) A[i] = 1;
    }
}

int par[MN], sz[MN];
int root(const int u) {
    return par[u] == u ? u : par[u] = root(par[u]);
}
bool join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return false;

    if (sz[ru] < sz[rv]) swap(ru, rv);
    sz[ru] += sz[rv];
    par[rv] = par[v] = ru;
    return true;
}

bool was_wall[MN];
bool inside[MN];

void print_ans(const set<pll>& s) {
    cout << s.size() << '\n';
    for (const pll& p: s) {
        if (p != *s.begin()) cout << ' ';
        cout << p.se + 1;
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<M; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        --a; --b;
        adj[a].eb(b, l);
        adj[b].eb(a, l);
    }

    calc_dist();
    simplify_unused();

    fill(was_wall, was_wall+N, false);
    set<pll> wall;
    for (int i=0; i<N; ++i) {
        if (A[i] == 1) {
            for (const pll& e: adj[i]) {
                if (A[e.fi] == -1) {
                    cout << "-1\n";
                    return 0;
                }
                if (A[e.fi] == 0) {
                    was_wall[e.fi] = true;
                    wall.emplace(ndist[e.fi], e.fi);
                }
            }
        }
    }

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }
    int groups = 0;
    for (int i=0; i<N; ++i) {
        if (A[i] == 1) {
            inside[i] = true;
            ++groups;
        }
        for (const pll& e: adj[i]) {
            if (A[i] == 1 && A[e.fi] == 1) {
                groups -= join(i, e.fi);
            }
        }
    }
    //print_ans(wall);

    if (groups == 1) {
        print_ans(wall);
        return 0;
    }

    while (wall.size() > 0) {
        const int u = wall.begin()->se;
        if (wall.begin()->fi == INF) {
            cout << "-1\n";
            return 0;
        }
        inside[u] = true;
        wall.erase(wall.begin());

        ++groups;
        for (const pll& e: adj[u]) {
            //cerr << "e: " << e.fi << ' ' << e.se << endl;
            if (inside[e.fi]) {
                groups -= join(u, e.fi);
                continue;
            }
            if (was_wall[e.fi]) continue;
            was_wall[e.fi] = true;
            wall.emplace(ndist[e.fi], e.fi);
        }

        //cerr << "u,g: " << u << ' ' << groups << endl;
        //print_ans(wall);

        if (groups == 1) {
            print_ans(wall);
            return 0;
        }
    }

    cout << "-1\n";
}

