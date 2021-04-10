//883a.cpp created at 04/09/21 14:38:41

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
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

ll X, D;
ll solve() {
    ll cur = 1; // time when door last shut
    ll ans = 0;
    ll erate = 1 + (D / X);
    for (int i=0; i<M; ++i) {
        const ll efi = ((cur - 1) / X) + 1; // first employee id with arrival time >= cur
        const ll elt = min(N, A[i] / X); // last employee id with arrival time <= A[i]

        if (efi <= elt) {
            const ll ect = elt - efi + 1; // # of employees that arrived between [cur, A[i]]
            ans += (ect + erate - 1) / erate;

            const ll last_open = (efi + (((ect - 1) / erate) * erate)) * X;
            cur = last_open + D + 1;
        }

        if (cur <= A[i]) {
            cur = A[i] + D + 1;
            ++ans;
        }
    }
    const ll efi = ((cur - 1) / X) + 1; // first employee id with arrival time >= cur

    if (efi <= N) {
        const ll ect = N - efi + 1; // # of employees that arrived between [cur, A[i]]
        ans += (ect + erate - 1) / erate;
    }
    return ans;
}

ll brute() {
    vector<ll> times(A, A+M);
    for (int i=1; i<=N; ++i) {
        times.push_back(i * X);
    }
    sort(all(times), greater<ll>());

    ll cur = 0;
    ll ans = 0;
    while (sz(times) > 0) {
        if (cur <= times.back()) {
            cur = times.back() + D + 1;
            ++ans;
        }
        times.pop_back();
    }
    return ans;
}

void test() {
    for (N=1; N<=20; ++N) {
        for (M=1; M<=5; ++M) {
            cerr << N << ' ' << M << endl;
            for (X=1; X<=20; ++X) {
                for (D=1; D<=20; ++D) {
                    for (int t=0; t<=1000; ++t) {
                        for (int i=0; i<M; ++i) {
                            A[i] = (rand() % 20) + 1;
                        }
                        sort(A, A+M);

                        ll ans = solve();
                        ll bans = brute();

                        if (ans != bans) {
                            cout << N << ' ' << M << ' ' << X << ' ' << D << '\n';
                            for (int i=0; i<M; ++i) {
                                if (i) cout << ' ';
                                cout << A[i];
                            }
                            cout << endl;
                            cout << ans << ' ' << bans << endl;
                        }
                        assert(ans == bans);
                    }
                }
            }
        }
    }
}
        

int main() {
    //test(); return 0;
    setIO();
    
    ll TEST_COUNT = 1;
    
    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N >> M >> X >> D;

        for (int i=0; i<M; ++i) {
            cin >> A[i];
        }

        cout << solve() << '\n';
    }
    
    return 0;
}
/*
100 1 10 1
101

1 1 10 1
101

5 2 20 20
21 41

6 2 20 20
21 41

2 1 1 1
3

3 1 1 1
4
*/
