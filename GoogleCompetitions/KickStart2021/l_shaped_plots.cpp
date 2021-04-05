//l_shaped_plots.cpp created at 03/20/21 21:03:23

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

#define pb push_back
#define ins insert

#define fi first
#define se second
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

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int INIT = 1001001001;
const int MN = 1001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN];// , B[MN];
ll G[MN][MN];
ll len[MN][MN][4];
//set<ll> adj[MN];

void solve(int testcase) {
    cin >> N >> M;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
        }
    }

    for (int i=0; i<N; ++i) {
        int x = 0;
        for (int j=0; j<M; ++j) {
            ++x;
            if (G[i][j] == 0) x = 0;
            len[i][j][0] = x;
        }
    }
    for (int j=0; j<M; ++j) {
        int x = 0;
        for (int i=0; i<N; ++i) {
            ++x;
            if (G[i][j] == 0) x = 0;
            len[i][j][1] = x;
        }
    }
    for (int i=0; i<N; ++i) {
        int x = 0;
        for (int j=M-1; j>=0; --j) {
            ++x;
            if (G[i][j] == 0) x = 0;
            len[i][j][2] = x;
        }
    }
    for (int j=0; j<M; ++j) {
        int x = 0;
        for (int i=N-1; i>=0; --i) {
            ++x;
            if (G[i][j] == 0) x = 0;
            len[i][j][3] = x;
        }
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            for (int a=0; a<4; ++a) {
                for (int b=a+1; b<4; ++b) {
                    if ((a & 1) == (b & 1)) continue;
                    if (len[i][j][a] < 2 || len[i][j][b] < 2) continue;
                    ans += max(0LL, min(len[i][j][a] / 2, len[i][j][b]) - 1);
                    ans += max(0LL, min(len[i][j][a], len[i][j][b] / 2) - 1);
                }
            }
        }
    }
    debug1(len[3][0], 4);

    cout << "Case #" << testcase << ": " << ans << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
