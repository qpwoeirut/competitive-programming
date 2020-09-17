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
typedef pair<int,bool> pib;
typedef pair<ll,bool> plb;
typedef pair<double,double> pdd;
typedef map<ll,ll> mll;
typedef map<char, int> mci;
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

ll binpow(const ll& x, const ll& p, const ll& mod) {assert(mod>0);
	if (p == 0) return 1;
	if (p == 1) return x % mod;
	if (p & 1) return (binpow((x*x) % mod, p/2, mod) * x) % mod;
	return binpow((x*x) % mod, p/2, mod) % mod;
}

template <class T> void chmn(T& a, const T& b) {if (a>b) a=b;}
template <class T> void chmx(T& a, const T& b) {if (a<b) a=b;}

void setIO(const string& filename = "") {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353;
const int INIT = 1001001001;
const int MN = 2005;

ll N, M, K;
//int A[MN];
int H[MN][MN];
char G[MN][MN];
//set<int> adj[MN];
int diag_left[MN][MN], diag_right[MN][MN];
bool ok(int r, int c, int thres) {
    if (G[r][c] != G[r-1][c] || G[r][c] != G[r+1][c] || G[r][c] != G[r][c-1] || G[r][c] != G[r][c+1]) return false;
    return min(min(H[r-1][c], H[r+1][c]), min(H[r][c-1], H[r][c+1])) >= thres; 
}
void solve(int t) {
    //N = M = 2000;
    cin >> N >> M;

    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            //G[i][j] = 'a';
            cin >> G[i][j];   
            H[i][j] = 1;
        }
    }
    for (int i=1; i<=N; i++) {
        int r=i, c=1;
        int len = 1;
        while (r <= N && c <= M) {
            if (G[r-1][c-1] == G[r][c]) {
                ++len;
            } else {
                len = 1;
            }
            diag_right[r][c] = len;
            ++r; ++c;
        }

        len = 1;
        r = i, c = M;
        while (r <= N && c > 0) {
            if (G[r-1][c+1] == G[r][c]) {
                ++len;
            } else {
                len = 1;
            }
            diag_left[r][c] = len;
            ++r; --c;
        }
    }
    for (int j=1; j<=M; j++) {
        int r=1, c=j;
        int len = 1;
        while (r <= N && c <= M) {
            if (G[r-1][c-1] == G[r][c]) {
                ++len;
            } else {
                len = 1;
            }
            diag_right[r][c] = len;
            ++r; ++c;
        }

        len = 1;
        r = 1, c = j;
        while (r <= N && c > 0) {
            if (G[r-1][c+1] == G[r][c]) {
                ++len;
            } else {
                len = 1;
            }
            diag_left[r][c] = len;
            ++r; --c;
        }
    }


    for (int i=2; i<N; i++) {
        for (int j=2; j<M; j++) {
            if (G[i-1][j] != G[i][j]) {
                H[i][j] = 1;
                continue;
            }
            int prev = H[i-1][j];
            H[i][j] = prev - 1;
            for (int k=prev-1; k+i<=N && k<=prev; k++) {
                if (G[i+k][j] != G[i][j] || min(diag_left[i+k][j], diag_right[i+k][j]) <= k) {
                    H[i][j] = k;
                    break;
                } else {
                    H[i][j] = k+1;
                }
            }
        }
    }
    //debug2(diag_left, N+1, M+1);
    //debug2(diag_right, N+1, M+1);
    //debug2(H, N+1, M+1);


    ll ans = 0;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            ans += H[i][j];
        }
    }

    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
