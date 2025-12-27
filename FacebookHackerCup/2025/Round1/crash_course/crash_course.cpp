//crash_course.cpp created at 10/18/25 12:00:34
#include <bits/stdc++.h>

using namespace std;

#ifdef DELETE_FOR_PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class T> using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
#endif

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
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

bitset<MN> dp[2][MN];
string solve_slow() {
    assert(N < MN);

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=N; ++j) {
            dp[0][i][j] = dp[1][i][j] = false;
        }
    }
    for (int len=1; len<=N; ++len) {
        for (int L=0; L+len<=N; ++L) {
            int R = L + len;
            for (int k=L; k<R; ++k) {
                if (S[k] == 'A') {
                    dp[0][L][R] = dp[0][L][R] || !dp[1][k+1][R];
                }
                if (S[k] == 'B') {
                    dp[1][L][R] = dp[1][L][R] || !dp[0][L][k];
                }
            }
        }
    }

    return dp[0][0][N] ? "Alice" : "Bob";
}

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/RMQ.h
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
            for (int j=0; j<sz(jmp[k]); ++j) {
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

string solve() {
    vector<pii> pref(N), suff(N);
    for (int i=0; i<N; ++i) {
        pref[i] = pii((i ? pref[i-1].fi : 0) + (S[i] == 'A' ? -1 : +1), i);
    }
    for (int i=N-1; i>=0; --i) {
        suff[i] = pii((i<N-1 ? suff[i+1].fi : 0) + (S[i] == 'B' ? -1 : +1),-i);
    }
    for (int i=0; i<N; ++i) {
        if (S[i] != 'A') pref[i].fi = -INIT;
        if (S[i] != 'B') suff[i].fi = -INIT;
    }

    RMQ<pii> pref_rmq(pref), suff_rmq(suff);

    string ans = "";

    bool turn = 0;
    int L = 0, R = N;
    while (L < R) {
        //debug(L, R, turn);
        if (turn == false) {
            if (S[R-1] == 'A') {
                ans = "Alice";
                break;
            }
            pii best = pref_rmq.query(L, R);
            //debug(best);
            if (best.fi == -INIT) {
                ans = "Bob";
                break;
            }
            L = best.se + 1;
        } else {
            if (S[L] == 'B') {
                ans = "Bob";
                break;
            }
            pii best = suff_rmq.query(L, R);
            //debug(best);
            if (best.fi == -INIT) {
                ans = "Alice";
                break;
            }
            R = -best.se;
        }

        turn = !turn;
    }
    if (ans == "") {
        ans = turn ? "Alice" : "Bob";
    }
    return ans;
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=50; ++N) {
        debug(N);
        for (int t=0; t<1000000; ++t) {
            S = "";
            for (int i=0; i<N; ++i) {
                S.push_back(rng() % 2 ? 'A' : 'B');
            }
            string ans_slow = solve_slow();
            string ans = solve();

            if (ans_slow != ans) {
                debug(N, S);
                debug(ans_slow, ans);
            }
            assert(ans_slow == ans);
        }
    }
}

int main() {
    //test(); return 0;
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N;
        cin >> S;

        if (N < MN) debug(test_case, N, solve_slow());
        const string ans = solve();
        cout << "Case #" << test_case << ": " << ans << '\n';
    }

    return 0;
}
/*
2
4 AAAB
2 AB
*/
