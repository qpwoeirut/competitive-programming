//209b.cpp created at 01/07/21 11:25:28

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
const ll INF = 2e18;

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll calc(ll a, ll b, ll c) {
    ll ret = 0;
    while (b > 0 || c > 0) {
        debug(a, b, c, ret);
        if (b > 0 && c > 0) {
            ll x = min(b, c);
            assert(x > 0);
            a += x;
            b -= x;
            c -= x;
            ret += x;
        } else {
            if (b < c) swap(b, c);
            assert(b > 0);
            assert(c == 0);
            if (a == 0 && c == 0) return ret;
            assert(a > 0);

            if (b == 1) {
                return ret + a;
            }

            ll x = b - (b & 1);
            assert(x > 0);
            b -= x;
            ret += x;
        }
    }
    return ret;
}

void solve(int testcase) {
    cin >> A[0] >> A[1] >> A[2];
    
    ll ans = INF;
    for (int i=0; i<3; ++i) {
        chmn(ans, calc(A[i], A[(i+1)%3], A[(i+2)%3]));
    }
    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}

/*
5 2 0
*/
