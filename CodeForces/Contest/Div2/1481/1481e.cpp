//1481e.cpp created at 02/04/21 23:26:29

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
//set<ll> adj[MN];

ll ct[MN];
pll pos[MN];
ll dp[MN];
vector<ll> endings[MN];

ll solve() {
    fill(ct, ct+N+1, 0);
    fill(pos, pos+N+1, pll(INIT, -1));
    fill(endings, endings+N+1, vector<ll>());
    fill(dp, dp+N+1, 0);
    for (ll i=1; i<=N; ++i) {
        ++ct[A[i]];
        chmn(pos[A[i]].FI, i);
        chmx(pos[A[i]].SE, i);
    }
    for (int i=1; i<=N; ++i) {
        if (pos[i].SE != -1) {
            endings[pos[i].SE].push_back(i);
        }
    }

    dp[0] = 0;
    for (int i=1; i<=N; ++i) {
        dp[i] = dp[i-1];

        for (const int e: endings[i]) {
            chmx(dp[i], dp[pos[e].FI - 1] + ct[e]);
        }
    }

    debug1(A, N+1);
    debug1(dp, N+1);
    return N - dp[N];
}
        
        
int main() {
    setIO();
    
    cin >> N;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
    }
    ll ans = solve();

    int free_moves = 0;
    for (int i=N; i>0; --i) {
        if (A[i] == A[N]) ++free_moves;
        else break;
    }
    const ll old_n = N;
    N = remove(A+1, A+N+1, A[N]) - A;
    --N;
    chmn(ans, solve() + old_n - N - free_moves);
    debug(free_moves, old_n, N);

    cout << ans << endl;
    
    return 0;
}
