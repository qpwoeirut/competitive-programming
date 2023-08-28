//431d.cpp created at 10/21/20 11:57:13

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
const int MN = 1001001;

ll N, M, K;
//ll A[MN];
//ll G[MN][MN];
__int128 choose[65][65];
ll count(ll n) {
    int lg = 0;
    ll nn = n;
    while (nn) {
        ++lg;
        nn >>= 1;
    }
    debug(n, lg, K);

    __int128 ans = choose[lg][K];
    int ct = 0;
    for (int i=lg-1; i>=0; --i) {
        debug(i, (ll)ans, (n >> i) & 1);
        if ((n >> i) & 1) {
            ++ct;
            if (ct >= K) break;
        } else {
            ans -= choose[i][K - ct - 1];
        }
    }

    if ((ans >> 62) > 0) {
        return (1LL << 62);
    }
    debug((ll)ans);
    return (ll) ans;
}
ll check(ll n) {
    return count(n << 1) - count(n);
}

void solve(int testcase) {
    cin >> M >> K;

    ll lo = 1, hi = 1e18;
    ++hi;
    while (lo < hi) {
        ll mid = (lo + hi) >> 1;
        ll val = check(mid);
        debug(mid, val);
        if (val < M) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    cout << lo << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;

    for (__int128 i=0; i<=64; ++i) {
        for (__int128 j=0; j<=64; ++j) {
            if (j > i) choose[i][j] = 0;
            else if (j == i || j == 0) choose[i][j] = 1;
            else {
                choose[i][j] = (choose[i][j-1] * (i-j+1)) / j;
            }
            assert(choose[i][j] >= 0);
        }
    }
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
