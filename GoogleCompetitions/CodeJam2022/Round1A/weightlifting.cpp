//weightlifting.cpp created at 04/08/22 18:47:04
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
const int MN = 101;

ll N, M, K, Q;
ll A[MN][MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

vector<int> cur[MN];  // cur[weight] = list of insertion positions

int add_ct[MN][MN];  // add_ct[ins_pos][del_pos] = # to add
int del_ct[MN];  // del_ct[del_pos] = # of weights

int solve() {
    fill(cur, cur+M, vector<int>());
    fill(del_ct, del_ct+N+1, 0);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<=N; ++j) {
            add_ct[i][j] = 0;
        }
    }
    for (int j=0; j<M; ++j) {
        A[N][j] = 0;
    }
    
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<M; ++j) {
            while (cur[j].size() < A[i][j]) {
                cur[j].pb(i);
            }
            while (cur[j].size() > A[i][j]) {
                int ins_pos = cur[j].back(); cur[j].pop_back();
                ++add_ct[ins_pos][i];
            }
        }
    }

    int ans = 0;
    for (int i=0; i<=N; ++i) {
        ans += del_ct[i];
        del_ct[i] = 0;  // remove weights

        int max_del_pos = 0;
        for (int j=0; j<=N; ++j) {
            if (add_ct[i][j] > 0) max_del_pos = j;
        }

        for (int j=0; j<max_del_pos; ++j) {
            ans += 2 * del_ct[j];  // remove and replace
        }
        for (int j=0; j<=max_del_pos; ++j) {
            ans += add_ct[i][j];  // place
            del_ct[j] += add_ct[i][j];
        }
    }
    return ans;
}

const int MASKS = 1 << 18;
vector<int> unmask(int mask) {
    vector<int> result;
    for (int i=0; i<9; ++i) {
        if (mask & 3) result.pb(mask & 3);
        mask >>= 2;
    }
    reverse(all(result));
    return result;
}
int to_mask(const vector<int>& v) {
    int mask = 0;
    for (const int x: v) {
        mask <<= 2;
        mask |= x;
    }
    assert(mask < MASKS);
    return mask;
}
vector<int> create_perm(const int i) {
    vector<int> perm;
    for (int j=0; j<M; ++j) {
        for (int k=0; k<A[i][j]; ++k) {
            perm.pb(j+1);
        }
    }
    return perm;
}
int cost(const vector<int>& v1, const vector<int>& v2) {
    int same = 0;
    for (same=0; same<v1.size() && same<v2.size() && v1[same] == v2[same]; ++same);
    assert(same <= v2.size());
    return v1.size() + v2.size() - same * 2;
}
int dp[12][MASKS];

mt19937 rng(8);

int brute() {
    for (int j=0; j<M; ++j) {
        A[N][j] = 0;
    }
    for (int i=0; i<=N+1; ++i) {
        for (int j=0; j<MASKS; ++j) {
            dp[i][j] = INIT;
        }
    }
    dp[0][0] = 0;

    for (int i=1; i<=N+1; ++i) {
        vector<int> cur = create_perm(i-1);
        vector<int> last = i == 1 ? vector<int>() : create_perm(i - 2);
        do {
            do {
                chmn(dp[i][to_mask(cur)], dp[i-1][to_mask(last)] + cost(last, cur));
            } while (next_permutation(all(cur)));
        } while (next_permutation(all(last)));
    }

    int ans = INIT;
    for (int j=0; j<MASKS; ++j) {
        chmn(ans, dp[N+1][j]);
    }
    return ans;
}

void test() {
    for (N=1; N<=5; ++N) {
        for (M=1; M<=3; ++M) {
            debug(N, M);
            for (int t=0; t<1000; ++t) {
                for (int i=0; i<N; ++i) {
                    for (int j=0; j<M; ++j) {
                        A[i][j] = rng() % 4;
                    }
                }

                const int sans = solve();
                const int bans = brute();
                if (sans != bans) {
                    debug(sans, bans);
                    cout << N << ' ' << M << endl;
                    for (int i=0; i<N; ++i) {
                        for (int j=0; j<M; ++j) {
                            if (j) cout << ' ';
                            cout << A[i][j];
                        }
                        cout << endl;
                    }
                    //assert(sans == bans);
                }
            }
        }
    }
}

int main() {
    setIO();

    test(); return 0;

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N >> M;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                cin >> A[i][j];
            }
        }
        const int ans = brute();
        cout << "Case #" << test_case << ": " << ans << '\n';
    }

    return 0;
}
/*
3 2
0 2
3 2
1 0
*/
