//interesting_integers.cpp created at 03/19/22 22:10:24
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

bool is_interesting(ll x) {
    ll prod = 1, sum = 0;
    while (x > 0) {
        prod *= x % 10;
        sum += x % 10;
        x /= 10;
    }
    return (prod % sum) == 0;
}

int ct[10];
int ct_cpy[10];
ll fact[15];
int digits[12];

ll count_perms(ll mx, int k) {
    copy(ct, ct+10, ct_cpy);
    ll tmp = mx;
    for (int i=0; i<k; ++i) {
        digits[k-i-1] = tmp % 10;
        tmp /= 10;
    }
    ll denom = 1;
    if (tmp > 0) {
        for (int d=0; d<10; ++d) {
            denom *= fact[ct[d]];
        }
        ll p = fact[k] / denom;
        if (ct[0] > 0) {
            denom = 1;
            
            for (int d=0; d<10; ++d) {
                denom *= fact[ct[d] - (d == 0)];
            }
            p -= fact[k-1] / denom;
        }
        return p;
    }

    if (digits[0] == 0) {
        return 0;
    }

    ll perms = 0;
    for (int i=0; i<k; ++i) {
        for (int d=i==0; d<digits[i]; ++d) {
            if (ct[d] == 0) continue;
            --ct[d];
            denom = 1;
            for (int d0=0; d0<10; ++d0) {
                denom *= fact[ct[d0]];
            }
            perms += fact[k-i-1] / denom;
            ++ct[d];
        }
        if (ct[digits[i]] == 0) break;
        --ct[digits[i]];
        if (i+1 == k) ++perms;
    }
    copy(ct_cpy, ct_cpy+10, ct);
    //if (perms > 0) { debug(perms, mx, k); debug1(ct, 10); }
    return perms;
}

ll brute(int digits, int last, ll prod, ll sum) {
    if (digits == 12) {
        ll ret = 0;
        for (int lead_z=0; lead_z<ct[0]; ++lead_z) {
            ct[0] -= lead_z;
            ret += count_perms(M, 12 - lead_z) - count_perms(N-1, 12 - lead_z);
            ct[0] += lead_z;
        }
        if (sum > 0 && (prod % sum) == 0) {
            int tmp = ct[0];
            ct[0] = 0;
            ret += count_perms(M, 12 - tmp) - count_perms(N-1, 12 - tmp);
            ct[0] = tmp;
        }
        return ret;
    }
    ll ret = 0;
    for (int i=last; i<10; ++i) {
        ++ct[i];
        ret += brute(digits + 1, i, i == 0 ? prod : prod * i, sum + i);
        --ct[i];
    }
    return ret;
}

void solve(int testcase) {
    cin >> N >> M;
    ll ans = brute(0, 0, 1, 0);
    if (M == binpow(10, 12, INF)) ++ans;

    cout << "Case #" << testcase << ": " << ans << '\n';
}

int main() {
    setIO();

    fact[0] = 1;
    for (ll i=1; i<15; ++i) {
        fact[i] = fact[i-1] * i;
    }

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}

/*
20
1032 1000000000000
132432 1000000000000
1345 1000000000000
134643 1000000000000
1234 1000000000000
1345 1000000000000
12353 1000000000000
134643 1000000000000
11232 1000000000000
2351 1000000000000
135 1000000000000
43641 1000000000000
5461 1000000000000
15544 1000000000000
4571 1000000000000
451 1000000000000
3451 1000000000000
3461 1000000000000
45451 1000000000000
135 1000000000000
*/
