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
    if (filename.size() > 0) {
        freopen((filename + ".txt").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353;
const int INIT = 1001001001;
const int MN = 1000001;
const int MXV = 5e8 + 100;

ll N, M, K;
ll L[MN], H[MN], W[MN];
ll ans[MN];
//int G[MN][MN];
//set<int> adj[MN];

struct Item {
    ll x, h;
    int idx;
    bool start;
    Item(ll a, ll b, int c, bool d) {
        x = a;
        h = b;
        idx = c;
        start = d;
    }
};
struct cmp {
    inline const bool operator()(const Item& a, const Item& b) const {
        if (a.x == b.x) {
            return a.idx < b.idx;
        }
        return a.x < b.x;
    }
};

void solve(int t) {
    cin >> N >> K;
    
    for (int i=0; i<K; i++) {
        cin >> L[i];
    }
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    for (int i=K; i<N; i++) {
        L[i] = ((a * L[i-2] + b * L[i-1] + c) % d) + 1;
    }
    
    for (int i=0; i<K; i++) {
        cin >> W[i];
    }
    cin >> a >> b >> c >> d;
    for (int i=K; i<N; i++) {
        W[i] = ((a * W[i-2] + b * W[i-1] + c) % d) + 1;
    }

    for (int i=0; i<K; i++) {
        cin >> H[i];
    }
    cin >> a >> b >> c >> d;
    for (int i=K; i<N; i++) {
        H[i] = ((a * H[i-2] + b * H[i-1] + c) % d) + 1;
    }

    vector<pair<ll, pll>> range;
    for (int i=0; i<N; i++) {
        for (int j=0; j<sz(range); j++) {
            if (range[j].SE.FI <= L[i] && L[i] + W <= range[j].SE.SE) {
                break;
            }
            if (range[j].SE.FI <= L[i] && L[i] <= range[j].SE.SE) {

    }
    
    ll prod = 1;
    for (int i=0; i<N; i++) {
        prod = (prod * ans[i]) % MOD;
    }

    debug1(L, N);
    debug1(W, N);
    debug1(H, N);
    debug1(ans, N);
    cout << "Case #" << t << ": " << prod << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}