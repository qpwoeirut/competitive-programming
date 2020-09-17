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
const int MN = 1000001;

ll N, M, K;
//int A[MN];
string G[MN];
//set<int> adj[MN];
ll changes[MN][10];
ll dist(int idx, int state) {
    ll cost = 0;
    for (int i=0; i<N; i++) {
        if (G[i][idx] - '0' != ((state >> i) & 1)) {
            ++cost;
        }
    }
    return cost;
}
ll dp(int idx, int prev) {
    if (idx == M) return 0;
    if (changes[idx][prev] != -1) {
        return changes[idx][prev];
    }
    changes[idx][prev] = INIT;

    int cur[N][2];
    for (int i=0; i<N; i++) {
        cur[i][0] = (prev >> i) & 1;
    }
    for (int n=0; n<(1<<N); n++) {
        for (int i=0; i<N; i++) {
            cur[i][1] = (n >> i) & 1;
        }
        bool ok = true;
        for (int i=0; i+1<N; i++) {
            if (((cur[i][0] + cur[i][1] + cur[i+1][0] + cur[i+1][1]) & 1) == 0) {
                ok = false;
            }
        }
        if (ok) {
            chmn(changes[idx][prev], dist(idx, n) + dp(idx+1, n));
        }
    }
    //cout << idx << ' ' << prev << ' ' << changes[idx][prev] << endl;

    return changes[idx][prev];
}

void solve(int t) {
    cin >> N >> M;

    for (int i=0; i<N; i++) {
        cin >> G[i];
    }

    if (N == 1 || M == 1) {
        cout << 0 << endl;
        return;
    }

    if (N >= 4 && M >= 4) {
        cout << -1 << endl;
        return;
    }

    assert(N == 2 || N == 3);
    for (int i=0; i<=M; i++) {
        for (int j=0; j<=(1<<N); j++) {
            changes[i][j] = -1;
        }
    }

    ll ans = INIT;
    for (int i=0; i<(1<<N); i++) {
        ll cost = dp(1, i) + dist(0, i);
        //cout << 0 << ' ' << i << ' ' << cost << endl;
        chmn(ans, cost);
    }
    
    if (ans >= INIT) {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
} 
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
