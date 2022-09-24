//consecutive_cuts.cpp created at 09/10/22 23:05:45
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

void setIO(const string& filename = "consecutive_cuts") {
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

const int MOD_CT = 6;
const ll MODS[MOD_CT] = {(ll)1e9 + 7, (ll)1e9 + 9, (ll)1e9 + 21, (ll)1e9 + 33, (ll)1e9 + (ll)1e5 + 7, (ll)1e9 + (ll)1e5 + 33};

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

const ll BASE = 500009;
ll BASES[MN][MOD_CT];

struct Hash {
    ll len;
    ll vals[MOD_CT];
    
    Hash() {
        len = 0;
        fill(vals, vals+MOD_CT, 0);
    }
    void operator=(const Hash& o) {
        len = o.len;
        copy(o.vals, o.vals + MOD_CT, vals);
    }
    const bool operator==(const Hash& o) const {
        return len == o.len && equal(vals, vals+MOD_CT, o.vals);
    }
    void push_front(const int x) {
        for (int m=0; m<MOD_CT; ++m) {
            vals[m] = (vals[m] + x * BASES[len][m]) % MODS[m];
        }
        ++len;
    }
    void push_back(const int x) {
        for (int m=0; m<MOD_CT; ++m) {
            vals[m] = (vals[m] * BASE + x) % MODS[m];
        }
        ++len;
    }
};

Hash hashes[MN][2][2];

void solve(int testcase) {
    cin >> N >> K;
    vector<int> values;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        values.pb(A[i]);
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
        values.pb(B[i]);
    }

    sort(all(values));
    values.resize(unique(all(values)) - values.begin());
    for (int i=0; i<N; ++i) {
        A[i] = LB(all(values), A[i]) - values.begin();
        B[i] = LB(all(values), B[i]) - values.begin();
    }

    hashes[0][0][0] = Hash();
    hashes[0][1][0] = Hash();
    hashes[N][0][1] = Hash();
    hashes[N][1][1] = Hash();
    for (int i=1; i<=N; ++i) {
        hashes[i][0][0] = hashes[i-1][0][0];
        hashes[i][0][0].push_back(A[i-1]);
        hashes[i][1][0] = hashes[i-1][1][0];
        hashes[i][1][0].push_back(B[i-1]);
    }
    for (int i=N-1; i>=0; --i) {
        hashes[i][0][1] = hashes[i+1][0][1];
        hashes[i][0][1].push_front(A[i]);
        hashes[i][1][1] = hashes[i+1][1][1];
        hashes[i][1][1].push_front(B[i]);
    }

    set<int> matches;
    for (int i=1; i<N; ++i) {
        if (hashes[i][0][0] == hashes[N-i][1][1] && hashes[i][0][1] == hashes[N-i][1][0]) {
            matches.ins(i);
        }
    }
    //for (int i=0; i<=N; ++i) debug(hashes[i][0][0].vals[0]);
    //for (int i=0; i<=N; ++i) debug(hashes[N-i][0][1].vals[0]);
    //for (int i=0; i<=N; ++i) debug(hashes[i][1][0].vals[0]);
    //for (int i=0; i<=N; ++i) debug(hashes[N-i][1][1].vals[0]);


    bool ok = false;
    if (K != 1 && hashes[N][0][0] == hashes[N][1][0]) ok = true;
    else if (K > 0 && matches.size() > 0) ok = true;
    
    if (N == 2 && K > 0) {
        if (A[0] == A[1] && A[0] == B[0] && B[0] == B[1]) ok = true;
        else if (A[0] == B[0] && A[1] == B[1] && K % 2 == 1) ok = false;
        else if (A[0] == B[1] && A[1] == B[0] && K % 2 == 0) ok = false;
    }

    cout << "Case #" << testcase << ": " << (ok ? "YES" : "NO") << '\n';
}

int main() {
    setIO();

    for (int i=0; i<MN; ++i) {
        for (int j=0; j<MOD_CT; ++j) {
            BASES[i][j] = i ? (BASES[i-1][j] * BASE) % MODS[j] : 1;
        }
    }

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}
