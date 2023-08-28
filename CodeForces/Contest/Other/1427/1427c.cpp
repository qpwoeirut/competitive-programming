//1427c.cpp created at 10/10/20 01:17:53

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

struct Event {
    int x, y, t;

    inline const bool ok(const Event& other) const {
        return t - other.t >= abs(x - other.x) + abs(y - other.y);
    }
};

int N, M, K;
Event A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
int dp[MN], mxdp[MN];

void solve(int testcase) {
    cin >> K >> N;
    for (int i=1; i<=N; ++i) {
        cin >> A[i].t >> A[i].x >> A[i].y;
    }
    A[0].t = 0;
    A[0].x = 1;
    A[0].y = 1;
    dp[0] = 1;
    mxdp[0] = 1;
    for (int i=1; i<=N; ++i) {
        int stop = max(0, i - (K+K));
        if (i >= (K+K)) {
            dp[i] = mxdp[stop] + 1;
        }
        for (int j=i-1; j>=stop; --j) {
            if (dp[j] == 0) continue;
            if (dp[i] > dp[j]) continue;
            if (A[i].ok(A[j])) {
                chmx(dp[i], dp[j]+1);
                if (mxdp[i-1] < dp[i]) break;
            }
        }
        chmx(mxdp[i], max(mxdp[i-1], dp[i]));
    }

    debug1(dp, N+1);
    
    cout << mxdp[N] - 1 << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
