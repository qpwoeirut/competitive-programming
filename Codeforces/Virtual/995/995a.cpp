//995a.cpp created at 07/02/21 22:43:14

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
ll A[4][MN], B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

int ans[MN][3];
void add_move(int val, int r, int c) {
    debug(val, r, c);
    debug2(A, 4, N);
    ans[M][0] = val;
    ans[M][1] = r + 1;
    ans[M][2] = c + 1;
    ++M;
}

void solve(int testcase) {
    cin >> N >> K;
    for (int i=0; i<4; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> A[i][j];
        }
    }

    M = 0;
    int k = 0;
    while (k < K) {
        for (int i=0; i<N; ++i) {
            if (A[0][i] == A[1][i] && A[1][i] != 0) {
                A[1][i] = 0;
                add_move(A[0][i], 0, i);
                ++k;
            }
            if (A[3][i] == A[2][i] && A[2][i] != 0) {
                A[2][i] = 0;
                add_move(A[3][i], 3, i);
                ++k;
            }
        }
        if (M == 0 && K == 2*N) {
            cout << "-1\n";
            return;
        }

        for (int j=0; j+1<N; ++j) {
            if (A[1][j] == 0 && A[1][j+1] != 0) {
                swap(A[1][j], A[1][j+1]);
                add_move(A[1][j], 1, j);

                if (A[0][j] == A[1][j]) {
                    A[1][j] = 0;
                    add_move(A[0][j], 0, j);
                    ++k;
                }
            }
        }
        if (A[1][N-1] == 0 && A[2][N-1] != 0) {
            swap(A[1][N-1], A[2][N-1]);
            add_move(A[1][N-1], 1, N-1);

            if (A[0][N-1] == A[1][N-1]) {
                A[1][N-1] = 0;
                add_move(A[0][N-1], 0, N-1);
                ++k;
            }
        }
        for (int j=N-1; j>0; --j) {
            if (A[2][j] == 0 && A[2][j-1] != 0) {
                swap(A[2][j], A[2][j-1]);
                add_move(A[2][j], 2, j);

                if (A[3][j] == A[2][j]) {
                    A[2][j] = 0;
                    add_move(A[3][j], 3, j);
                    ++k;
                }
            }
        }
        if (A[2][0] == 0 && A[1][0] != 0) {
            swap(A[2][0], A[1][0]);
            add_move(A[2][0], 2, 0);

            if (A[3][0] == A[2][0]) {
                A[2][0] = 0;
                add_move(A[3][0], 3, 0);
                ++k;
            }
        }
        //debug2(A, 4, N);

        assert(M <= 20000);
    }

    cout << M << '\n';
    for (int i=0; i<M; ++i) {
        cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
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
/*
3 6
1 2 3
1 3 4
5 6 2
4 5 6

3 6
1 2 3
3 2 4
5 6 1
4 5 6
*/
