//1470b.cpp created at 01/05/21 07:35:32

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
//set<ll> adj[MN];

ll pf[MN];
ll odd_pows(ll x) {
    ll ret = 1;
    while (x > 1) {
        int ct = 0;
        ll p = pf[x];
        while (x % p == 0) {
            x /= p;
            ++ct;
        }

        if (ct & 1) ret *= p;
    }
    return ret;
}

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    mll ct;
    ll ans0 = 0;
    for (int i=0; i<N; ++i) {
        A[i] = odd_pows(A[i]);
        chmx(ans0, ++ct[A[i]]);
    }
    ll ans1 = ans0;
    ll evens = 0;
    for (const pll& p: ct) {
        if ((p.SE & 1) == 0 || p.FI == 1) evens += p.SE;
    }
    chmx(ans1, evens);

    cin >> K;
    for (int i=0; i<K; ++i) {
        ll W;
        cin >> W;
        if (W == 0) {
            cout << ans0 << '\n';
        } else {
            cout << ans1 << '\n';
        }
    }
}
        
        
int main() {
    setIO();

    for (int i=2; i<MN; ++i) {
        if (i & 1) {
            pf[i] = i;
        } else {
            pf[i] = 2;
        }
    }
    for (ll i=3; i<MN; i+=2) {
        if (pf[i] < i) continue;
        for (ll j=i*i; j<MN; j+=i) {
            pf[j] = i;
        }
    }
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
1
3
3 3 4
3
0 1 2
*/
