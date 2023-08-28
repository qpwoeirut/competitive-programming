//906b.cpp created at 12/04/20 11:44:11

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

void solve(int testcase) {
    cin >> N >> M;

    vector<vector<ll>> G(N, vector<ll>(M));
    vector<vector<ll>> cpy(N, vector<ll>(M));
    if (N == 1 && M == 1) {
        cout << "YES\n1\n";
        return;
    } else if (N == 1) {
        if (M <= 3) {
            cout << "NO" << endl;
            return;
        }
        for (int i=0; i<M; ++i) {
            G[0][i] = i<M/2 ? (i<<1) + 2 : ((i - M/2) << 1) + 1;
        }
    } else if (M == 1) {
        if (N <= 3) {
            cout << "NO" << endl;
            return;
        }
        for (int i=0; i<N; ++i) {
            G[i][0] = i<N/2 ? (i<<1) + 2 : ((i - N/2) << 1) + 1;
        }
    } else if ((N <= 2 && M <= 3) || (N <= 3 && M <= 2)) {
        cout << "NO" << endl;
        return;
    } else if (N <= M) {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                G[i][j] = i*M + j + 1;
            }
            rotate(G[i].begin(), G[i].begin() + ((i << 1) % M), G[i].end());
        }
        debug2(G, N, M);

        cpy = G;
        for (int j=0; j<M; ++j) {
            for (int i=0; i<N; ++i) {
                G[i][j] = cpy[(((i-j) % N) + N) % N][j];
            }
        }
    } else {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                cpy[i][j] = i*M + j + 1;
            }
        }
        
        for (int i=0; i<N; ++i) {
            for (int j=0; j<M; ++j) {
                G[i][j] = cpy[(i + (j << 1)) % N][j];
            }
        }
        debug2(G, N, M);

        for (int i=0; i<N; ++i) {
            rotate(G[i].begin(), G[i].begin() + (i % M), G[i].end());
        }
    }

    cout << "YES" << endl;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (j) cout << ' ';
            cout << G[i][j];
        }
        cout << '\n';
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
