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
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353;
const int INIT = 1001001001;
const int MN = 1000001;

ll N, M, K;
//int A[MN];
//int G[MN][MN];
vector<pii> adj[MN], radj[MN];
ll tup[20];
ll ans = 0;
ll start;
bool V[MN];
void dfs(ll node, ll vct) {
    //debug(node);
    //debug(radj[node]);
    //debug1(tup, K+1);
    for (ll i=0; i<radj[node].size(); i++) {
        ll u = radj[node][i].FI;
        if (tup[adj[u].size()] == radj[node][i].SE) {
            if (u == start && vct == N) {
                ll add = 1;
                for (ll j=1; j<=K; j++) {
                    if (tup[j] == -1) add *= j;
                }
                ans += add;
                continue;
            }
            if (V[u]) continue;
            V[u] = true;
            dfs(u, vct+1);
            V[u] = false;
        } else if (tup[adj[u].size()] == -1) {
            if (u == start && vct == N) {
                ll add = 1;
                for (ll j=1; j<=K; j++) {
                    if (tup[j] == -1) add *= j;
                }
                ans += add;
                continue;
            }
            if (V[u]) continue;
            V[u] = true;
            tup[adj[u].size()] = radj[node][i].SE;
            dfs(u, vct+1);
            tup[adj[u].size()] = -1;
            V[u] = false;
        }
    }
}

void solve(int t) {
    cin >> N >> M >> K;

    for (int i=0; i<M; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].PB(pii(v, w));
    }
    for (int i=0; i<N; i++) {
        sort(all(adj[i]), cmps<int,int>());
        assert(adj[i].size() <= 9);
        for (int j=0; j<adj[i].size(); j++) {
            assert(j == 0 || adj[i][j-1].SE < adj[i][j].SE);
            radj[adj[i][j].FI].PB(pii(i, j));
        }
    }
        

    start = 0;
    ll mx = 0;
    for (int i=0; i<N; i++) {
        ll sum = 0;
        for (int j=0; j<radj[i].size(); j++) {
            sum += adj[radj[i][j].FI].size();
        }

        if (sum > mx) {
            mx = sum;
            start = i;
        }
    }
    fill(tup, tup+20, -1);
    ans = 0;
    fill(V, V+N, false);
    V[start] = true;
    //debug(start);
    assert(start >= 0 && start < N);
    dfs(start, 1);

    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
