//p2.cpp created at 02/15/21 12:02:34

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
const int MN = 1501;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

int perm[MN];
ll brute() {
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (i == j) continue;
            for (int k=0; k<N; ++k) {
                if (i == k || j == k) continue;
                for (int l=0; l<N; ++l) {
                    if (i == l || j == l || k == l) continue;
                    if (A[i] * A[j] == A[k] * A[l]) {
                        ++ans;
                        //debug(i, j, k, l);
                    }
                }
            }
        }
    }

    return ans;
}
        
ll nums[MN * MN];
ll ct[MN * MN];
ll solve(int testcase) {
    M = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (i == j) continue;
            nums[M++] = A[i] * A[j];
        }
    }
    sort(nums, nums+M);
    M = unique(nums, nums+M) - nums;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (i == j) continue;
            const int idx = LB(nums, nums+M, A[i] * A[j]) - nums;
            ++ct[idx];
        }
    }
    for (int i=0; i<M; ++i) {
        ct[i] -= 2;
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (i == j) continue;
            const int idx = LB(nums, nums+M, A[i] * A[j]) - nums;
            ans += ct[idx];
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (i == j) continue;

            if (A[i] == A[j]) {
                ans -= (N - 2) * 4;
            }
        }
    }
    return ans;
}

void test() {
    for (N=1; N<=10; ++N) {
        cerr << N << endl;
        for (int t=0; t<N * N * 10000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = (rand() % 100) + 1;
            }

            ll sans = solve(0), bans = brute();
            if (sans != bans) {
                cout << sans << ' ' << bans << endl;
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    if (i) cout << ' ';
                    cout << A[i];
                }
                cout << endl;
            }
            assert(sans == bans);
        }
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

        cout << solve(t) << '\n';
    }
    
    return 0;
}
/*
2
1 1
*/
