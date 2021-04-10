//hacked_exam.cpp created at 04/09/21 19:35:07

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
const int MN = 45;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
string A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string T;
const string S = "FT";

struct Fraction {
    ll a, b;
    Fraction(const ll _a, const ll _b) {
        a = _a;
        b = _b;

        simplify();
    }
    Fraction operator+=(const Fraction& o) {
        const ll l = lcm(b, o.b);
        a *= l / b;
        b *= l / b;

        a += o.a * (l / o.b);

        simplify();

        return *this;
    }

    void simplify() {
        const ll g = gcd(a, b);
        a /= g;
        b /= g;
    }
};

string to_string(const Fraction& f) {
    return to_string(f.a) + "/" + to_string(f.b);
}

bool check(const string& s) {
    for (int i=0; i<N; ++i) {
        int sc = 0;
        for (int j=0; j<sz(s); ++j) {
            if (A[i][j] == s[j]) ++sc;
        }
        if (sc != B[i]) return false;
    }
    return true;
}

ll dp[MN][MN][MN][MN];
void solve(int testcase) {
    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i] >> B[i];
    }

    T = "";
    if (N == 1) {
        if (B[0] <= Q/2) {
            for (const char c: A[0]) {
                if (c == 'F') T.pb('T');
                else T.pb('F');
            }
            B[0] = Q - B[0];
        } else {
            T = A[0];
        }
        cout << "Case #" << testcase << ": " << T << ' ' << to_string(Fraction(B[0], 1)) << '\n';
        return;
    }

    for (int lo=0; lo<Q; ++lo) {
        for (int i=0; i<=Q; ++i) {
            for (int j=0; j<=Q; ++j) {
                dp[lo][lo][i][j] = 1;
            }
        }
    }

    for (int len=1; len<=Q; ++len) {
        for (int lo=0; lo+len<=Q; ++lo) {
            const int hi = lo + len;

            for (int i=0; i<=Q; ++i) {
                for (int j=0; j<=Q; ++j) {
                    dp[lo][hi][i][j] = 0;
                    if (A[0][lo] == A[1][lo]) {
                        if (i > 0 && j > 0) dp[lo][hi][i][j] += dp[lo+1][hi][i-1][j-1];
                        dp[lo][hi][i][j] += dp[lo+1][hi][i][j];
                    } else {
                        if (i > 0) dp[lo][hi][i][j] += dp[lo+1][hi][i-1][j];
                        if (j > 0) dp[lo][hi][i][j] += dp[lo+1][hi][i][j-1];
                    }

                    if (A[0][hi-1] == A[1][hi-1]) {
                        if (i > 0 && j > 0) dp[lo][hi][i][j] += dp[lo][hi-1][i-1][j-1];
                        dp[lo][hi][i][j] += dp[lo][hi-1][i][j];
                    } else {
                        if (i > 0) dp[lo][hi][i][j] += dp[lo][hi-1][i-1][j];
                        if (j > 0) dp[lo][hi][i][j] += dp[lo][hi-1][i][j-1];
                    }
                }
            }
        }
    }

    const ll total = dp[0][Q][B[0]][B[1]];
    debug(total);

    Fraction ans(0, 1);
    T = "";

    for (int i=0; i<Q; ++i) {
        ll ct[2] = {0, 0};

        for (int s=0; s<2; ++s) {
            for (int s1=0; s1+(A[0][i] == S[s])<=B[0]; ++s1) {
                for (int s2=0; s2+(A[1][i] == S[s])<=B[1]; ++s2) {
                    int rs1 = B[0] - s1 - (A[0][i] == S[s]);
                    int rs2 = B[1] - s2 - (A[1][i] == S[s]);
                    ct[s] += dp[0][i][s1][s2] * dp[i+1][Q][rs1][rs2];
                }
            }
        }

        if (ct[0] >= ct[1]) {
            ans += Fraction(ct[0], total);
            T.pb('F');
        } else {
            ans += Fraction(ct[1], total);
            T.pb('T');
        }
    }

    cout << "Case #" << testcase << ": " << T << ' ' << to_string(ans) << '\n';
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
