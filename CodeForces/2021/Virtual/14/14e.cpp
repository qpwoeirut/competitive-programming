//14e.cpp created at 10/30/21 20:21:44

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
const int MN = 40;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

ll dp[MN][MN][MN][5][5];

void solve(int testcase) {
    cin >> N >> K;

    for (int i=1; i<=4; ++i) {
        for (int j=1; j<=4; ++j) {
            dp[2][0][0][i][j] = i != j;
        }
    }

    for (int i=2; i<N; ++i) {
        for (int p=0; p<=K; ++p) {
            for (int v=0; v<K; ++v) {
                for (int oy=1; oy<=4; ++oy) {
                    for (int y=1; y<=4; ++y) {
                        for (int ny=1; ny<=4; ++ny) {
                            if (oy == y || y == ny) continue;
                            if (oy < y && y > ny) {
                                dp[i+1][p+1][v][y][ny] += dp[i][p][v][oy][y];
                            } else if (oy > y && y < ny) {
                                dp[i+1][p][v+1][y][ny] += dp[i][p][v][oy][y];
                            } else {
                                dp[i+1][p][v][y][ny] += dp[i][p][v][oy][y];
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i=2; i<=N; ++i) {
        for (int p=0; p<=K; ++p) {
            for (int v=0; v<K; ++v) {
                for (int y=1; y<=4; ++y) {
                    for (int yy=1; yy<=4; ++yy) {
                        debug(i, p, v, y, yy, dp[i][p][v][y][yy]);
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int i=1; i<=4; ++i) {
        for (int j=1; j<=4; ++j) {
            if (i == j) continue;
            ans += dp[N][K][K-1][i][j];
        }
    }

    cout << ans << '\n';
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
dp[0] is unused
for one/two points there are no peaks or valleys
dp[n][peaks][valleys][prev]
answer is sum of all dp[N][T][T-1][1..4]

20 * 10 * 10 * 4
*/