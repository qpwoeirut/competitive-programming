//1487e.cpp created at 03/01/21 19:08:18

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
const int MN = 1001001;
const ll INF = 2e18 + 1;

ll N[4], M[4], K, Q;
ll A[4][MN]; //, B[MN];
ll cost[4][MN];
//ll G[MN][MN];
vector<ll> adj[4][MN];

pll cur[MN];
int m[MN];
void calc(const int i1, const int i2) {
    for (int i=0; i<N[i1]; ++i) {
        cur[i] = pll(cost[i1][i], i);
    }
    sort(cur, cur+N[i1]);

    for (int i=0; i<N[i1]; ++i) {
        m[cur[i].SE] = i;
    }

    for (int i=0; i<N[i2]; ++i) {
        for (int j=0; j<adj[i2][i].size(); ++j) {
            adj[i2][i][j] = m[adj[i2][i][j]];
        }
        sort(all(adj[i2][i]));
        ll lo = 0, hi = adj[i2][i].size();
        while (lo < hi) {
            ll mid = (lo + hi) >> 1;
            if (adj[i2][i][mid] == mid) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        debug(i2, i, lo);
        const ll mex = lo < N[i1] ? cur[lo].FI : INF;
        cost[i2][i] = A[i2][i] + mex;
    }
}

void solve(int testcase) {
    cin >> N[0] >> N[1] >> N[2] >> N[3];
    for (int i=0; i<4; ++i) {
        for (int j=0; j<N[i]; ++j) {
            cin >> A[i][j];
        }
    }

    for (int i=1; i<4; ++i) {
        cin >> M[i];
        for (int j=0; j<M[i]; ++j) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            adj[i][y].push_back(x);
        }
    }

    copy(A[0], A[0] + N[0], cost[0]);
    calc(0, 1);
    calc(1, 2);
    calc(2, 3);

    debug2(cost, 4, max({N[0], N[1], N[2], N[3]}));

    ll ans = *min_element(cost[3], cost[3] + N[3]);
    if (ans >= INF) {
        ans = -1;
    }
    cout << ans << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
