//gemstones.cpp created at 11/14/20 11:19:40

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
const int MN = 305;

ll N, M, K;
//ll A[MN];
ll G[MN][MN];
//set<ll> adj[MN];

ll dp[MN][MN][MN]; 
ll row[MN][MN][3], col[MN][MN][3], diag[MN][MN][3];

ll mxx(ll a, ll b, ll c) {
    return max(a, max(b, c));
}
ll calc(int R, int C, int D) {
    if (R+C+D > N+1) return 0;
    if (dp[R][C][D] != -1) return dp[R][C][D];
    debug(R, C, D);
    ll rv = 0, cv = 0, dv = 0;
    for (int i=0; i<3; ++i) {
        chmx(rv, row[R][N-D-R+2][i] - row[R][C-1][i]);
        chmx(cv, col[N-D-C+2][C][i] - col[R-1][C][i]);
        chmx(dv, diag[N-D-C+2][C][i] - diag[R-1][N-D-R+2 + 1][i]);
    }
    debug(rv, cv, dv);

    dp[R][C][D] = mxx(
        calc(R+1, C, D) + rv,
        calc(R, C+1, D) + cv,
        calc(R, C, D+1) + dv
    );

    return dp[R][C][D];
}


void solve(int testcase) {
    cin >> N;
    if (N >= MN - 1) {
        cout << N -1 << endl;
    }
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=i; ++j) {
            cin >> G[i][j];
        }
    }
    for (int i=1; i<=N/2; ++i) {
        swap(G[i], G[N-i+1]);
    }
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=N; ++j) {
            for (int k=0; k<=N; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            for (int k=0; k<3; ++k) {
                row[i][j][k] = row[i][j-1][k] + (G[i][j] == k+1);
                col[i][j][k] = col[i-1][j][k] + (G[i][j] == k+1);
                diag[i][j][k] = diag[i-1][j+1][k] + (G[i][j] == k+1);
            }
        }
    }
    
    cout << calc(1, 1, 1) << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
5
2
2 3
2 3 1
1 2 2 1
3 1 3 2 3
*/
