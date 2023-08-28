//1401e.cpp created at 01/08/21 19:33:02

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
const int MN = 1001001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

#define x first
#define y second

const int MX = 1e6;
pll point[MN];
pll top[MN], bot[MN];

ll BIT[MN];
void upd(int idx, int val) {
    for (++idx; idx<=MX; idx+=(idx & -idx)) BIT[idx-1] += val;
}
ll query(int idx) {
    ll ret = 0;
    for (++idx; idx>0; idx-=(idx & -idx)) ret += BIT[idx - 1];
    return ret;
}

void solve(int testcase) {
    cin >> N >> M;

    ll ans = 1;
    for (int i=0; i<N; ++i) {
        ll yy, lx, rx;
        cin >> yy >> lx >> rx;

        point[i<<1] = pll(lx, yy);
        point[(i<<1)+1] = pll(rx+1, yy);

        if (lx == 0 && rx == MX) ++ans;
    }
    sort(point, point+N+N);

    int B = 0, T = 0;
    for (int i=0; i<M; ++i) {
        ll xx, by, ty;
        cin >> xx >> by >> ty;

        if (by == 0) {
            bot[B++] = pll(xx, ty);
        } else if (ty == MX) {
            top[T++] = pll(xx, by);
        }
        if (by == 0 && ty == MX) ++ans;
    }
    sort(bot, bot+B);
    sort(top, top+T);

    debug(ans);
    set<int> active;
    int idx = 0;
    for (int i=0; i<B; ++i) {
        for (; idx < N+N && point[idx].x <= bot[i].x; ++idx) {
            if (active.count(point[idx].y)) {
                active.erase(point[idx].y);
                upd(point[idx].y, -1);
            } else {
                active.insert(point[idx].y);
                upd(point[idx].y, 1);
            }
        }
        debug(active, bot[i]);

        ans += query(bot[i].y);
    }
    debug(ans);
    fill(BIT, BIT+MX+1, 0);
    active.clear();

    idx = 0;
    for (int i=0; i<T; ++i) {
        for (; idx < N+N && point[idx].x <= top[i].x; ++idx) {
            if (active.count(point[idx].y)) {
                active.erase(point[idx].y);
                upd(point[idx].y, -1);
            } else {
                active.insert(point[idx].y);
                upd(point[idx].y, 1);
            }
        }
        debug(active);

        ans += query(MX) - query(top[i].y - 1);
    }

    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
