//1000e.cpp created at 12/04/20 22:21:17

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
set<int> adj[MN], btree[MN];
vector<pii> bridge;

bool visited[MN];
int cur_time = 0;
int disc[MN], low[MN];
void dfs(int u, int par) {
    debug(u, par);
    disc[u] = low[u] = cur_time++;
    visited[u] = true;

    for (const int& v: adj[u]) {
        debug(v);
        if (v == par) continue;
        if (visited[v]) {
            chmn(low[u], disc[v]);
        } else {
            dfs(v, u);
            chmn(low[u], low[v]);
        }
    }
    debug(u, par);
    if (par != -1 && disc[par] < low[u]) {
        bridge.emplace_back(par, u);
    }
    debug(u, par);
}

int mark[MN];
int cur_mark = 0;
void component(int u) {
    debug(u);
    visited[u] = true;
    mark[u] = cur_mark;
    for (const int& v: adj[u]) {
        if (!visited[v]) component(v);
    }
}


int dist[MN];
void dfs2(int u, int par) {
    for (const int& v: btree[u]) {
        if (v == par) continue;
        dist[v] = dist[u] + 1;
        dfs2(v, u);
    }
}

void solve(int testcase) {
    cin >> N >> M;

    for (int i=0; i<M; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        adj[x].insert(y);
        adj[y].insert(x);
    }

    dfs(0, -1);
    debug(bridge);
    for (const pii& p: bridge) {
        debug(p);
        adj[p.FI].erase(p.SE);
        adj[p.SE].erase(p.FI);
    }
    debug1(adj, N);

    fill(visited, visited+N, false);
    for (int i=0; i<N; ++i) {
        if (!visited[i]) {
            component(i);
            ++cur_mark;
        }
    }
    debug1(mark, N);

    for (const pii& p: bridge) {
        btree[mark[p.FI]].insert(mark[p.SE]);
        btree[mark[p.SE]].insert(mark[p.FI]);
    }

    dfs2(0, -1);
    int far_node = 0, far_val = 0;
    for (int i=0; i<N; ++i) {
        if (chmx(far_val, dist[i])) {
            far_node = i;
        }
    }
    dist[far_node] = 0;
    dfs2(far_node, -1);
    int diameter = 0;
    for (int i=0; i<N; ++i) {
        chmx(diameter, dist[i]);
    }

    cout << diameter << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
