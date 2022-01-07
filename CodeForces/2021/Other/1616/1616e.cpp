//1616e.cpp created at 12/29/21 09:06:40
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

set<int> pos[128];

void solve(int testcase) {
    fill(pos, pos+128, set<int>());
    cin >> N;
    cin >> S;
    cin >> T;
    debug(S, T);
    string sorted = S;
    sort(all(sorted));
    if (T <= sorted) {
        cout << "-1\n";
        return;
    }

    for (int i=0; i<N; ++i) {
        pos[S[i]].ins(i);
    }

    ll ans = INF;
    ll cur = 0;
    int j = 0;
    deque<int> gaps;
    for (int i=0; i<N; ++i) {
        while (gaps.size() > 0 && gaps[0] == j) {
            ++j;
            gaps.pop_front();
        }
        //debug(i, j, ans, cur, gaps);
        //debug(S[j], pos[S[j]], T[i], pos[T[i]]);
        for (char c=0; c<T[i]; ++c) {
            if (pos[c].empty()) continue;
            int gaps_between = LB(all(gaps), *pos[c].begin()) - gaps.begin();
            int swap_cost = *pos[c].begin() - j - gaps_between;
            //debug(c, *pos[c].begin(), swap_cost);
            assert(swap_cost >= 0);
            chmn(ans, cur + swap_cost);
        }
        if (S[j] > T[i]) {
            if (pos[T[i]].empty()) {
                cur += INF;
            } else {
                int idx = *pos[T[i]].begin();
                int swap_cost = idx - i;
                cur += swap_cost;

                gaps.pb(idx);
                pos[T[i]].erase(pos[T[i]].begin());
            }
        } else {
            assert(!pos[S[j]].empty());
            pos[S[j]].erase(pos[S[j]].begin());
            ++j;
        }
    }
    for (char c='a'; c<='z'; ++c) {
        //debug(c, pos[c]);
    }

    cout << ans << '\n';
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

/*
5
1
a
a
2
aa
aa
2
ab
ba
2
ba
ab
3
cab
bac

-1
-1
0
-1
1

========

5
5
bcbca
babca
4
baab
acaa
6
ddabcd
abcede
7
bcdefgb
bcbdefa
8
bcbfdgea
bbcdfage

4
1
6
5
4
*/
