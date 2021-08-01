//squid_art.cpp created at 06/12/21 08:19:59

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
const int MN = 1001001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN], B[MN];
string G[MN];
set<ll> adj[MN], tr[MN];
string S, T;

ll color[MN];

void dfs(int u, int m) {
    B[u] = m;
    for (const int v: adj[u]) {
        if (B[v] == 0 && A[u] == A[v]) dfs(v, m);
    }
}

ll dist[2][MN];
void mark_dist(int u, int d, int i) {
    dist[i][u] = d;
    for (int v: tr[u]) {
        if (dist[i][v] > d+1) mark_dist(v, d+1, i);
    }
}

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> G[i];
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            const int idx = i * M + j;
            A[idx] = G[i][j] - '0';

            if (i) adj[idx].ins(idx - M);
            if (i+1 < N) adj[idx].ins(idx + M);

            if (j) adj[idx].ins(idx - 1);
            if (j+1 < M) adj[idx].ins(idx + 1);

            if (i & 1) {
                if (j) {
                    if (i) adj[idx].ins(idx - M - 1);
                    if (i+1 < N) adj[idx].ins(idx + M - 1);
                }
            } else {
                if (j+1 < M) {
                    if (i) adj[idx].ins(idx - M + 1);
                    if (i+1 < N) adj[idx].ins(idx + M + 1);
                }
            }
        }
    }

    N = N * M;

    for (int i=0; i<N; ++i) {
        if (B[i] == 0) dfs(i, ++K);
    }
    for (int i=0; i<N; ++i) {
        for (const int v: adj[i]) if (B[i] != B[v]) tr[B[i] - 1].ins(B[v] - 1);
        color[B[i] - 1] = A[i];
    }
    debug1(color, K);
    debug1(B, N);
    debug1(tr, K);

    fill(dist[0], dist[0]+K, INF);
    fill(dist[1], dist[1]+K, INF);
    mark_dist(0, 0, 1);
    const int d1 = max_element(dist[1], dist[1]+K) - dist[1];

    mark_dist(d1, 0, 0);
    const int d2 = max_element(dist[0], dist[0]+K) - dist[0];

    fill(dist[1], dist[1]+K, INF);
    mark_dist(d2, 0, 1);

    const int diam = dist[0][d2];
    debug(diam, d1, d2);
    debug2(dist, 2, K);
    debug(dist[0][d2], dist[1][d1]);
    assert(diam == dist[1][d1]);

    // https://codeforces.com/contest/734/problem/E
    const int moves_to_same = (diam + 1) / 2;
    bool extra = true;
    for (int i=0; i<K; ++i) {
        if (dist[0][i] <= moves_to_same && dist[1][i] <= moves_to_same) {
            debug(i, color[i]);
            if (((color[i] ^ moves_to_same) & 1)) extra = false;
        }
    }

    debug(moves_to_same, extra);
    cout << moves_to_same + extra << '\n';
}
        

int main() {
    setIO();
    
    ll TEST_COUNT = 1;
    
    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
/*
6 10
0100000001
0011010100
1001101101
1010011010
0011101101
0101001011

*/
