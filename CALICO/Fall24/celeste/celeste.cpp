//celeste.cpp created at 11/16/24 16:57:41
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

#define pb push_back
#define eb emplace_back
#define ins insert
#define emp emplace

#define fi first
#define se second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

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

template <class T> using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

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
const int MN = 1001001;

ll N, M, K;

struct State {
    ll r, c;
    bool red;
    ll cost;

    const bool operator<(const State& o) const {
        // ignore cost
        return r < o.r || (r == o.r && (c < o.c || (c == o.c && red < o.red)));
    }

    int pack() {
        return (r * (M + 1) + c) * 2 + red;
    }
};

using vvi = vector<vector<int>>;

State dash_state(const State& state, int d, const vvi& wct_r, const vvi& wct_c, const vvi& crystal) {
    State ns = state;
    if (d == 2) {
        //debug(d, state.r, state.c, wct_c[ns.c]);
        auto cur = wct_c[ns.c].begin() + ns.r;
        ns.r = upper_bound(cur, wct_c[ns.c].end(), *cur) - wct_c[ns.c].begin() - 1;
        ns.r = min(ns.r, state.r + K);
    } else if (d == 1) {
        //debug(d, state.r, state.c, wct_r[ns.r]);
        auto cur = wct_r[ns.r].begin() + ns.c;
        ns.c = upper_bound(cur, wct_r[ns.r].end(), *cur) - wct_r[ns.r].begin() - 1;
        ns.c = min(ns.c, state.c + K);
    } else if (d == 0) {
        //debug(d, state.r, state.c, wct_c[ns.c]);
        auto cur = wct_c[ns.c].begin() + ns.r;
        ns.r = lower_bound(wct_c[ns.c].begin(), cur + 1, *cur) - wct_c[ns.c].begin() + 1;
        ns.r = max(ns.r, state.r - K);
    } else if (d == 3) {
        //debug(d, state.r, state.c, wct_r[ns.r]);
        auto cur = wct_r[ns.r].begin() + ns.c;
        ns.c = lower_bound(wct_r[ns.r].begin(), cur + 1, *cur) - wct_r[ns.r].begin() + 1;
        ns.c = max(ns.c, state.c - K);
    } else assert(false);

    ll sr = state.r + chr[d], sc = state.c + chc[d];
    if (sr < 0 || sr >= N || sc < 0 || sc >= M) return state;

    int r0 = min(ns.r, sr), c0 = min(ns.c, sc);
    int r1 = max(ns.r, sr) + 1, c1 = max(ns.c, sc) + 1;
    ns.red = crystal[r1][c1] - crystal[r1][c0] - crystal[r0][c1] + crystal[r0][c0] != 0;
    //debug(r0, c0, r1, c1);
    //debug(crystal[r0][c0], crystal[r0][c1], crystal[r1][c0], crystal[r1][c1]);
    //debug(d, state.r, state.c, ns.r, ns.c, ns.red);
    return ns;
}

const int MAX = 1e7;
bitset<MAX> vis;

void solve(int testcase) {
    cin >> N >> M >> K;
    vector<string> G(N);
    vector<vector<int>> wct_r(N, vector<int>(M));
    vector<vector<int>> wct_c(M, vector<int>(N));

    for (int i=0; i<N; ++i) {
        cin >> G[i];
        for (int j=0; j<M; ++j) {
            wct_r[i][j] = (j ? wct_r[i][j-1] : 0) + (G[i][j] == '#');
        }
    }
    for (int j=0; j<M; ++j) {
        for (int i=0; i<N; ++i) {
            wct_c[j][i] = (i ? wct_c[j][i-1] : 0) + (G[i][j] == '#');
        }
    }

    vvi crystal(N+1, vector<int>(M+1));
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=M; ++j) {
            crystal[i][j] = crystal[i-1][j] + crystal[i][j-1] - crystal[i-1][j-1] + (G[i - 1][j - 1] == '*');
        }
    }
    vis.reset();

    State start;
    start.red = true;
    start.cost = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (G[i][j] == 'S') {
                start.r = i;
                start.c = j;
            }
        }
    }
    queue<State> q;
    q.push(start);
    while (q.size() > 0) {
        const State state = q.front(); q.pop();
        if (G[state.r][state.c] == 'E') {
            cout << state.cost << '\n';
            return;
        }
        for (int d=0; d<4; ++d) {
            State ns = state;
            ns.r += chr[d];
            ns.c += chc[d];
            if (ns.r < 0 || ns.r >= N || ns.c < 0 || ns.c >= M || G[ns.r][ns.c] == '#') continue;
            if (G[ns.r][ns.c] == '*') ns.red = true;
            ns.cost = state.cost + 1;

            if (!vis[ns.pack()]) {
                vis[ns.pack()] = true;
                q.push(ns);
            }
        }

        if (!state.red) continue;
        for (int d=0; d<4; ++d) {
            State ns = dash_state(state, d, wct_r, wct_c, crystal);

            assert(!(ns.r < 0 || ns.r >= N || ns.c < 0 || ns.c >= M || G[ns.r][ns.c] == '#'));
            ns.cost = state.cost + 1;

            if (!vis[ns.pack()]) {
                vis[ns.pack()] = true;
                q.push(ns);
            }
        }
    }

    cout << "-1\n";
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
/*
8 13 100
#############
#.####*....*#
#.####.####.#
#S..........#
#.####.######
#.####.######
#.#........E#
#############
*/
