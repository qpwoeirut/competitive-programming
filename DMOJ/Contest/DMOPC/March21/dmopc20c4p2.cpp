//dmopc20c4p2.cpp created at 03/14/21 16:12:20

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
#define eb emplace_back
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
const int MN = 1001001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
pll A[MN];// , B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

void flip(set<ll>& s, const ll val) {
    auto it = s.insert(val);
    if (it.se == false) {
        s.erase(it.fi);
    }
}

void solve(int testcase) {
    cin >> N >> M >> K;
    set<ll> row, col;
    for (int i=0; i<K; ++i) {
        cin >> A[i].fi >> A[i].se;

        flip(row, A[i].fi);
        flip(col, A[i].se);
    }

    vector<pll> ans;
    while (sz(row) > 0 && sz(col) > 0) {
        const ll r = *row.begin(), c = *col.begin();
        ans.eb(r, c);
        row.erase(row.begin());
        col.erase(col.begin());
    }
    while (sz(row) > 0) {
        assert(sz(row) >= 2);
        const ll r1 = *row.begin();
        row.erase(row.begin());
        const ll r2 = *row.begin();
        row.erase(row.begin());
        ans.eb(r1, 1);
        ans.eb(r2, 1);
    }
    while (sz(col) > 0) {
        assert(sz(col) >= 2);
        const ll c1 = *col.begin();
        col.erase(col.begin());
        const ll c2 = *col.begin();
        col.erase(col.begin());
        ans.eb(1, c1);
        ans.eb(1, c2);
    }

    cout << sz(ans) << '\n';
    for (const pll& p: ans) {
        cout << p.fi << ' ' << p.se << '\n';
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
