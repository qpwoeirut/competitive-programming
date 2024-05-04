//strgery.cpp created at 04/27/24 18:16:08
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
string S, P;

int z_pre[MN];
int z_suf[MN];
// https://cp-algorithms.com/string/z-function.html
void calc_z(const string& s, int z[]) {
    int n = s.size();
    int l = 0, r = 0;
    fill(z, z+n, 0);
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
}

void solve() {
    if (P.size() == 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    calc_z(P + '#' + S, z_pre);
    
    string P_rev = P; reverse(all(P_rev));
    string S_rev = S; reverse(all(S_rev));
    calc_z(P_rev + '#' + S_rev, z_suf);

    const int start = P.size() + 1;
    const int finish = start + S.size();

    vector<pii> prefs, suffs;
    for (int i=start; i<finish; ++i) {
        if (z_pre[i] >= P.size()) {
            //string result = S.substr(i - start, 1) + S.substr(i - start + 1, P.size() - 1);
            cout << i - start << ' ' << 1 << ' ' << i - start + 1 << ' ' << P.size() - 1 << '\n';
            return;
        }
        if (z_pre[i] > 0) {
            prefs.eb(z_pre[i], i - start);
        }
        if (z_suf[i] > 0) {
            const int i_rev = i - start;
            suffs.eb(z_suf[i], S.size() - i_rev - 1);
        }
    }

    sort(all(prefs));
    sort(all(suffs), greater<pii>());
    //debug(S.size(), P.size());
    //debug(prefs);
    //debug(suffs);

    int s_i = 0;
    int a = S.size(), b = -1;
    for (const pii& pref: prefs) {
        while (s_i < suffs.size() && suffs[s_i].fi + pref.fi >= P.size()) {
            chmn(a, suffs[s_i].se + 1);
            chmx(b, suffs[s_i].se + 1);
            ++s_i;
        }
        int len2 = (int)P.size() - pref.fi;
        //debug(pref, len2, a, b);
        if (a <= pref.se) {
            //debug(a);
            cout << pref.se << ' ' << pref.fi << ' ' << a - len2 << ' ' << len2 << '\n';
            string result = S.substr(pref.se, pref.fi) + S.substr(a - len2, len2);
            assert(result == P);
            assert(a <= pref.se);
            assert(pref.fi > 0 && len2 > 0);
            return;
        }
        if (pref.fi + pref.se <= b - len2) {
            //debug(b);
            cout << pref.se << ' ' << pref.fi << ' ' << b - len2 << ' ' << len2 << '\n';
            string result = S.substr(pref.se, pref.fi) + S.substr(b - len2, len2);
            assert(result == P);
            assert(pref.se + pref.fi <= b - len2);
            assert(pref.fi > 0 && len2 > 0);
            return;
        }
    }

    cout << "IMPOSSIBLE\n";
}

void test() {
    mt19937 rng(8);

    for (int n=1; n<=8; ++n) {
        for (int m=1; m<=8; ++m) {
            debug(n, m);
            for (int t=0; t<10000000; ++t) {
                S = P = "";
                for (int i=0; i<n; ++i) {
                    S += 'a' + (rng() % 5);
                }
                for (int i=0; i<m; ++i) {
                    P += 'a' + (rng() % 5);
                }

                //cout << S << ' ' << P << endl;
                solve();
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
        cin >> S;
        cin >> P;
        solve();
    }

    return 0;
}
/*
8
aa
aa

a
aa

b
a

bb
aa

abc
cba

abc
acb

abc
bca

abc
cab
*/
