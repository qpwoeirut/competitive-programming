//1696d.cpp created at 06/24/22 23:31:17
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

int pos[MN];
int mn[MN], mx[MN];

int BIT[MN];
void upd(int idx, int val) {
    for (; idx<=N; idx+=idx&-idx) chmn(BIT[idx], val);
}
int query(int idx) {
    int ret = N;
    for (; idx>0; idx-=idx&-idx) chmn(ret, BIT[idx]);
    return ret;
}

int solve() {
    for (int i=0; i<N; ++i) {
        pos[A[i]] = i;
    }
    pos[0] = pos[N+1] = N;

    fill(BIT, BIT+N+1, N);
    for (int i=N-1; i>=0; --i) {
        mn[i] = query(A[i]);
        upd(A[i], i);
    }
    fill(BIT, BIT+N+1, N);
    for (int i=N-1; i>=0; --i) {
        mx[i] = query(N - A[i] + 1);
        upd(N - A[i] + 1, i);
    }

    set<int> vals;
    for (int i=1; i<=N; ++i) vals.ins(i);
    ll ans = 0;
    ll cur = 0;
    int i = 0;
    while (cur < N-1) {
        for (; i<=cur; ++i) vals.erase(A[i]);
        //debug(cur, mn[cur], mx[cur], vals);
        if (mn[cur] == N) cur = pos[*vals.rbegin()];
        else if (mx[cur] == N) cur = pos[*vals.begin()];
        else {
            if (mn[cur] < mx[cur]) {
                int x = mx[cur];
                while (mn[cur] < x) {
                    cur = mn[cur];
                }
            } else {
                int x = mn[cur];
                while (mx[cur] < x) {
                    cur = mx[cur];
                }
            }
        }
        ++ans;
    }

    return ans;
}
int brute() {
    if (N == 1) {
        return 0;
    }

    fill(B, B+N, N);
    queue<int> q;
    q.push(0);
    B[0] = 0;
    while (q.size() > 0) {
        const int cur = q.front(); q.pop();
        vector<int> edge;
        ll _mn = A[cur], _mx = A[cur];
        for (int i=cur+1; i<N; ++i) {
            chmn(_mn, A[i]);
            chmx(_mx, A[i]);
            if ((_mn == A[cur] && _mx == A[i]) || (_mx == A[cur] && _mn == A[i])) {
                edge.pb(i);
            }
        }
        if (!edge.empty() && edge.back() == N-1) {
            return B[cur] + 1;
        }
        reverse(all(edge));
        for (const int e: edge) {
            if (chmn(B[e], B[cur] + 1)) q.push(e);
        }
    }
    assert(0);
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=20; ++N) {
        debug(N);
        for (int t=0; t<100000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = i + 1;
            }
            shuffle(A, A+N, rng);
            int sans = solve();
            int bans = brute();
            if (sans != bans) {
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    cout << A[i] << ' ';
                }
                cout << endl;
                cout << sans << ' ' << bans << endl;
                assert(sans == bans);
            }
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
        cout << solve() << '\n';
    }

    return 0;
}
/*
4
2 3 4 1
3 2
*/
