//1487g.cpp created at 03/01/21 20:25:40
//had right idea for G, but didn't make a key observation
//read editorial for observation

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

const ll MOD = 998244353; //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 401;
const ll INF = 2e18 + 1;

struct mint {
    ll val;

    mint() {
        val = 0;
    }
    mint(const ll _val) {
        val = _val % MOD;
        if (val < 0) val += MOD;
    }

    mint operator+=(const mint& o) {
        val += o.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    mint operator-=(const mint& o) {
        val -= o.val;
        if (val < 0) val += MOD;
        return *this;
    }
    mint operator*=(const mint& o) {
        val = (val * o.val) % MOD;
        return *this;
    }

    mint operator+(const mint& o) {
        return mint(val + o.val);
    }
    mint operator-(const mint& o) {
        return mint(val - o.val);
    }
    mint operator*(const mint& o) {
        return mint(val * o.val);
    }

    mint operator+=(const ll o) {
        val += o;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    mint operator-=(const ll o) {
        val -= o;
        if (val < 0) val += MOD;
        return *this;
    }
    mint operator*=(const ll o) {
        val = (val * o) % MOD;
        if (val < 0) val += MOD;
        return *this;
    }
};

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

mint dp1[MN][MN][2][2];
mint dp2[2][MN][MN][3][3];

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<26; ++i) {
        cin >> A[i];
    }
    M = N;

    dp1[2][0][0][0] = 25 * 25;
    dp1[2][1][0][1] = dp1[2][1][1][0] = 25;
    dp1[2][2][1][1] = 1;
    for (int i=3; i<=N; ++i) {
        for (int j=0; j<=M; ++j) {
            dp1[i][j][0][0] = dp1[i-1][j][0][0] * 24 + dp1[i-1][j][1][0] * 25;
            dp1[i][j][1][0] = dp1[i-1][j][0][1] * 24 + dp1[i-1][j][1][1] * 25;
            if (j > 0) {
                dp1[i][j][0][1] = dp1[i-1][j-1][0][0];
                dp1[i][j][1][1] = dp1[i-1][j-1][0][1];
            }
        }
    }

    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            const int x = (i == 1) + (j == 1);
            const int y = (i == 2) + (j == 2);
            dp2[0][x][y][i][j] = binpow(24, 2 - x - y, MOD);
        }
    }
    for (int i=3; i<=N; ++i) {
        for (int j=0; j<=M; ++j) {
            for (int k=0; k<=M; ++k) {
                for (int c=0; c<3; ++c) {
                    for (int b=0; b<3; ++b) {
                        dp2[i&1][j][k][b][c] = 0;
                        const int jj = j - (c == 1), kk = k - (c == 2);
                        if (jj < 0 || kk < 0) continue;

                        for (int a=0; a<3; ++a) {
                            const ll opts = (c == 0 ? 24 : 1) - (a == c);

                            dp2[i&1][j][k][b][c] += dp2[!(i&1)][jj][kk][a][b] * opts;
                        }
                    }
                }
            }
        }
    }

    mint total = 26LL * 26LL * binpow(25, N-2, MOD);
    for (int i=0; i<26; ++i) {
        for (int j=A[i]+1; j<=M; ++j) {
            total -= dp1[N][j][0][0] + dp1[N][j][1][0] + dp1[N][j][0][1] + dp1[N][j][1][1];
            for (int k=i+1; k<26; ++k) {
                for (int l=A[k]+1; l<=M; ++l) {
                    for (int a=0; a<3; ++a) {
                        for (int b=0; b<3; ++b) {
                            total += dp2[N&1][j][l][a][b];
                        }
                    }
                }
            }
        }
    }

    cout << total.val << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
