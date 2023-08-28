//1864e.cpp created at 08/26/23 08:47:09
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
const ll MOD = 998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 1001001;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

struct TrieNode {
    const ll p2;
    const ll val;
    ll ct;

    TrieNode* child[2];

    TrieNode() : p2(0), val(0), ct(0) {
        child[0] = nullptr;
        child[1] = nullptr;
    }
    TrieNode(const ll _p2, const ll _val, const ll _ct) : p2(_p2), val(_val), ct(_ct) {
        child[0] = nullptr;
        child[1] = nullptr;
    }

    void add_value(const int x) {
        ++ct;

        if (p2 < 0) return;
        if (!child[0]) child[0] = new TrieNode(p2 - 1, 0, 0);
        if (!child[1]) child[1] = new TrieNode(p2 - 1, 1, 0);

        const int nxt = (x >> (p2 - 1)) & 1;
        child[nxt]->add_value(x & ((1 << p2) - 1));
    }

    ll count_ans(const int x) {
        if (x == 0 || p2 < 0) return ct;
        if (!child[0]) child[0] = new TrieNode(p2 - 1, 0, 0);
        if (!child[1]) child[1] = new TrieNode(p2 - 1, 1, 0);

        int ret = 0;
        if (val == 1) ret += ct;

        const int nxt = (x >> (p2 - 1)) & 1;
        ret += child[nxt]->count_ans(x & ((1 << p2) - 1));
        ret += child[nxt ^ 1]->ct * (nxt == 0 ? 2 : 1);
        debug(p2, x, child[0]->ct, child[1]->ct, ret);

        return ret;
    }
};

TrieNode* strie[31];

int ilog2(int x) {
    int lg = 0;
    while (x > 1) {
        x >>= 1;
        ++lg;
    }
    return lg;
}

ll solve() {
    for (int i=0; i<=30; ++i) {
        if (strie[i]) delete strie[i];
        strie[i] = new TrieNode(i, 1, 0);
    }

    for (int i=0; i<N; ++i) {
        strie[ilog2(A[i])]->add_value(A[i]);
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        const int lg = ilog2(A[i]);
        debug(i, A[i]);
        for (int p2=0; p2<=30; ++p2) {
            if (lg < p2) {
                ans += strie[p2]->ct;
            } else if (lg == p2) {
                ans += strie[p2]->count_ans(A[i]);
                //debug(A[i], p2, strie[p2]->count_ans(A[i]));
            } else if (lg > p2) {
                ans += strie[p2]->ct * 2;
            }
        }
    }

    ans %= MOD;
    debug(ans);
    ans = (ans * binpow((N * N) % MOD, MOD - 2, MOD)) % MOD;
    return ans;
}

ll brute() {
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            ++ans;
            for (int k=30; k>=0; --k) {
                const int a = (A[i] >> k) & 1;
                const int b = (A[j] >> k) & 1;
                if (a == 0 && b == 0) continue;
                else if (a == 1 && b == 0) {
                    ans += 2;
                    break;
                } else if (a == 0 && b == 1) {
                    ++ans;
                    break;
                } else {
                    ++ans;
                }
            }
        }
    }
    ans %= MOD;
    debug(ans);
    ans = (ans * binpow((N * N) % MOD, MOD - 2, MOD)) % MOD;
    return ans;
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=3; ++N) {
        for (int t=0; t<10000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = rng() % 20;
            }
            ll sans = solve();
            ll bans = brute();
            if (sans != bans) {
                cout << N << '\n';
                for (int i=0; i<N; ++i) cout << A[i] << ' ';
                cout << endl;

                cout << sans << ' ' << bans << endl;
            }
            assert(sans == bans);
        }
    }
}

int main() {
    setIO();

    //test();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        solve();
    }

    return 0;
}
