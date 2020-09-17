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
#define sz(obj) ((ll)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef unsigned long long ull;
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef pair<double,double> pdd;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
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

ll binpow(const ll& x, const ll& p, const ll& mod) {assert(mod>0);
	if (p == 0) return 1;
	if (p == 1) return x % mod;
	if (p & 1) return (binpow((x*x) % mod, p/2, mod) * x) % mod;
	return binpow((x*x) % mod, p/2, mod) % mod;
}

template <class T> void chmn(T& a, const T& b) {if (a>b) a=b;}
template <class T> void chmx(T& a, const T& b) {if (a<b) a=b;}

void setIO(const string& filename = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    if (filename.size() > 0) {
        freopen((filename + ".txt").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353;
const int INIT = 1001001001;
const int MN = 1000001;

ll N, M, K;
//int A[MN];
//int G[MN][MN];
set<ll> adj[MN];
ll E[MN];
ll lvl[MN];
ll ct[MN];
ll tsize[MN], safe[MN];
ll par[MN][64];
string S;
vector<vector<ll> > groups;

inline const bool cmp_sz(const vector<ll>& a, const vector<ll>& b) {
    return sz(a) > sz(b);
}

ll dfs(ll node, ll mark) {
    ct[node] = E[node] >= 0 ? ct[E[node]] : 0;
    lvl[node] = E[node] >= 0 ? lvl[E[node]] + 1 : 0;
    if (E[node] >= 0 && (S[E[node]] == '#' || S[node] == '#')) {
        ++ct[node];
    }
    if (S[node] == '*') {
        groups[mark].PB(node);
    }
    tsize[node] = 1;
    safe[node] = S[node] == '*';
    for (set<ll>::iterator it=adj[node].begin(); it!=adj[node].end(); it++) {
        if (S[node] == '#' || S[*it] == '#') {
            groups.PB(vector<ll>());
            tsize[node] += dfs(*it, sz(groups) - 1);
            safe[node] += safe[*it];
        } else {
            tsize[node] += dfs(*it, mark);
            safe[node] += safe[*it];
        }
    }

    return tsize[node];
}

ll lca(int u, int v) {
    if (lvl[u] < lvl[v]) {
        swap(u, v);
    }
    ll lg;
    for (lg=1; (1LL<<lg)<=lvl[u]; lg++);

    for (int i=lg; i>=0; --i) {
        if (lvl[u] - (1 << i) >= lvl[v]) {
            u = par[u][i];
        }
    }
    if (u == v) {
        return u;
    }

    for (int i=lg; i>=0; --i) {
        if (par[u][i] != -1 && par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    assert(u > 0);
    return E[u];
}


void solve(int t) {
    cin >> N >> K;
    cin >> S;
    assert(sz(S) == N);

    E[0] = -1;
    for (int i=1; i<=K; i++) {
        cin >> E[i];
    }
    ll a, b, c;
    cin >> a >> b >> c;
    for (ll i=K+1; i<N; i++) {
        E[i] = ((a * E[i-2] + b * E[i-1] + c) % (i - 1)) + 1;
    }

    for (int i=0; i<N; i++) {
        adj[i].clear();
    }
    for (int i=1; i<N; i++) {
        --E[i];
        adj[E[i]].INS(i);
    }

    for (int i=0; i<N; i++) {
        for (int j=0; (1LL<<j)<N; j++) {
            par[i][j] = -1;
        }
    }
    for (int i=0; i<N; i++) {
        par[i][0] = E[i];
    }
    for (int j=1; (1LL<<j)<N; j++) {
        for (int i=0; i<N; i++) {
            if (par[i][j-1] != -1) {
                par[i][j] = par[par[i][j-1]][j-1];
            }
        }
    }

    groups.clear();
    groups.PB(vector<ll>());
    dfs(0, 0);
    sort(groups.begin(), groups.end(), cmp_sz);
    while (sz(groups) > 0 && groups.back().empty()) {
        groups.pop_back();
    }
    if (sz(groups) == 0) {
        ll ways = 0;
        for (int i=1; i<N; i++) {
            ways += tsize[i] * (N - tsize[i]);
        }
        cout << "Case #" << t << ": " << 0 << ' ' << ways << endl; 
        return;
    }
    if (sz(groups) == 1) {
        ll ways = 0;
        for (int i=1; i<sz(groups[0]); i++) {
            ways += safe[groups[0][i]] * (sz(groups[0]) - safe[groups[0][i]]);
        }
        for (int i=1; i<N; i++) {
            if (S[i] == '*' && S[E[i]] == '*') continue;
            ways += tsize[i] * (N - tsize[i]);
        }
        cout << "Case #" << t << ": " << sz(groups[0]) * (sz(groups[0]) - 1) / 2 << ' ' << ways << endl; 
        return;
    }
        
    ll pairs = (sz(groups[0]) + sz(groups[1])) * (sz(groups[0]) + sz(groups[1]) - 1) / 2;
    for (int i=2; i<sz(groups); i++) {
        pairs += sz(groups[i]) * (sz(groups[i]) - 1) / 2;
    }

    ll ways = 0;
    for (int i=0; i<sz(groups); i++) {
        if (sz(groups[i]) != sz(groups[0])) continue;
        for (int j=i+1; j<sz(groups); j++) {
            if (sz(groups[j]) != sz(groups[1])) continue;
            ll edges = ct[groups[i][0]] + ct[groups[j][0]];
            edges -= ct[lca(groups[i][0], groups[j][0])] * 2;
            ways += edges * sz(groups[i]) * sz(groups[j]);
        }
    }

    cout << "Case #" << t << ": " << pairs << ' ' << ways << endl;
}
        
        
int main() {
    setIO("quarantine_validation");
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
