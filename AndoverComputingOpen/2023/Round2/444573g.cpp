//444573g.cpp created at 05/20/23 14:11:30
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

struct Node {
    const ll inf = INF;
	Node *l = 0, *r = 0;
	ll lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(int _, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(_, lo, mid); r = new Node(_, mid, hi);
			val = min(l->val, r->val);
		}
		else val = INF;
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return -INF;
		if (L <= lo && hi <= R) return val;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

struct Location {
    int pos;
    int cost;
    int level;
    Location() {
        pos = cost = level = 0;
    }
    Location(int _pos, int _cost, int _level) {
        pos = _pos;
        cost = _cost;
        level = _level;
    }
    const bool operator<(const Location& o) const {
        return pos < o.pos;
    }
};

ll N, M, K, Q;
Location A[MN];
Location B[MN];
int a_idx[MN], b_idx[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

bool cmp_lvl(const Location& a, const Location& b) {
    return a.level < b.level || (a.level == b.level && a.pos < b.pos);
}
bool cmp_pos_a(const int a, const int b) {
    return A[a].pos < A[b].pos;
}
bool cmp_pos_b(const int a, const int b) {
    return B[a].pos < B[b].pos;
}

ll dp[MN];

void solve(int testcase) {
    cin >> K >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i].pos >> A[i].level >> A[i].cost;
    }
    for (int i=1; i<=M; ++i) {
        cin >> B[i].pos >> B[i].level >> B[i].cost;
    }

    B[0] = Location(0, 0, 0);
    B[M+1] = Location(K + 1, 0, INIT);
    M += 2;

    sort(A, A+N, cmp_lvl);
    sort(B, B+M, cmp_lvl);

    for (int i=0; i<N; ++i) a_idx[i] = i;
    for (int i=0; i<M; ++i) b_idx[i] = i;

    sort(a_idx, a_idx + N, cmp_pos_a);
    sort(b_idx, b_idx + M, cmp_pos_b);

    Node* st = new Node(0, 0, M);
    int m_i = 0;

    dp[0] = 0;
    st->set(0, 1, 0);
    for (int i=1; i<M; ++i) {
        debug(i, b_idx[i], B[b_idx[i]].pos, B[b_idx[i]].level);
        while (m_i < N && A[a_idx[m_i]].pos <= B[b_idx[i]].pos) {
            int lb = lower_bound(B, B+M, Location(-1, -1, A[a_idx[m_i]].level), cmp_lvl) - B;
            st->add(0, lb, A[a_idx[m_i]].cost);
            ++m_i;
        }
        dp[b_idx[i]] = B[b_idx[i]].cost + st->query(0, M);
        st->set(b_idx[i], b_idx[i]+1, dp[b_idx[i]]);
    }
    
    cout << dp[b_idx[M-1]] << '\n';
}

int main() {
    setIO();

    ll TEST_COUNT = 1;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}
