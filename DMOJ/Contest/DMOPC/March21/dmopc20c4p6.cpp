//dmopc20c4p6.cpp created at 03/14/21 16:39:21

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
pll edge[MN];

int cur[MN], ans[MN];

#define u first
#define v second

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        cin >> edge[i].u >> edge[i].v;
        --edge[i].u; --edge[i].v;
    }

    int best = 0;
    for (int i=0; i<(1 << N); ++i) {
        for (int j=0; j<N; ++j) {
            cur[j] = (i >> j) & 1;
            A[j] = 0;
        }
        for (int j=0; j<M; ++j) {
            if (cur[edge[j].u] == cur[edge[j].v]) {
                A[edge[j].u] ^= 1;
                A[edge[j].v] ^= 1;
            }
        }
        int score = 0;
        for (int j=0; j<N; ++j) {
            score += A[j] == 0;
        }
        if (chmx(best, score)) {
            copy(cur, cur+N, ans);
        }
    }
    
    cout << best << '\n';
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i] + 1;
    }
    cout << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
