//dmopc20c4p5.cpp created at 03/14/21 17:29:13

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
const int MN = (1 << 21) + 6;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN];// , B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

bool check() {
    int p = 1;
    for (int i=0; i<K; ++i) {
        p *= A[i];
    }
    int sum = 0;
    for (int i=0; i<N; ++i) {
        sum += p;
        p *= A[(i+K) % N];
        p /= A[i];
    }
    return sum == 0;
}

bool brute() {
    for (int i=0; i<(1 << N); ++i) {
        for (int j=0; j<N; ++j) {
            if ((i >> j) & 1) {
                A[j] = 1;
            } else {
                A[j] = -1;
            }
        }

        if (check()) {
            if (accumulate(A, A+N/2, 0) != N/2) continue;
            if (accumulate(A+N/2, A+N/2+K, 0) != -K) continue;
            //debug1(A, N);
            return true;
        }
    }
    return false;
}

bool solve() {
    if ((N & 1) || N == K || ((N % 4) == 2 && (K & 1) == 0)) {
        return false;
    }
    if (K & 1) {
        for (int i=0; i<N; ++i) {
            A[i] = (i & 1) ? 1 : -1;
        }
        return true;
    }
    if (K*2 == N) {
        for (int i=0; i<N; ++i) {
            A[i] = i ? -1 : +1;
        }
        return true;
    }
    chmn(K, N-K);
    for (int i=0; i<N; ++i) {
        if (i*2 < N) A[i] = 1;
        else A[i] = -1;
    }
    for (int i=N/2 + K; i<N; i+=K) {
        A[i] = 1;
    }
    return true;
}

void test() {
    for (N=1; N<=300; ++N) {
        for (int k=1; k<=N; ++k) {
            debug(N, K);
            K = k;
            if (solve()) {
                if (!check()) {
                    debug(N, K);
                    debug1(A, N);
                    debug(brute());
                    debug1(A, N);
                    assert(0);
                }
            } else {
                continue;
                if (brute()) {
                    debug(N, K);
                    debug1(A, N);
                    assert(0);
                }
            }
        }
    }
}
        
        
int main() {
    //test(); return 0;
    setIO();
    
    ll T = 1;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        cin >> N >> K;
        //brute(); continue;
        if (solve()) {
            for (int i=0; i<N; ++i) {
                if (i) cout << ' ';
                cout << A[i];
            }
            cout << '\n';
            assert(check());
        } else {
            cout << "0\n";
        }
    }
    
    return 0;
}