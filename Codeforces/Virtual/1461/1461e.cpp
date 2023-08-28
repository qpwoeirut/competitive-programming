//1461e.cpp created at 03/08/21 13:03:05

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
ll A[MN];// , B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll L, R, T, X, Y;
bool solve(int testcase) {
    fill(A, A+X, false);

    if (X > Y) {
        if (K+Y > R) K -= Y;

        ll t = K / (X - Y);
        return t >= T;
    }

    ll t = 0;
    ll pt = 1;
    for (int i=0; i<=X; ++i) {
        K += min(pt, (R - K) / Y) * Y;
        if (K < X) {
            return t >= T;
        }
        pt = K / X;
        t += pt;
        if (t >= T) {
            break;
        }
        K %= X;
        if (A[K] && X <= Y) {
            break;
        }
        A[K] = true;
    }
    return true;
}

bool brute() {
    for (int i=0; i<T; ++i) {
        if (K+Y <= R) K += Y;
        K -= X;

        if (K < 0) {
            return false;
        }
    }

    return true;
}
        
void test() {
    for (T=1; T<=1000; ++T) {
        debug(T);
        L = 0;
        for (R=1; R<=100; ++R) {
            for (ll k=1; k<=R; ++k) {
                for (X=1; X<=100; ++X) {
                    for (Y=1; Y<=100; ++Y) {
                        K = k;
                        bool sans = solve(0);
                        K = k;
                        bool bans = brute();

                        if (sans != bans) {
                            debug(k+1, 1, R+1, T, X, Y);
                            debug(sans, bans);
                        }
                        assert(sans == bans);
                    }
                }
            }
        }
    }
}
        
int main() {
    //test(); return 0;
    setIO();
    
    cin >> K >> L >> R >> T >> X >> Y;

    R -= L;
    K -= L;
    cout << (solve(0) ? "Yes" : "No") << '\n';
    //cout << (brute() ? "Yes" : "No") << '\n';
    
    return 0;
}
/*
1 1 5 3 2 1
1 1 2 2 1 1
4 1 5 4 2 1
2 1 3 1 2 1
2 1 3 1 3 1
*/
