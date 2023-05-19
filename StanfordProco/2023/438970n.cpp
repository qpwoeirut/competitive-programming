//438970n.cpp created at 04/15/23 11:51:54
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
const int MN = 41001;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;


struct Seg{
    int n, h;
    int t[2 * MN];
    int d[MN];
    Seg () {
        n = MN - 1;
        h = sizeof(int) * 8 - __builtin_clz(n);
        fill(t, t+2*n, 0);
        fill(d, d+n, 0);
    }
    
    void apply (int p, int v){
        t[p] += v;
        if (p < n)
        {
            d[p] += v;
        }
    }
    
    void build(int p){
        while (p > 1)
        {
            p /= 2;
            t[p] = max(t[p * 2], t[p * 2 + 1]) + d[p];
        }
    }
    
    void push(int p){
        for (int s = h; s > 0; s--)
        {
            int i = p >> s;
            if (d[i] != 0){
                apply(i * 2, d[i]);
                apply(i * 2 + 1, d[i]);
                d[i] = 0;
            }
        }
    }
    void inc (int l, int r, int v){
        l += n, r += n;
        int lp = l, rp = r;
        for (; l < r; l /= 2, r /= 2)
        {
            if (l % 2) apply(l++, v);
            if (r % 2) apply(--r, v);
        }
        build(lp);
        build(rp-1);
    }
    
    int query (int l, int r){
        l += n, r += n;
        push(l);
        push(r-1);
        int res = 0;
        for (; l < r; l /= 2, r /= 2)
        {
            if (l % 2) res = max(res, t[l++]);
            if (r % 2) res = max(res, t[--r]);
        }
        return res;
    }
};

Seg st[105];
int solve() {
    if (N == 1) return 1;
    for (int x=0; x<=K; ++x) {
        st[x] = Seg();
    }
    fill(B, B+N+1, 0);
    for (int i=1; i<=N; ++i) {
        for (int x=1; x<=K; ++x) {
            st[x-1].inc(B[A[i-1]], i, 1);
            int val = st[x-1].query(0, i);
            //debug(B[A[i-1]], i, x, val);
            st[x].inc(i, i+1, val);

            //for (int a=0; a<=N; ++a) { for (int b=0; b<=K; ++b) { cerr << st[b].query(a, a+1) << ' '; } cerr << endl; }

        }
    B[A[i-1]] = i;
    }
    return st[K].query(N, N+1);
}

ll dp[MN][105];
int brute() {
    for (int i=0; i<=N; ++i) {
        for (int x=0; x<=K; ++x) {
            dp[i][x] = 0;
        }
    }

    for (int i=1; i<=N; ++i) {
        for (int x=1; x<=K; ++x) {
            set<int> nums;
            for (int j=i-1; j>=0; --j) {
                nums.ins(A[j]);
                chmx(dp[i][x], (ll)(nums.size()) + dp[j][x-1]);
            }
        }
    }
    return dp[N][K];
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=10; ++N) {
        debug(N);
        for (int t=0; t<=N*N*N*N*100; ++t) {
            K = (rng() % N) + 1;
            for (int i=0; i<N; ++i) {
                A[i] = (rng() % N) + 1;
            }
            int bans = brute();
            int sans = solve();
            if (bans != sans) {
                cout << N << ' ' << K << endl;
                for (int i=0; i<N; ++i) {
                    cout << A[i] << ' ';
                }
                cout << endl;
                cout << bans << ' ' << sans << endl;
                assert(bans == sans);
            }
        }
    }
}

int main() {
    setIO();

    //test(); return 0;

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    cout << solve() << '\n';

    return 0;
}
/*

*/
