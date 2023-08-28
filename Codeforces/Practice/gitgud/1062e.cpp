//1062e.cpp created at 11/27/20 14:58:06
// smol brane memory moment
// additional smol brane array bounds moment

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

#define PB push_back
#define INS insert

#define FI first
#define SE second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef unsigned long long ull;
typedef long double dbl;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef pair<dbl,dbl> pdd;
typedef map<ll,ll> mll;
typedef map<char,int> mci;
typedef map<string,int> msi;
typedef map<string,string> mss;

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

template <class T1,class T2> struct cmpf {
	bool rev;
	inline bool operator()(const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.first<b.first)^rev;}
	cmpf(bool b=false) {rev=b;}
};
template <class T1,class T2> struct cmps {
	bool rev;
	inline bool operator()(const pair<T1,T2>& a, const pair<T1,T2>& b) const {return (a.second<b.second)^rev;}
	cmps(bool b=false) {rev=b;}
};

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return ((a>b) ? ((a=b) || true) : false);}
template <class T> bool chmx(T& a, const T& b) {return ((a<b) ? ((a=b) || true) : false);}

void setIO(const string& filename = "") {
	cin.tie(0)->sync_with_stdio(0);
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 101001;
const int LG = 18;

ll N, M, K, Q;
ll A[MN];
//ll G[MN][MN];
set<ll> adj[MN];

ll anc[LG][MN];
int lvl[MN];
pll mark[MN];

ll cur_mark;
void dfs(int node) {
    mark[node].FI = cur_mark++;
    for (int x: adj[node]) {
        lvl[x] = lvl[node] + 1;
        dfs(x);
    }
    mark[node].SE = cur_mark - 1;
}

bool is_anc(int a, int b) {
    return mark[a].FI <= mark[b].FI && mark[b].SE <= mark[a].SE;
}

int lca(int u, int v) {
    if (is_anc(u, v)) return u;
    if (is_anc(v, u)) return v;

    for (int i=LG-1; i>=0; --i) {
        if (anc[i][u] == -1) continue;
        if (!is_anc(anc[i][u], v)) {
            u = anc[i][u];
        }
    }
    return anc[0][u];
}

int sparse[LG][MN];
int lg2[MN];

int lca_range(int a, int b) {
    int lg = lg2[b - a];
    return lca(sparse[lg][a], sparse[lg][b - (1 << lg)]);
}

int L, R;
int get_ans(int del) {
    if (L == del) {
        return lca_range(del+1, R);
    } else if (del+1 == R) {
        return lca_range(L, del);
    } else {
        return lca(lca_range(L, del), lca_range(del + 1, R));
    }
}

void solve(int testcase) {
    cin >> N >> Q;
    for (int i=0; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            anc[i][j] = -1;
        }
    }
    for (int i=1; i<N; ++i) {
        cin >> anc[0][i];
        --anc[0][i];
        adj[anc[0][i]].insert(i);
    }

    cur_mark = 0;
    dfs(0);
    debug1(mark, N);
    debug1(lvl, N);

    for (int i=1; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            if (anc[i-1][j] == -1) continue;
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }

    for (int i=0; i<N; ++i) {
        sparse[0][i] = i;
    }
    for (int i=1; i<LG; ++i) {
        for (int j=0; j+(1 << i) <= N; ++j) {
            sparse[i][j] = lca(sparse[i-1][j], sparse[i-1][j + (1 << (i-1))]);
        }
    }

    for (int i=2; i<=N; ++i) {
        lg2[i] = lg2[i >> 1] + 1;
    }

    for (int i=0; i<Q; ++i) {
        cin >> L >> R;
        --L;

        int overall = lca_range(L, R);
        debug(i, L, R, overall, lvl[overall]);

        int lo = L, hi = R-1;
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (lvl[overall] < lvl[lca_range(L, mid)]) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        int ans1 = lo;
        int lca1 = get_ans(ans1);

        lo = L, hi = R-1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (lvl[overall] < lvl[lca_range(mid+1, R)]) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        int ans2 = lo;
        int lca2 = get_ans(ans2);

        int ans = ans1;
        if (lvl[lca2] > lvl[lca1]) {
            ans = ans2;
        }

        debug(ans1, ans2);
        debug(lca1, lvl[lca1], lca2, lvl[lca2]);

        cout << ans + 1 << ' ' << lvl[get_ans(ans)] << '\n';
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
