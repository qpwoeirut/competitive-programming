//1472f.cpp created at 01/04/21 08:04:51

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
pll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

bool dp[MN][4];
int G[MN][2];

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        cin >> A[i].SE >> A[i].FI;
        --A[i].FI; --A[i].SE;
    }
    sort(A, A+M);
    ll prev = 0;
    ll rem = A[0].FI;
    for (int i=0; i<M; ++i) {
        A[i].FI -= rem;
        if (A[i].FI - prev >= 2) {
            const ll x = (((A[i].FI - prev) >> 1) << 1) - 2;
            A[i].FI -= x;
            rem += x;
        }
        prev = A[i].FI;
    }
    debug1(A, M);
    N = A[M-1].FI + 1;
    for (int i=0; i<N; ++i) { 
        G[i][0] = G[i][1] = 0;
    }
    for (int i=0; i<M; ++i) { 
        G[A[i].FI][A[i].SE] = 1;
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<4; ++j) {
            dp[i][j] = false;
        }
    }
    dp[0][G[0][0] + (G[0][1] << 1)] = true;
    for (int i=1; i<N; ++i) {
        for (int j=0; j<4; ++j) {
            if ((G[i][0] > (j & 1)) || (G[i][1] > ((j >> 1) & 1))) dp[i][j] = false;
            else {
                const int k = j - G[i][0] - (G[i][1] << 1);
                debug(i, j, k);
                dp[i][j] = dp[i-1][k ^ 3];
                if (j == 3 && (G[i][0] + G[i][1] == 0)) dp[i][j] |= dp[i-1][3];
            }
        }
    }
    debug2(G, N, 2);
    debug2(dp, N, 4);

    cout << (dp[N-1][3] ? "YES" : "NO") << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
2 3
1 1
1 2
2 1

5 2
2 2
2 3

3 4
1 1
2 1
1 3
2 3
*/
