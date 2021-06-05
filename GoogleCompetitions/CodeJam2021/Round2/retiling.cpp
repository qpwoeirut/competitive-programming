//retiling.cpp created at 05/15/21 08:39:25

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

#define pb push_back
#define ins insert

#define fi first
#define se second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

using ull = unsigned long long;
using dbl = long double;
using pib = pair<int,bool>;
using plb = pair<ll,bool>;
using pdd = pair<dbl,dbl>;
using mii = map<int,int>;
using mll = map<ll,ll>;
using mci = map<char,int>;
using msi = map<string,int>;
using mss = map<string,string>;

template <class T> using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

#ifdef DELETE_THIS_IN_CASE_OF_GEO
const dbl EPS = 1e-16;

#define x real()
#define y imag()

typedef PUT_SMTH_HERE _t; 
typedef complex<_t> pt;

template <class T> string to_string(const complex<T>& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

namespace std {
    inline bool operator<(const pt& a, const pt& b) {
        if (abs(a.x - b.x) > EPS) return a.x < b.x;
        if (abs(a.y - b.y) > EPS) return a.y < b.y;
        return false;
    }
}

struct Line {
    pt p1, p2;
    Line() {
        p1 = p2 = pt(0, 0);
    }
    Line(const pt& _p1, const pt& _p2) {
        p1 = min(_p1, _p2);
        p2 = max(_p1, _p2);
    }
};

// (hopefully) returns +1 for counterclockwise turn, -1 for clockwise turn, 0 for collinear
int ccw(const pt& a, const pt& b, const pt& c) {
    const _t dx1 = b.x - a.x, dy1 = b.y - a.y;
    const _t dx2 = c.x - a.x, dy2 = c.y - a.y;
    if (dx1 * dy2 < dx2 * dy1) return +1;
    if (dx1 * dy2 > dx2 * dy1) return -1;
    return 0;
}
#endif

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int INIT = 1001001001;
const int MN = 100;
const int LG = 24;
const ll INF = 2e18 + 1;

const ll MULT = 100;

ll R, C;
ll A[MN], B[MN];
int G[MN][MN], tar[MN][MN];
//set<pll> adj[MULT * MULT * MULT];
//string S, T;
ll F, S;

ll dist[MN][MN];
ll mat[MN << 1][MN << 1];

struct Edge {
    int u, v;
    ll cost;

    Edge(const int _u, const int _v, const ll _cost) {
        u = _u;
        v = _v;
        cost = _cost;
    }
};

vector<Edge> edges;

void bfs(const int r, const int c) {
    debug(r, c);
    for (int i=0; i<R; ++i) {
        for (int j=0; j<C; ++j) {
            dist[i][j] = INF;
        }
    }
    dist[r][c] = 0;
    queue<pii> q;
    q.emplace(r, c);
    while (q.size() > 0) {
        const pii p = q.front();
        q.pop();

        for (int i=0; i<4; ++i) {
            const int nr = p.fi + chr[i], nc = p.se + chc[i];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (G[r][c] == G[nr][nc]) {
                if (chmn(dist[nr][nc], dist[p.fi][p.se] + 1)) {
                    q.emplace(nr, nc);
                }
            } else if (G[r][c] == tar[nr][nc]) {
                chmn(dist[nr][nc], dist[p.fi][p.se] + 1);
                edges.emplace_back(r * MULT + c, nr * MULT + nc, dist[nr][nc]);
            }
        }
    }
}

ll hungarian() {
    int n = MN * 2 + 1, m = MN * 2 + 1;
    vector<ll> u(n), v(m), p(m);
    for (int i=1; i<n; ++i) {
        p[0] = i;
        ll j0 = 0;
        vector<ll> dist(m, INF), pre(m, -1);
        vector<bool> done(m + 1);
        do {
            done[j0] = true;
            ll i0 = p[j0], j1, delta = INF;
            for (int j=1; j<m; ++j) {
                if (!done[j]) {
                    auto cur = mat[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
                    if (dist[j] < delta) delta = dist[j], j1 = j;
                }
            }
            for (int j=0; j<m; ++j) {
                if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);

        while(j0) {
            ll j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }

    return -v[0];
}

void solve(int testcase) {
    cin >> R >> C >> F >> S;
    edges.clear();
    for (int i=0; i<R; ++i) {
        for (int j=0; j<C; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == 'M';
        }
    }
    for (int i=0; i<R; ++i) {
        for (int j=0; j<C; ++j) {
            char c;
            cin >> c;
            tar[i][j] = c == 'M';
        }
    }
    debug2(G, R, C);
    debug2(tar, R, C);

    vector<ll> bad[2];
    for (int i=0; i<R; ++i) {
        for (int j=0; j<C; ++j) {
            if (G[i][j] != tar[i][j]) {
                bfs(i, j);
                bad[G[i][j]].pb(i * MULT + j);
            }
        }
    }

    for (int i=0; i<MN*2; ++i) {
        for (int j=0; j<MN*2; ++j) {
            mat[i][j] = INF;
        }
    }
    for (const Edge& e: edges) {
        int u = e.u;
        int v = e.v;
        if (G[u / MULT][u % MULT]) swap(u, v);

        u = (LB(all(bad[0]), u) - bad[0].begin());
        v = (LB(all(bad[1]), v) - bad[1].begin());
        mat[u][v] = mat[v][u] = e.cost * F;
    }

    for (int i=0; i<MN; ++i) {
        for (int j=MN; j<MN*2; ++j) {
            mat[i][j] = S;
        }
    }
    for (int i=MN; i<MN*2; ++i) {
        for (int j=0; j<MN; ++j) {
            mat[i][j] = S;
        }
        for (int j=MN; j<MN*2; ++j) {
            mat[i][j] = 0;
        }
    }

    ll ans = hungarian();

    cout << "Case #" << testcase << ": " << hungarian() << '\n';
}
        

int main() {
    setIO();
    
    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;
    
    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
