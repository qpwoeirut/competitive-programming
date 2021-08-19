//aac3p5.cpp created at 08/03/21 17:19:30

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
const int MN = 2001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
//ll A[MN], B[MN];
string G[MN];
pii adj[MN * MN][4];
string S, T;

struct Item {
    ll dist;
    ll r, c;

    Item(const ll _dist, const ll _r, const ll _c) {
        dist = _dist;
        r = _r;
        c = _c;
    }

    inline const bool operator<(const Item& o) const {
        return dist < o.dist || (dist == o.dist || (r < o.r || (r == o.r && c < o.c)));
    }
};

int ans[MN * MN];

void join(const ll r1, const ll c1, const ll r2, const ll c2, const ll dist, const int i) {
    adj[r1*M+c1][i] = pii(r2*M+c2, dist);
}

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> G[i];
    }
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            for (int k=0; k<4; ++k) {
                adj[i*M+j][k] = pii(-1, -1);
            }
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (G[i][j] == '.') continue;
            if (i) {
                if (G[i-1][j] == '#') join(i, j, i-1, j, INIT, 0);
                else {
                    int k = i-1;
                    while (k >= 0 && G[k][j] != '#') --k;
                    if (k >= 0) join(i, j, k, j, i-k-1, 0);
                }
            }
            if (j) {
                if (G[i][j-1] == '#') join(i, j, i, j-1, INIT, 1);
                else {
                    int k = j-1;
                    while (k >= 0 && G[i][k] != '#') --k;
                    if (k >= 0) join(i, j, i, k, j-k-1, 1);
                }
            }
            if (i+1<N) {
                if (G[i+1][j] == '#') join(i, j, i+1, j, INIT, 2);
                else {
                    int k=i+1;
                    while (k < N && G[k][j] != '#') ++k;
                    if (k < N) join(i, j, k, j, k-i-1, 2);
                }
            }
            if (j+1<M) {
                if (G[i][j+1] == '#') join(i, j, i, j+1, INIT, 3);
                else {
                    int k = j+1;
                    while (k < M && G[i][k] != '#') ++k;
                    if (k < M) join(i, j, i, k, k-j-1, 3);
                }
            }
        }
    }

    priority_queue<pii> pq;
    for (int j=0; j<M; ++j) {
        if (G[0][j] == '#') pq.emplace(INIT, j);
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            ans[i*M+j] = -1;
        }
    }

    while (pq.size() > 0) {
        const int dst = pq.top().fi;
        const ll u = pq.top().se; pq.pop();

        if (dst < ans[u]) continue;

        for (int i=0; i<4; ++i) {
            const pii& edge = adj[u][i];
            if (chmx(ans[edge.fi], min(dst, edge.se))) {
                pq.emplace(ans[edge.fi], edge.fi);
            }
        }
    }


    for (int i=0; i<M; ++i) {
        if (i) cout << ' ';
        const ll x = ans[(N-1)*M + i];
        cout << (x == INIT ? 0 : x);
    }
    cout << '\n';
}
        

int main() {
    setIO();
    
    ll TEST_COUNT = 1;
    
    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
