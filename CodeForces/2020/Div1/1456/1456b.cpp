//1456b.cpp created at 11/28/20 22:49:56

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

template <class T> bool chmn(T& a, const T& b) {return ((a>b) ? ((a=b) || true) : false);}
template <class T> bool chmx(T& a, const T& b) {return ((a<b) ? ((a=b) || true) : false);}

void setIO(const string& filename = "") {
	cin.tie(0)->sync_with_stdio(0);
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

int go() {
    for (int i=1; i<N; ++i) {
        if (A[i-1] > A[i]) assert(false);
    }

    for (int i=1; i<=33; ++i) {
        for (int j=i; j<N; ++j) {
            ll total = 0;
            for (int k=0; k<=i; ++k) {
                total ^= A[j - k];
            }
            ll cur = 0;
            for (int k=i; k>0; --k) {
                cur ^= A[j - k];
                total ^= A[j - k];
                if (cur > total) return i - 1;
            }
        }
    }
    return -1;
}

int brute() {
    int ans = N+1;
    for (int i=0; i<N; ++i) {
        int cur = 0;
        for (int j=i; j>=0; --j) {
            cur ^= A[j];

            int R = 0;
            for (int k=i+1; k<N; ++k) {
                R ^= A[k];

                if (cur > R) {
                    chmn(ans, k - j - 1);
                }
            }
        }
    }
    if (ans == N+1) ans = -1;
    return ans;
}

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    //debug(brute());
    cout << go() << endl;
}
        
void test() {
    for (N=2; N<=50; ++N) {
        debug(N);
        for (int t=0; t<200000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = (rand() % (MOD - 7)) + 1;
                //A[i] %= 1000;
            }
            sort(A, A+N);
            //if (brute() >= 3) {
            //    debug(brute());

            //    cout << N << endl;
            //    for (int i=0; i<N; ++i) {
            //        cout << A[i] << ' ';
            //    }
            //    cout << endl;
            //}

            int a1 = go(), a2 = brute();
            if (a1 != a2) {
                debug(a1, a2);

                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    cout << A[i] << ' ';
                }
                cout << endl;
                assert(false);
            }
        }
    }
}
        
int main() {
    setIO();
    
    solve(0);
    //test();
    
    return 0;
}

