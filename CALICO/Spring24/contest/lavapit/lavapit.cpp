//lavapit.cpp created at 04/27/24 16:24:37
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
const int MN = 1001;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
string G[MN];
//set<ll> adj[MN];
string S, T;

int dp_tr[MN][MN];
int dp_bl[MN][MN];

int best_r[MN];

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> G[i];
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            dp_tr[i][j] = dp_bl[i][j] = -INIT;
        }
    }

    dp_tr[0][0] = G[0][0] == 'D';
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (G[i][j] == 'L' || (i == 0 && j == 0)) continue;
            dp_tr[i][j] = max(i ? dp_tr[i-1][j] : -INIT, j ? dp_tr[i][j-1] : -INIT) + (G[i][j] == 'D');
        }
    }

    dp_bl[N-1][M-1] = G[N-1][M-1] == 'L' ? -INIT : (G[N-1][M-1] == 'D');
    for (int i=N-1; i>=0; --i) {
        for (int j=M-1; j>=0; --j) {
            if (G[i][j] == 'L' || (i == N-1 && j == M-1)) continue;
            dp_bl[i][j] = max(i+1 < N ? dp_bl[i+1][j] : -INIT, j+1 < M ? dp_bl[i][j+1] : -INIT) + (G[i][j] == 'D');
        }
    }
    //debug2(dp_tr, N, M);
    //debug2(dp_bl, N, M);

    int ans = -INIT;
    fill(best_r, best_r + M, -INIT);
    for (int i=0; i<N; ++i) {
        int best_col = -INIT;
        for (int j=0; j<M; ++j) {
            chmx(best_r[j], max(i ? dp_tr[i-1][j] : -INIT, j ? dp_tr[i][j-1] : -INIT));
            chmx(best_col, max(i ? dp_tr[i-1][j] : -INIT, j ? dp_tr[i][j-1] : -INIT));

            if (G[i][j] == 'D') ++best_r[j];
            if (G[i][j] == 'D') ++best_col;

            chmx(best_r[j], dp_tr[i][j]);
            chmx(best_col, dp_tr[i][j]);
            
            chmx(ans, best_r[j] + max(i+1 < N ? dp_bl[i+1][j] : -INIT, j+1 < M ? dp_bl[i][j+1] : -INIT));
            chmx(ans, best_col + max(i+1 < N ? dp_bl[i+1][j] : -INIT, j+1 < M ? dp_bl[i][j+1] : -INIT));

            chmx(ans, best_r[j] + dp_bl[i][j] - (G[i][j] == 'D'));
            chmx(ans, best_col + dp_bl[i][j] - (G[i][j] == 'D'));

            if (i == N - 1 && j == M - 1) {
                chmx(ans, best_r[j]);
                chmx(ans, best_col);
            }

            //debug(i, j, best_r[j], best_col, dp_bl[i][j]);
        }
    }
    if (ans < 0) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << '\n';
    }
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
7
1 1
D

1 1
O

1 2
DL

2 2
DL
LL

3 3
DLL
LLL
LLO

3 3
DLD
LLL
LLO

3 3
DLD
LLO
LLO

1
4 3
DLL
DLL
LLL
LLL
*/