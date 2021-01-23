//1473d.cpp created at 01/14/21 07:25:24

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
const int MN = 201001;
const ll INF = 2e18 + 1;
const int LG = 20;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
ll depth[MN];
ll pref_mn[MN], pref_mx[MN];
ll suff_mn[MN], suff_mx[MN];

void solve(int testcase) {
    cin >> N >> Q;
    string S;
    cin >> S;

    depth[0] = 0;
    pref_mn[0] = 0;
    pref_mx[0] = 0;
    for (int i=1; i<=N; ++i) {
        A[i] = S[i-1] == '-' ? -1 : 1;
        depth[i] = depth[i-1] + A[i];
        pref_mn[i] = min(pref_mn[i-1], depth[i]);
        pref_mx[i] = max(pref_mx[i-1], depth[i]);
    }
    depth[N+1] = depth[N];
    debug1(depth, N+2);
    debug1(pref_mn, N+2);
    debug1(pref_mx, N+2);

    suff_mn[N+1] = suff_mx[N+1] = depth[N];
    for (int i=N; i>0; --i) {
        suff_mn[i] = min(suff_mn[i+1], depth[i]);
        suff_mx[i] = max(suff_mx[i+1], depth[i]);
    }

    for (int i=0; i<Q; ++i) {
        ll L, R;
        cin >> L >> R;
        --L;

        ll lo = pref_mn[L];
        ll hi = pref_mx[L];
        if (R < N) {
            chmn(lo, suff_mn[R+1] - depth[R] + depth[L]);
            chmx(hi, suff_mx[R+1] - depth[R] + depth[L]);

            debug(depth[L], depth[R], suff_mn[R+1], suff_mx[R+1]);
        }
        debug(L, R, lo, hi);
        cout << hi - lo + 1 << '\n';
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
