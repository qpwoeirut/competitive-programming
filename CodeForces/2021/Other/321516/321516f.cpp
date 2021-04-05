//321516f.cpp created at 03/31/21 19:22:09

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
const int MN = 1001001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN];// , B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

void solve1() {
    cin >> N >> M;
    cout << N+M << '\n';
}
void solve2() {
    cin >> N >> M;
    assert(false);
}
void solve3() {
    string S;
    cin >> S;
    assert(false);
}
void solve4() {
    assert(false);
}
void solve5() {
    assert(false);
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T >> K;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        if (K == 1) solve1();
        if (K == 3) solve3();
    }
    
    return 0;
}
/*
1: a+b
2
numbers from 1-1000?
  1 2 3 4 5 6 7 8 9 10
1 Y Y Y Y Y Y Y Y Y Y
2 Y Y N N N N Y N N N
3 Y Y Y N N Y N N N N
4 Y Y Y Y Y Y Y Y Y Y
5 Y Y N Y Y N N N N Y
6 Y Y Y N Y Y N N N Y
7 Y Y Y N N
*/
