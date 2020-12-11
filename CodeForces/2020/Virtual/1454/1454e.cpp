//1454e.cpp created at 12/08/20 11:07:43

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
const int MN = 1001001;

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
set<ll> adj[MN];

pll e1, e2;
bool V[MN];
ll par[MN];
void dfs(int u) {
    V[u] = true;
    for (auto& v: adj[u]) {
        if (par[u] == v) continue;
        if (V[v]) {
            assert(par[u] != -1);
            e1 = pll(u, v);
            e2 = pll(par[u], u);
            break;
        }
        if (par[v] == -1) par[v] = u;
        dfs(v);
        if (e1.FI != -1) break;
    }
}

ll get_size(int u, int p) {
    ll ret = 1;
    for (auto& v: adj[u]) {
        if (v == p) continue;
        if ((u == e2.FI && v == e2.SE) || (u == e2.SE && v == e2.FI)) continue;
        ret += get_size(v, u);
    }
    return ret;
}

ll subsize[MN];
void dfs2(int u, int p) {
    subsize[u] = 1;
    par[u] = p;
    for (auto& v: adj[u]) {
        if (v == p) continue;
        dfs2(v, u);
        subsize[u] += subsize[v];
    }
}

void solve(int testcase) {
    cin >> N;
    fill(adj, adj+N, set<ll>());
    for (int i=0; i<N; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    ll ans = (N * (N - 1)) >> 1;
    debug(ans);
    e1 = pll(-1, -1);

    fill(V, V+N, false);
    fill(par, par+N, -1);
    dfs(0);

    adj[e1.FI].erase(e1.SE);
    adj[e1.SE].erase(e1.FI);

    debug(e1, e2);
    ll size = get_size(0, -1);
    debug(size);
    ans += size * (N - size);

    adj[e2.FI].erase(e2.SE);
    adj[e2.SE].erase(e2.FI);

    fill(subsize, subsize+N, 0);
    dfs2(e2.FI, -1);

    int cur = e1.SE;
    while (cur != -1) {
        debug(cur, subsize[cur]);
        ans += subsize[cur] * (subsize[e2.FI] - subsize[cur]);
        cur = par[cur];
    }

    cout << ans << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
