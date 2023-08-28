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
const int MN = 205;

ll R, G, B;
//int A[MN];
//int G[MN][MN];
//set<int> adj[MN];
vector<ll> X, Y, Z;
ll val[MN][MN][MN];
ll dp(int r, int g, int b) {
    int done = 0;
    if (r == R) {
        ++done;
    }
    if (g == G) {
        ++done;
    }
    if (b == B) {
        ++done;
    }
    if (done >= 2) return 0;
    if (val[r][g][b] != -1) {
        return val[r][g][b];
    }
    if (done == 1) {
        if (r == R) {
            val[r][g][b] = Y[g] * Z[b] + dp(r, g+1, b+1);
        } else if (g == G) {
            val[r][g][b] = X[r] * Z[b] + dp(r+1, g, b+1);
        } else {
            val[r][g][b] = X[r] * Y[g] + dp(r+1, g+1, b);
        }

        // cout << r << ' ' << g << ' ' << b << ": " << val[r][g][b] << endl;
        return val[r][g][b];
    }
    
    chmx(val[r][g][b], X[r] * Y[g] + dp(r+1, g+1, b));
    chmx(val[r][g][b], X[r] * Z[b] + dp(r+1, g, b+1));
    chmx(val[r][g][b], Y[g] * Z[b] + dp(r, g+1, b+1));
    //cout << r << ' ' << g << ' ' << b << ": " << val[r][g][b] << endl;

    return val[r][g][b];
}

void solve(int t) {
    cin >> R >> G >> B;

    X = vector<ll>(R);
    Y = vector<ll>(G);
    Z = vector<ll>(B);

    for (int i=0; i<R; i++) {
        cin >> X[i];
    }
    for (int i=0; i<G; i++) {
        cin >> Y[i];
    }
    for (int i=0; i<B; i++) {
        cin >> Z[i];
    }

    sort(all(X), greater<int>());
    sort(all(Y), greater<int>());
    sort(all(Z), greater<int>());

    for (int i=0; i<=R; i++) {
        for (int j=0; j<=G; j++) {
            for (int k=0; k<=B; k++) {
                val[i][j][k] = -1;
            }
        }
    }

    cout << dp(0, 0, 0) << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
