//machu-pichu.cpp created at 08/25/25 22:43:50
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pcll = pair<const ll,ll>;

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
using _t=PUT_SMTH_HERE;
using pt=complex<_t>;

const dbl EPS = 1e-16;

#define x real()
#define y imag()

namespace std {
    inline bool operator<(const pt& a, const pt& b) {
        if (abs(a.x - b.x) > EPS) return a.x < b.x;
        if (abs(a.y - b.y) > EPS) return a.y < b.y;
        return false;
    }
    inline bool operator>(const pt& a, const pt& b) {
        return b < a;
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
    Line(const _t a, const _t b, const _t c, const _t d) {
        p1 = pt(a, b);
        p2 = pt(c, d);
        if (p1 > p2) swap(p1, p2);
    }
    inline bool operator<(const Line& o) const {
        return p1 < o.p1 || (p1 == o.p1 && p2 < o.p2);
    }
};

namespace std {
    inline bool operator<(const Line& a, const Line& b) {
        return a.p1 < b.p1 || (a.p1 == b.p1 && a.p2 < b.p2);
    }
}

istream& operator>>(istream& is, pt& p) {
    _t a, b;
    is >> a >> b;
    p = pt(a, b);
    return is;
}
istream& operator>>(istream& is, Line& p) {
    _t a, b, c, d;
    is >> a >> b >> c >> d;
    p = Line(a, b, c, d);
    return is;
}

string to_string(const complex<_t>& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}
string to_string(const Line& a) {
    return "(" + to_string(a.p1) + "--" + to_string(a.p2) + ")";
}
#endif

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll INF = 2e18 + 1;
const int INIT = 1001001001;
const int LG = 24;
const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 1005;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

struct Cell {
    int r, c;
    ll h;
};

struct Query {
    ll c, v;
    int idx;
    pll ans;
};

Cell cell[MN*MN];
Query query[MN*MN];

pii par[MN][MN];
pll root(int ur, int uc) {
    return par[ur][uc] == pii(ur, uc) ? pii(ur, uc) : par[ur][uc] = root(par[ur][uc].fi, par[ur][uc].se);
}

void join(int ur, int uc, int vr, int vc) {
    pii ru = root(ur, uc);
    pii rv = root(vr, vc);

    if (ru == rv) return;

    if (ru > rv) swap(ru, rv);
    par[rv.fi][rv.se] = par[ur][uc] = par[vr][vc] = ru;
}

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<=N+1; ++i) {
        for (int j=0; j<=M+1; ++j) {
            G[i][j] = INF;
            par[i][j] = pii(i, j);
        }
    }
    int c_i = 0;
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=M; ++j) {
            cin >> G[i][j];
            cell[c_i].r = i;
            cell[c_i].c = j;
            cell[c_i].h = G[i][j];
            ++c_i;
        }
    }
    sort(cell, cell+N*M, [](const Cell& a, const Cell& b) {
        return a.h < b.h;
    });

    cin >> K;
    for (int i=0; i<K; ++i) {
        cin >> A[i] >> B[i];
    }

    cin >> Q;
    for (int i=0; i<Q; ++i) {
        cin >> query[i].c >> query[i].v;
        query[i].idx = i;
    }
    sort(query, query+Q, [](const Query& a, const Query& b) {
        return a.c < b.c || (a.c == b.c && a.idx < b.idx);
    });

    c_i = 0;
    for (int i=0; i<Q; ++i) {
        while (c_i < N*M && cell[c_i].h <= query[i].c) {
            for (int d=0; d<4; ++d) {
                int nr = cell[c_i].r + chr[d];
                int nc = cell[c_i].c + chc[d];
                if (cell[c_i].h - 1 <= G[nr][nc] && G[nr][nc] <= cell[c_i].h) join(nr, nc, cell[c_i].r, cell[c_i].c);
            }
            ++c_i;
        }

        pll best(INF, INF);
        for (int k=0; k<K; ++k) {
            int ct = 0;
            if (G[A[k]][B[k]] > query[i].c) continue;
            pll rk = root(A[k], B[k]);
            for (int k0=0; k0<K; ++k0) {
                ct += rk == root(A[k0], B[k0]);
            }
            if (ct >= query[i].v) {
                chmn(best, rk);
            }
            debug(A[k], B[k], query[i].c, query[i].v, ct);
        }

        if (best.fi == INF) best = {-1, -1};
        query[i].ans = best;
    }
    sort(query, query+Q, [](const Query& a, const Query& b) {
        return a.idx < b.idx;
    });
    for (int i=0; i<Q; ++i) {
        cout << query[i].ans.fi << ' ' << query[i].ans.se << '\n';
    }
}

int main() {
    setIO();

    ll TEST_COUNT = 1;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}
