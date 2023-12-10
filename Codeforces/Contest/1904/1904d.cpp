//1904d.cpp created at 12/09/23 08:49:24
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
ll cur[MN];
ll B[MN];
set<int> pos_a[MN];
set<int> pos_b[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

int expand(int idx) {
    int val = cur[idx];
    for (int i=idx-1; i>=0; --i) {
        if (cur[i] != B[i] && cur[i] <= val) cur[i] = val;
        else break;
    }
    for (int i=idx+1; i<N; ++i) {
        if (cur[i] != B[i] && cur[i] <= val) cur[i] = val;
        else return i;
    }
    return N;
}

bool in_interval(const vector<pii>& intervals, int val) {
    int idx = (lower_bound(all(intervals), pii(val + 1, 0)) - intervals.begin()) - 1;
    return idx >= 0 && intervals[idx].first <= val && val < intervals[idx].second;
}

bool slow() {
    copy(A, A+N, cur);
    for (int x=1; x<=N; ++x) {
        for (int i=0; i<N;) {
            if (cur[i] == x) i = expand(i);
            else ++i;
        }
    }
 
    for (int i=0; i<N; ++i) {
        if (cur[i] != B[i]) {
            return false;
        }
    }
    return true;
}

bool solve() {
    for (int i=0; i<=N; ++i) {
        pos_a[i].clear();
        pos_b[i].clear();
    }
    set<int> blocks;
    for (int i=0; i<N; ++i) {
        pos_a[A[i]].ins(i);
        pos_b[B[i]].ins(i);
        blocks.ins(i);
    }

    for (int x=1; x<=N; ++x) {
        vector<pii> intervals;
        for (int p: pos_a[x]) blocks.erase(p);
        //debug(x, blocks);

        for (int p: pos_a[x]) {
            auto it = blocks.upper_bound(p);
            int lo = 0, hi = N;
            if (it != blocks.begin()) {
                auto lo_it = it;
                --lo_it;
                lo = *lo_it + 1;
            }
            if (it != blocks.end()) {
                hi = *it;
            }
            intervals.emplace_back(lo, hi);
        }
        sort(all(intervals));  // just in case
        //debug(intervals);

        for (int p: pos_b[x]) blocks.ins(p);
        for (int p: pos_b[x]) {
            if (!in_interval(intervals, p)) {
                //debug(x, p);
                return false;
            }
        }
    }

    //for (int i=0; i<N; ++i) {
    //    if (A[i] != B[i]) {
    //        cout << "NO\n";
    //        return;
    //    }
    //}
    return true;
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=100; ++N) {
        debug(N);
        for (int t=0; t<100000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = (rng() % N) + 1;
                B[i] = (rng() % N) + 1;
                if (rng() % 3 == 0) A[i] = B[i];
            }

            bool slow_ans = slow();
            bool fast_ans = solve();
            if (slow_ans != fast_ans) {
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    if (i) cout << ' ';
                    cout << A[i];
                }
                cout << endl;
                for (int i=0; i<N; ++i) {
                    if (i) cout << ' ';
                    cout << B[i];
                }
                cout << endl;
            }
            assert(slow_ans == fast_ans);
        }
    }
}

int main() {
    setIO();

    //test(); return 0;

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }

        for (int i=0; i<N; ++i) {
            cin >> B[i];
        }
        cout << (solve() ? "YES" : "NO") << '\n';
    }

    return 0;
}
