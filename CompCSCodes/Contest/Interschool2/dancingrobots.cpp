//dancingrobots.cpp created at 11/21/20 12:27:38

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

void setIO(const string& filename = "dancingrobots") {
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
const int MN = 5005;
const int LG = 30;

ll N, M, K, Q;
ll A[2][MN];
ll G[MN][MN];
//set<ll> adj[MN];

ll perm[LG][MN];
ll pct[LG][MN];

ll ans[MN], ans2[MN];
void brute() {
    bool idx = false;
    for (int i=0; i<N; ++i) {
        A[0][i] = i;
    }
    for (int i=0; i<Q; ++i) {
        for (int j=0; j<M; ++j) {
            for (int k=0; k<N; ++k) {
                A[!idx][G[j][k]] = A[idx][k];
            }
            ++ans2[A[!idx][N-1]];
            idx = !idx;
        }
    }
}
void solve() {
    for (int i=0; i<N; ++i) {
        A[0][i] = i;
    }

    for (int i=0; i<M; ++i) {
        for (int j=0; j<N; ++j) {
            A[!(i&1)][j] = G[i][A[i&1][j]];
            if (A[!(i&1)][j] == N-1) ++pct[0][j];
        }
    }
    for (int i=0; i<N; ++i) {
        perm[0][i] = A[M&1][i];
    }

    for (int i=1; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            pct[i][j] = pct[i-1][j] + pct[i-1][perm[i-1][j]];
            perm[i][j] = perm[i-1][perm[i-1][j]];
        }
    }

    for (int i=0; i<N; ++i) {
        A[0][i] = i;
    }
    bool idx = false;
    int rem = Q;
    for (int i=LG-1; i>=0; --i) {
        if (rem >= (1 << i)) {
            rem -= (1 << i);
            
            for (int j=0; j<N; ++j) {
                ans[A[idx][j]] += pct[i][j];
                A[!idx][perm[i][j]] = A[idx][j];
            }

            idx = !idx;
        }
    }

    for (int i=0; i<N; ++i) {
        cout << ans[i] << '\n';
    }
}

        
const int MXN = 500;
const int MXM = 500;
const int MXQ = 10000;
void go() {
    ll T = 100;
    for (int t=0; t<T; ++t) {
        for (int i=0; i<MN; ++i) {
            A[0][i] = A[1][i] = ans[i] = ans2[i] = 0;
            for (int j=0; j<LG; ++j) {
                perm[j][i] = pct[j][i] = 0;
            }
        }
        N = rand() % MXN; ++N; M = rand() % MXM; ++M; Q = rand() % MXQ; ++Q;
        debug(N, M, Q);
        for (int i=0; i<M; ++i) {
            for (int j=0; j<N; ++j) {
                G[i][j] = j;
            }
            random_shuffle(G[i], G[i] + N);
        }
    
        solve();
        brute();
        for (int i=0; i<N; ++i) {
            if (ans[i] != ans2[i]) {
                debug1(ans, N);
                debug1(ans2, N);
                cerr << "ERROR at i=" << i << ", ans=" << ans[i] << ", ans2=" << ans2[i] << endl;
                cerr << N << ' ' << M << ' ' << Q << endl;
                for (int j=0; j<M; ++j) {
                    for (int k=0; k<N; ++k) {
                        cerr << G[j][k] + 1 << ' ';
                    }
                    cerr << endl;
                }
                assert(false);
            }
        }
    }
}
        
int main() {
    setIO();

    //go(); return 0;

    cin >> N >> M >> Q;
    for (int i=0; i<M; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> G[i][j];
            --G[i][j];
        }
    }
    solve();
    
    return 0;
}
