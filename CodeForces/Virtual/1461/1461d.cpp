//1461d.cpp created at 03/08/21 13:03:04

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
ll A[MN], B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
set<ll> ok;


ll psum[MN];
void rec(const int lo, const int hi) {
    ok.insert(psum[hi] - psum[lo]);
    if (lo + 1 == hi) return;
    ll mid = (A[hi-1] + A[lo]) >> 1;
    mid = UB(A+lo, A+hi, mid) - A;
    if (mid != hi) rec(lo, mid);
    if (mid != lo) rec(mid, hi);
}

void solve(int testcase) {
    ok.clear();
    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);
    psum[0] = 0;
    for (int i=0; i<N; ++i) {
        psum[i+1] = psum[i] + A[i];
    }
    rec(0, N);

    for (int i=0; i<Q; ++i) {
        ll x;
        cin >> x;
        cout << (ok.count(x) ? "Yes" : "No") << '\n';
    }
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
