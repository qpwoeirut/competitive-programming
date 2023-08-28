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
//set<int> adj[MN];
ll choose[MN];

ll modinv(ll a) {
    ll m = MOD;
    ll y = 0, x = 1;
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

void solve(int t) {
    cin >> N;

    choose[0] = 1;
    for (int i=1; i<N; i++) {
        choose[i] = (((choose[i-1] * (N - i)) % MOD) * modinv(i)) % MOD;
    }
    assert(choose[N-1] == 1);

    ll ans = 0;
    for (int i=0; i<N; i++) {
        ans = (ans + choose[i]) % MOD;
    }

    ll total = 1;
    for (int i=2; i<=N; i++) {
        total = (total * i) % MOD;
    }

    ll x = (total - ans + MOD) % MOD;

    cout << x << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
