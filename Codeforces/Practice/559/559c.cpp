//559c.cpp created at 09/21/20 12:55:31

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

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
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
const int MN = 2001;
const int MV = 200001;

ll N, H, W;
pll A[MN];
ll dp[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll fact[MV], inv[MV];
ll choose(ll n, ll k) {
    return (((fact[n] * inv[k]) % MOD) * inv[n-k]) % MOD;
}

void solve(int testcase) {
    cin >> H >> W >> N;
    --H; --W;

    for (int i=0; i<N; ++i) {
        cin >> A[i].FI >> A[i].SE;
        --A[i].FI; --A[i].SE;
    }
    sort(A, A+N);
    A[N] = pll(H, W);
    ++N;

    for (int i=0; i<N; ++i) {
        dp[i] = choose(A[i].FI + A[i].SE, A[i].FI);
        for (int j=0; j<i; ++j) {
            if (A[i].FI >= A[j].FI && A[i].SE >= A[j].SE) {
                ll rd = A[i].FI - A[j].FI;
                ll cd = A[i].SE - A[j].SE;
                dp[i] -= (dp[j] * choose(rd + cd, rd)) % MOD;
            }
        }
        dp[i] = ((dp[i] % MOD) + MOD) % MOD;
    }

    cout << dp[N-1] << endl;
}
        
int main() {
    setIO();
    
    ll T = 1;

    fact[0] = 1;
    inv[0] = 1;
    for (ll i=1; i<MV; ++i) {
        fact[i] = (i * fact[i-1]) % MOD;
        inv[i] = binpow(fact[i], MOD-2, MOD);
    }
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
