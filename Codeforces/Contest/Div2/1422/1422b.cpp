//1422b.cpp created at 10/04/20 09:04:32

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
const int MN = 1001;

ll N, M, K;
//ll A[MN];
ll G[MN][MN];
//set<ll> adj[MN];

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
        }
    }

    ll ans = 0;
    for (int i=0; i<N/2; ++i) {
        for (int j=0; j<M/2; ++j) {
            ll val[4];
            val[0] = G[i][j];
            val[1] = G[N-i-1][j];
            val[2] = G[i][M-j-1];
            val[3] = G[N-i-1][M-j-1];

            ll best = 1e18;
            for (int k=0; k<4; ++k) {
                ll  cur = 0;
                for (int l=0; l<4; ++l) {
                    cur += abs(val[k] - val[l]);
                }
                chmn(best, cur);
            }
            ans += best;
        }
    }
    if (N & 1) {
        for (int j=0; j<M/2; ++j) {
            ans += abs(G[N/2][j] - G[N/2][M-j-1]);
        }
    }
    if (M & 1) {
        for (int i=0; i<N/2; ++i) {
            ans += abs(G[i][M/2] - G[N-i-1][M/2]);
        }
    }

    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
