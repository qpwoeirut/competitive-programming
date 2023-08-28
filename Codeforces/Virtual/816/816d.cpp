//816d.cpp created at 01/30/21 12:02:05

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

const ll MOD = 1e9 + 7; //998244353; //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll fact[MN];
ll invf[MN];

ll mult[MN];
ll solve_even(ll s, ll n, bool flip) {
    ll x = (n / 2) - 1;
    //debug((x & 1) ^ flip);
    for (ll i=0; i<n; ++i) {
        const ll k = i / 2;
        assert(x >= k);
        mult[i] = (((fact[x] * invf[k]) % MOD) * invf[x-k]) % MOD;
    }
    debug1(mult, n);
    ll op = 1;
    ll ans = 0;
    for (int i=0; i<n; ++i) {
        ans += (mult[i] * A[i+s] * op) % MOD;
        ans %= MOD;
        if ((x & 1) ^ flip) {
            op = -op;
        }
    }
    if (ans < 0) ans += MOD;
    return ans;
}

ll solve(int testcase) {
    if (N == 1) {
        return A[0];
    }
    fact[0] = invf[0] = 1;
    for (int i=1; i<=N; ++i) {
        fact[i] = (i * fact[i-1]) % MOD;
        invf[i] = binpow(fact[i], MOD-2, MOD);
    }
    ll ans = 0;
    if (N & 1) {
        if ((N >> 1) & 1) {
            ll a = solve_even(0, N-1, 0);
            ll b = solve_even(1, N-1, 1);
            //debug(a, b);
            ans = a + b;
        } else {
            ll a = solve_even(0, N-1, 1);
            ll b = solve_even(1, N-1, 0);
            //debug(a, b);
            ans = a - b;
        }
    } else {
        ans = solve_even(0, N, false);
    }

    ans %= MOD;
    if (ans < 0) ans += MOD;
    return ans;
}

ll p = 0;
ll p10() {
    return binpow(10, p++, MOD);
}

ll brute() {
    vector<ll> arr[2];
    arr[0] = vector<ll>(A, A+N);
    int idx = 0;
    ll op = 1;
    while (arr[idx].size() > 1) {
        debug(arr[idx]);
        arr[!idx].clear();
        
        for (int i=0; i+1<arr[idx].size(); ++i) {
            arr[!idx].push_back((arr[idx][i] + (arr[idx][i+1] * op)) % MOD);
            if (arr[!idx].back() < 0) arr[!idx].back() += MOD;
            op = -op;
        }
        idx = !idx;
    }
    return arr[idx][0];
}

        
void test() {
    for (N=1; N<=5000; N++) {
        p = 0;
        generate(A, A+N, p10);
        cout << N << endl;
        assert(brute() == solve(0));
    }
}
        
int main() {
    //test(); return 0;
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        cout << solve(t) << endl;
    }
    
    return 0;
}
/*
Op
((N - n) + 1) / 2
even positive, odd negative

4+
a - b + c - d

4-
a + b + c + d

6-
a - b + 2c - 2d + e - f

6+
a + b + 2c + 2d + e + f

8+
a - b + 3c - 3d + 3e - 3f + g - h
*/
