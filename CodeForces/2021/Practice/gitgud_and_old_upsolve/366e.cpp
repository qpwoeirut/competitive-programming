//366e.cpp created at 04/09/21 16:44:33

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

ll N, M, K, L;
ll A[MN], B[MN];
ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

int ok[10];
int diag[4][MN << 1];
// 0 3
// 2 1

void solve(int testcase) {
    cin >> N >> M >> K >> L;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
        }
    }
    for (int i=0; i<L; ++i) {
        cin >> A[i];
        if (i) ok[A[i-1]] |= 1 << A[i];
    }

    for (int i=0; i<N+M-1; ++i) {
        if (i) diag[0][i] = diag[0][i-1];
        for (int r=0; r<=i; ++r) {
            if (0 <= r && r < N && 0 <= i-r && i-r < M) {
                diag[0][i] |= 1 << G[r][i-r];
            }
        }
    }
    for (int i=N+M-2; i>=0; --i) {
        if (i+1<N+M-1) diag[1][i] = diag[1][i+1];
        for (int r=0; r<=i; ++r) {
            if (0 <= r && r < N && 0 <= i-r && i-r < M) {
                diag[1][i] |= 1 << G[r][i-r];
            }
        }
    }

    for (int i=0; i<N+M-1; ++i) {
        if (i) diag[2][i] = diag[2][i-1];
        for (int r=0; r<=i; ++r) {
            if (0 <= N-r-1 && N-r-1 < N && 0 <= i-r && i-r < M) {
                diag[2][i] |= 1 << G[N-r-1][i-r];
            }
        }
    }
    for (int i=N+M-2; i>=0; --i) {
        if (i+1<N+M-1) diag[3][i] = diag[3][i+1];
        for (int r=0; r<=i; ++r) {
            if (0 <= N-r-1 && N-r-1 < N && 0 <= i-r && i-r < M) {
                diag[3][i] |= 1 << G[N-r-1][i-r];
            }
        }
    }
    //for (int i=0; i<4; ++i) { for (int j=0; j<N+M-1; ++j) { cerr << bitset<8>(diag[i][j]).to_string() << ' '; } cerr << endl; }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            for (int k=0; k<4; ++k) {
                ll lo = 0, hi = N+M-1;
                while (lo < hi) {
                    ll mid = (lo + hi + (k & 1)) >> 1;
                    if (ok[G[i][j]] & diag[k][mid]) {
                        if (k & 1) lo = mid;
                        else hi = mid;
                    } else {
                        if (k & 1) hi = mid - 1;
                        else lo = mid + 1;
                    }
                }

                if (k == 0) {
                    chmx(ans, (i + j) - lo);
                } else if (k == 1) {
                    chmx(ans, lo - (i + j));
                } else if (k == 2) {
                    chmx(ans, (N-i-1 + j) - lo);
                } else if (k == 3) {
                    chmx(ans, lo - (N-i-1 + j));
                } else assert(0);
            }
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
