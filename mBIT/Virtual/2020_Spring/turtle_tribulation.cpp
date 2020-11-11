//turtle_tribulation.cpp created at 11/10/20 16:46:53

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

typedef long double dbl;

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
const int MN = 2505;

const dbl EPS = 1e-10;

ll N, Z;
pll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

dbl K;
ll dp[MN][MN];
ll lo[MN], hi[MN];

const int LG = 13;
ll rmq[MN][LG];
void init(int idx) {
    for (int i=0; i<=Z; ++i) {
        rmq[i][0] = dp[idx][i];
    }
    for (int i=1; i<LG; ++i) {
        for (int j=0; j<=Z; ++j) {
            if (j + (1 << (i-1)) >= Z) {
                rmq[j][i] = INIT;
                continue;
            }
            rmq[j][i] = min(rmq[j][i-1], rmq[j + (1 << (i-1))][i-1]);
        }
    }
    debug1(dp[idx], Z+1);

    if (Z < 100) {
        for (int i=0; i<=Z; ++i) {
            for (int j=0; j<LG; ++j) {
                if (i+(1 << j) > Z) continue;
                ll mn = INIT;
                for (int k=i; k<i+(1 << j); ++k) {
                    chmn(mn, dp[idx][k]);
                }
                debug(i, j, mn, rmq[i][j]);
                assert(mn == rmq[i][j]);
            }
        }
    }
}
ll query(int L, int R) {
    ll ans = rmq[L][0];
    int cur = L;
    for (int i=LG-1; i>=0; --i) {
        if (cur + (1 << i) <= R) {
            chmn(ans, rmq[cur][i]);
            cur += (1 << i);
        }
    }
    return min(rmq[R][0], ans);
}

void solve(int testcase) {
    cin >> N >> Z >> K;

    for (int i=0; i<N; ++i) {
        cin >> A[i].FI >> A[i].SE;
        for (int j=0; j<=Z; ++j) {
            dp[i][j] = INIT;
        }
    }
    sort(A, A+N, cmps<ll,ll>());

    for (int dy=1; dy<=Z; ++dy) {
        lo[dy] = hi[dy] = 0;
        for (ll dx = -Z; dx<=Z; ++dx) {
            dbl rise = dy, run = dx;
            if (dx == 0 || abs(rise/run) >= K - EPS) {
                chmn(lo[dy], dx);
                chmx(hi[dy], dx);
            }
        }
    }
    //debug1(lo, Z+1);
    //debug1(hi, Z+1);
        

    dp[0][A[0].FI] = 0;
    for (int i=1; i<N; ++i) {
        init(i-1);
        debug2(rmq, N, LG);
        for (int j=1; j<=Z; ++j) {
            ll dy = A[i].SE - A[i-1].SE;
            ll dist = abs(j - A[i].FI);

            ll L = max(1LL, j + lo[dy]);
            ll R = min(Z, j + hi[dy]);
            ll mn = query(L, R);
            debug(i, j, L, R, mn);
            chmn(dp[i][j],mn + dist);
        }
    }
    debug2(dp, N, Z+1);

    cout << dp[N-1][A[N-1].FI] << endl;
}
        
        
int main() {
    setIO();
    //Z = 5;
    //dp[0][0] = 1;
    //dp[0][1] = 4;
    //dp[0][2] = 3;
    //dp[0][3] = 5;
    //dp[0][4] = 2;
    //init(0);
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
5 7 0.553537
2 1
6 5
2 4
2 3
6 6
*/
