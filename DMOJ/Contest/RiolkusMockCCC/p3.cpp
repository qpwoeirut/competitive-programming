//p3.cpp created at 02/15/21 12:02:35

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
typedef map<int,int> mii;
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

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 1001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN];
pll B[MN * MN];
//ll G[MN][MN];
set<ll> adj[MN];

int par[MN], sz[MN];
int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
void join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return;

    if (sz[ru] < sz[rv]) swap(ru, rv);
    sz[ru] += sz[rv];
    par[u] = par[v] = par[rv] = par[ru];
}

pll ans[MN * MN];

int prv[MN];
int df[MN << 1], ds[MN << 1];
void make_swap(const int a, const int b) {
    assert(a != b);
    fill(prv, prv+N, -1);
    queue<int> q;
    q.push(a);
    prv[a] = -2;

    debug1(A, N);
    debug(a, b);
    while (q.size() > 0) {
        const int u = q.front(); q.pop();
        debug(u);

        if (u == b) break;

        for (const int v: adj[u]) {
            if (prv[v] == -1) {
                prv[v] = u;
                if (v == b) {
                    while (q.size() > 0) q.pop();
                    break;
                }
                q.push(v);
            }
        }
    }
    debug1(prv, N);

    int lo = N-1, hi = N+1;
    df[N] = prv[b], ds[N] = b;
    int cur = prv[b];
    while (cur != a) {
        df[lo] = df[hi] = prv[cur], ds[lo] = ds[hi] = cur;
        --lo; ++hi;
        cur = prv[cur];
    }

    for (int i=lo+1; i<hi; ++i) {
        ans[K++] = pll(df[i], ds[i]);
    }
}

int val[MN], idxs[MN];
void solve_comp(const int rt) {
    int S = 0;
    for (int i=0; i<N; ++i) {
        if (root(i) == rt) {
            val[S] = A[i];
            idxs[S] = i;
            ++S;
        }
    }
    assert(S == sz[rt]);

    for (int i=0; i+1<S; ++i) {
        const int idx = min_element(val + i + 1, val + S) - val;
        if (val[i] < val[idx]) continue;

        make_swap(idxs[i], idxs[idx]);
        swap(A[idxs[i]], A[idxs[idx]]);
        swap(val[i], val[idx]);
    }
}

void solve(int testcase) {
    K = 0;
    cin >> N >> M;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<M; ++i) {
        cin >> B[i].FI >> B[i].SE;
        --B[i].FI; --B[i].SE;
        adj[B[i].FI].insert(B[i].SE);
        adj[B[i].SE].insert(B[i].FI);
    }

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }
    for (int i=0; i<M; ++i) {
        join(B[i].FI, B[i].SE);
    }

    for (int i=0; i<N; ++i) {
        if (root(i) == i) {
            solve_comp(i);
        }
    }

    cout << K << '\n';
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << '\n';
    for (int i=0; i<K; ++i) {
        cout << ans[i].FI+1 << ' ' << ans[i].SE+1 << '\n';
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
/*
5 4
5 4 3 2 1
1 2
1 3
1 4
1 5

4 6
3 4 2 1
1 2
1 3
1 4
2 3
2 4
3 4
*/
