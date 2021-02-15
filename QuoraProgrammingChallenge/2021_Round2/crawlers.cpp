//crawlers.cpp created at 02/06/21 18:41:10

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
const int MN = 1001001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
set<ll> adj[MN], radj[MN];

bool used[MN];
vector<int> order;
int root[MN];
void dfs1(const int u) {
    used[u] = true;
    for (const int v: adj[u]) {
        if (!used[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(const int u, const int rt) {
    used[u] = true;
    root[u] = rt;
    for (const int v: radj[u]) {
        if (!used[v]) dfs2(v, rt);
    }
}

set<int> sources, sinks;
bool visited[MN];
int find_sink(const int node) {
    if (visited[node]) return -1;
    if (sinks.count(node)) {
        return node;
    }
    visited[node] = true;
    for (const int v: adj[node]) {
        const int ret = find_sink(v);
        if (ret != -1) return ret;
    }
    return -1;
}

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        radj[v].insert(u);
    }

    fill(used, used+N, false);
    for (int i=0; i<N; ++i) {
        if (!used[i]) dfs1(i);
    }
    fill(used, used+N, false);
    for (int i=0; i<N;  ++i) {
        const int u = order[N - i - 1];
        if (!used[u]) {
            dfs2(u, u);
        }
    }

    for (int i=0; i<N; ++i) {
        adj[i].clear();
    }

    for (int i=0; i<N; ++i) {
        for (const int v: radj[i]) {
            adj[root[v]].insert(root[i]);
        }
    }

    for (int i=0; i<N; ++i) {
        radj[i].clear();
    }
    for (int i=0; i<N; ++i) {
        for (const int v: adj[i]) {
            radj[v].insert(i);
        }
    }

    for (int i=0; i<N; ++i) {
        if (adj[root[i]].size() >= 1 && radj[root[i]].empty()) {
            sources.insert(root[i]);
        } else if (adj[root[i]].empty() && radj[root[i]].size() > 1) {
            sinks.insert(root[i]);
        }
    }
    debug1(root, N);
    debug1(adj, N);
    debug1(radj, N);
    debug(sources, sinks);

    vector<pll> ans;
    while (sources.size() > 0) {
        const int source = *sources.begin();
        sources.erase(sources.begin());
        const int sink = find_sink(source);
        if (sink != -1) {
            ans.emplace_back(sink + 1, source + 1);
        }
    }

    cout << ans.size() << '\n';
    for (const pll& p: ans) {
        cout << p.FI << ' ' << p.SE << '\n';
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
5 7
1 2
2 3
1 3
1 5
4 5
4 2
5 3
*/
