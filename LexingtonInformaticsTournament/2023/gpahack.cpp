//gpahack.cpp created at 08/05/23 17:41:36
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

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

ll SA[MN], SB[MN];

dbl solve() {
    sort(A, A+N);
    sort(B, B+M, greater<ll>());

    SA[0] = SB[0] = 0;
    for (int i=0; i<N; ++i) {
        SA[i+1] = SA[i] + A[i];
    }
    for (int i=0; i<M; ++i) {
        SB[i+1] = SB[i] + B[i];
    }

    dbl ans = (((dbl)SA[N] / N) + ((dbl)SB[M] / M)) / 2;

    for (ll lo=0; lo<=K; ++lo) {
        ll hi = K - lo;
        int a_move = min(N, lo);
        int b_move = min(M, hi);
        if (N + b_move == a_move || M + a_move == b_move) {
            if (a_move > 0) --a_move;
            else if (b_move > 0) --b_move;
            else continue;
        }
        dbl sa = SA[N] - SA[a_move] + SB[b_move];
        dbl sb = SB[M] + SA[a_move] - SB[b_move];
        dbl avg_a = sa / (N - a_move + b_move);
        dbl avg_b = sb / (M + a_move - b_move);
        chmx(ans, (avg_a + avg_b) / 2);
    }

    sort(A, A+N, greater<ll>());
    sort(B, B+M);

    SA[0] = SB[0] = 0;
    for (int i=0; i<N; ++i) {
        SA[i+1] = SA[i] + A[i];
    }
    for (int i=0; i<M; ++i) {
        SB[i+1] = SB[i] + B[i];
    }
    for (ll lo=0; lo<=K; ++lo) {
        ll hi = K - lo;
        int a_move = min(N, lo);
        int b_move = min(M, hi);
        if (N + b_move == a_move || M + a_move == b_move) {
            if (a_move > 0) --a_move;
            else if (b_move > 0) --b_move;
            else continue;
        }
        dbl sa = SA[N] - SA[a_move] + SB[b_move];
        dbl sb = SB[M] + SA[a_move] - SB[b_move];
        dbl avg_a = sa / (N - a_move + b_move);
        dbl avg_b = sb / (M + a_move - b_move);
        chmx(ans, (avg_a + avg_b) / 2);
    }

    return ans;
}

bitset<5> mva, mvb;
dbl recurse(int k, ll sa, ll sb) {
    dbl ret = 0;
    dbl new_n = N - mva.count() + mvb.count();
    dbl new_m = M + mva.count() - mvb.count();
    if (new_n > 0 && new_m > 0) {
        ret = ((sa / new_n) + (sb / new_m)) / 2;
    }
    if (k == K) {
        return ret;
    }

    for (int i=0; i<N; ++i) {
        if (!mva[i]) {
            mva[i] = true;
            chmx(ret, recurse(k+1, sa - A[i], sb + A[i]));
            mva[i] = false;
        }
    }
    for (int i=0; i<M; ++i) {
        if (!mvb[i]) {
            mvb[i] = true;
            chmx(ret, recurse(k+1, sa + B[i], sb - B[i]));
            mvb[i] = false;
        }
    }
    return ret;
}

dbl brute() {
    assert(N <= 5 && M <= 5);
    ll sa = 0, sb = 0;
    for (int i=0; i<N; ++i) {
        sa += A[i];
    }
    for (int i=0; i<M; ++i) {
        sb += B[i];
    }
    mva.reset();
    mvb.reset();

    return recurse(0, sa, sb);
}

mt19937 rng(8);
void test() {
    for (N=1; N<=5; ++N) {
        for (M=1; M<=5; ++M) {
            debug(N, M);
            for (K=0; K<=N+M; ++K) {
                for (int t=0; t<100; ++t) {
                    for (int i=0; i<N; ++i) {
                        A[i] = (rng() % 10) + 1;
                    }
                    for (int i=0; i<M; ++i) {
                        B[i] = (rng() % 10) + 1;
                    }

                    dbl sans = solve();
                    dbl bans = brute();

                    if (abs(sans - bans) > 1e-8) {
                        debug(N, M, K);
                        debug1(A, N);
                        debug1(B, M);
                        debug(sans, bans);
                        assert(0);
                    }
                }
            }
        }
    }
}

int main() {
    setIO();
    //test(); return 0;

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    cout << fixed << setprecision(6);
    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N >> M >> K;

        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        for (int i=0; i<M; ++i) {
            cin >> B[i];
        }

        cout << solve() << '\n';
    }

    return 0;
}
