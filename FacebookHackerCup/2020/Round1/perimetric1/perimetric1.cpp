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

ll N, M, K, W;
ll L[MN], H[MN];
ll ans[MN];
//int G[MN][MN];
//set<int> adj[MN];
ll height[MXV];
void solve(int t) {
    cin >> N >> K >> W;
    
    for (int i=0; i<K; i++) {
        cin >> L[i];
    }
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    for (int i=K; i<N; i++) {
        L[i] = ((a * L[i-2] + b * L[i-1] + c) % d) + 1;
        assert(L[i-1] < L[i]);
    }
    
    for (int i=0; i<K; i++) {
        cin >> H[i];
    }
    cin >> a >> b >> c >> d;
    for (int i=K; i<N; i++) {
        H[i] = ((a * H[i-2] + b * H[i-1] + c) % d) + 1;
    }

    ll cur = 0;
    for (int i=0; i<N; i++) {
        for (ll pos=L[i]; pos<L[i]+W; pos++) {
            assert(0 < pos && pos + 1 < MXV);
            if (H[i] <= height[pos]) {
                continue;
            }
            if (height[pos] == 0) {
                cur += 2;
            }
            ll orig_diff = abs(height[pos] - height[pos-1]) + abs(height[pos] - height[pos+1]);
            height[pos] = H[i];
            ll cur_diff = abs(height[pos] - height[pos-1]) + abs(height[pos] - height[pos+1]);

            cur += cur_diff - orig_diff;
            cur %= MOD;
        }
        ans[i] = cur;
    }
    
    ll prod = 1;
    for (int i=0; i<N; i++) {
        prod = (prod * ans[i]) % MOD;
    }

    //debug(W);
    //debug1(L, N);
    //debug1(H, N);
    //debug1(ans, N);
    cout << "Case #" << t << ": " << prod << endl;


    for (int i=0; i<N; i++) {
        for (ll pos=L[i]-1; pos<=L[i] + W; pos++) {
            height[pos] = 0;
        }
    }
    //assert(*max_element(height, height+MXV) == 0);
}
        
        
int main() {
    setIO("perimetric_chapter_1");
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
