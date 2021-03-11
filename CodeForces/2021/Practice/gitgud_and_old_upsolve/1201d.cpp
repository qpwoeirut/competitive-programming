//1201d.cpp created at 01/07/21 19:18:12

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
const int MN = 201001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
pll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll safe[MN];
ll treasure[MN][2];
ll dp[MN][2];

void solve(int testcase) {
    cin >> N >> M >> K >> Q;
    for (int i=0; i<N; ++i) {
        treasure[i][0] = INIT;
        treasure[i][1] = 0;

        dp[i][0] = dp[i][1] = INF;
    }

    vector<ll> rows;
    rows.PB(0);
    for (int i=0; i<K; ++i) {
        cin >> A[i].FI >> A[i].SE;
        --A[i].FI; --A[i].SE;
        rows.PB(A[i].FI);
    }
    for (int i=0; i<Q; ++i) {
        cin >> safe[i];
        --safe[i];
    }
    sort(safe, safe+Q);

    sort(all(rows));
    rows.resize(unique(all(rows)) - rows.begin());
    const int R = sz(rows);

    ll up_cost = 0;
    for (int i=0; i<K; ++i) {
        chmx(up_cost, A[i].FI);
        A[i].FI = LB(all(rows), A[i].FI) - rows.begin();

        chmn(treasure[A[i].FI][0], A[i].SE);
        chmx(treasure[A[i].FI][1], A[i].SE);
    }

    if (treasure[0][0] == INIT) treasure[0][0] = 0;
    dp[0][0] = treasure[0][1] + (treasure[0][1] - treasure[0][0]);
    dp[0][1] = treasure[0][1];

    for (int r=1; r<R; ++r) {
        ll reach_left = INF, reach_right = INF;

        for (int i=0; i<4; ++i) {
            int idx;
            if (i >= 2) {
                idx = (UB(safe, safe+Q, treasure[r-1][i&1]) - safe) - 1;
            } else {
                idx = LB(safe, safe+Q, treasure[r-1][i&1]) - safe;
            }

            if (0 <= idx && idx < Q) {
                const ll dist = dp[r-1][i&1] + abs(safe[idx] - treasure[r-1][i&1]);
                chmn(reach_left, dist + abs(treasure[r][0] - safe[idx]));
                chmn(reach_right, dist + abs(treasure[r][1] - safe[idx]));
            }
        }

        const ll between = treasure[r][1] - treasure[r][0];
        dp[r][0] = reach_right + between;
        dp[r][1] = reach_left + between;
    }
    debug2(treasure, R, 2);
    debug2(dp, R, 2);

    cout << up_cost + min(dp[R-1][0], dp[R-1][1]) << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
/*
3 3 2 1
3 1
3 2
3
*/

