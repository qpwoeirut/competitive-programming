//treasure.cpp created at 02/06/21 17:15:04

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
const int MN = 1005;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll G[MN][MN];
//set<ll> adj[MN];

pll dp[MN][MN];
void solve(int testcase) {
    cin >> N;
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == '1';
        }
    }

    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            if (i == 1 && j == 1) {
                dp[i][j] = pll(G[i][j], 1);
                continue;
            }
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            if (dp[i-1][j].FI == dp[i][j-1].FI) {
                dp[i][j].SE = dp[i-1][j].SE + dp[i][j-1].SE;
                if (dp[i][j].SE >= MOD) dp[i][j].SE -= MOD;
            }

            if (G[i][j]) {
                ++dp[i][j].FI;
            }
        }
    }

    cout << dp[N][N].FI << ' ' << dp[N][N].SE << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
