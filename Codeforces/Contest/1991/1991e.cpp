//1991e.cpp created at 07/28/24 09:28:05
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
vector<ll> adj[MN];
string S, T;

//int par[MN];
//int cycle_start, cycle_end;
//bool dfs(int u) {
//    A[u] = 1;
//    for (int v: adj[u]) {
//        if (A[v] == 0) {
//            par[v] = u;
//            if (dfs(v)) return true;
//        } else if (A[v] == 1) {
//            cycle_start = u;
//            cycle_end = v;
//            return true;
//        }
//    }
//    A[u] = 2;
//    return false;
//}

bool dfs(int u, int val) {
    if (A[u] != -1) return A[u] == val;
    A[u] = val;
    bool ret = true;
    for (int v: adj[u]) ret &= dfs(v, val ^ 1);
    return ret;
}

int neighbor[MN];
void alice() {
    fill(B, B+N, 0);

    //vector<int> cycle;
    //int u = cycle_start;
    //while (u != cycle_end) {
    //    cycle.ins(u);
    //    u = par[u];
    //}
    cout << "Alice\n";
    cout.flush();
    for (int i=0; i<N; ++i) {
        //for (int j=0; j<cycle.size(); ++j) {
        //    int u = cycle[j], v = cycle[(j + 1) % cycle.size()];
        //    if (B[u] == 0 && B[v] == 0 && neighbor[u] != 0 && neighbor[v] != 0) {
        //        spam_a = 
        //    }
        //}
        cout << "1 2\n";
        cout.flush();

        int u, c;
        cin >> u >> c;
        //--u;
        //for (int v: adj[u]) neighbor[v] = c;
    }
}

void bob() {
    set<int> rem[2];
    for (int i=0; i<N; ++i) {
        rem[A[i]].ins(i);
    }
    cout << "Bob\n";
    cout.flush();
    for (int i=0; i<N; ++i) {
        int a, b;
        cin >> a >> b;
        
        if (a > b) swap(a, b);
        if (rem[a - 1].size() > 0) {
            cout << (*rem[a - 1].begin()) + 1 << ' ' << a << '\n';
            rem[a - 1].erase(rem[a - 1].begin());
        } else {
            cout << (*rem[a & 1].begin()) + 1 << ' ' << b << '\n';
            rem[a & 1].erase(rem[a & 1].begin());
        }
        cout.flush();
    }
}

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<N; ++i) adj[i].clear();
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v; --u; --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    //fill(A, A+N, 0);
    //cycle_start = cycle_end = -1;
    fill(A, A+N, -1);
    bool colorable = true;
    for (int i=0; i<N; ++i) {
        if (A[i] == -1) colorable &= dfs(i, 0);
    }
    if (!colorable) {
        alice();
    } else {
        bob();
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
