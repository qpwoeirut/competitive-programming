//1475g.cpp created at 03/02/21 19:49:39

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
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
ll dp[MN];
int pos[MN];
vector<int> divisors[MN];
ll solve(int testcase) {
    fill(pos, pos+MN, -1);

    for (int i=0; i<N; ++i) {
        dp[i] = i;
    }
    for (int i=1; i<N; ++i) {
        pos[A[i-1]] = i-1;
        for (const int div: divisors[A[i]]) {
            if (pos[div] == -1) continue;
            chmn(dp[i], dp[pos[div]] + i - pos[div] - 1);
        }
    }

    ll ans = INIT;
    for (int i=0; i<N; ++i) {
        chmn(ans, dp[i] + N - i - 1);
    }

    return ans;
}

bool ok(const vector<ll>& v) {
    for (int i=1; i<sz(v); ++i) {
        if (v[i] % v[i-1]) return false;
    }
    return true;
}

ll brute() {
    ll ans = N;
    for (ll i=0; i<(1 << N); ++i) {
        vector<ll> v;
        for (int j=0; j<N; ++j) {
            if ((i >> j) & 1) {
                v.PB(A[j]);
            }
        }
        if (ok(v)) {
            chmn(ans, N - sz(v));
        }
    }
    return ans;
}

void test() {
    for (N=1; N<=10; ++N) {
        debug(N);
        for (int t=0; t<10000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = rand() % N;
                ++A[i];
            }
            sort(A, A+N);

            ll ans = solve(0);
            ll bans = brute();

            if (ans != bans) {
                debug(ans, bans);

                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    if (i) cout << ' ';
                    cout << A[i];
                }
                cout << endl;
            }
            assert(ans == bans);
        }
    }
}
        
int main() {
    setIO();

    for (int i=1; i<MN; ++i) {
        for (int j=i; j<MN; j+=i) {
            divisors[j].push_back(i);
        }
    }

    //test(); return 0;
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; ++t) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        sort(A, A+N);

        cout << solve(t) << '\n';
    }
    
    return 0;
}
/*
1
2
2 1

1
3
3 2 3
*/
