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
const int MN = 21;

ll N, M, K;
ll A[MN];
//int G[MN][MN];
set<int> adj[MN];
const int MXV = 1e7;
ll kn[MXV];
ll get_ways(ll target, const vector<ll>& nums) {
    for (int i=0; i<=target; i++) {
        kn[i] = 0;
    }
    kn[target] = 1;
    for (int j=0; j<sz(nums); j++) {
        for (int i=target; i>=nums[j]; i--) {
            if (kn[i] == 0) continue;
            kn[i - nums[j]] += kn[i];
        }
    }
    return max(1LL, kn[0]);
}

bool V[MN];
ll ans = 0;
void dfs(int node) {
    if (V[node]) return;
    V[node] = true;
    vector<ll> nums;
    for (set<int>::iterator it=adj[node].begin(); it!=adj[node].end(); it++) {
        nums.PB(A[*it]);
    }
    ans += get_ways(A[node], nums);
    ans %= MOD;
    for (set<int>::iterator it=adj[node].begin(); it!=adj[node].end(); it++) {
        dfs(*it);
    }
}

void solve(int t) {
    cin >> N >> M;

    for (int i=0; i<N; i++) {
        cin >> A[i];
        if (A[i] > MXV) {
            cout << 1 << endl;
            return;
        }
        V[i] = false;
    }

    for (int i=0; i<M; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;

        if (u < v) swap(u,v);
        adj[u].INS(v);
    }

    dfs(N-1);
    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
