//server_ordering.cpp created at 10/24/20 12:37:05

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

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
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
const int MN = 1001001;

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll BIT[MN];
ll query(int i) {
    ll ret = 0;
    for (; i>0; i-=(i&-i)) ret += BIT[i];
    return ret;
}
void add(int i, ll val) {
    for (; i<=N; i+=(i&-i)) BIT[i] += val;
}
ll ans[MN];
ll sorted[MN];
mll pos;
void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        sorted[i] = A[i];
    }
    sort(sorted, sorted+N);

    M = unique(sorted, sorted+N) - sorted;
    for (int i=0; i<M; ++i) {
        pos[sorted[i]] = i+1;
    }
    debug(M);
    debug1(sorted, N);

    ll total = A[0];
    add(pos[A[0]], A[0]);
    ans[0] = 0;
    for (int i=1; i<N; ++i) {
        ll cost = total - query(pos[A[i]]);
        ans[i] = ans[i-1] + cost;
        debug(i, ans[i], cost, total);
        //debug(pos[A[i]], query(pos[A[i]]));
        total += A[i];
        add(pos[A[i]], A[i]);
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
