//1473e.cpp created at 01/14/21 08:14:36

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
set<pll> adj[MN];

struct Item {
    ll u;
    ll cost;
    int used;

    Item(const ll _u, const ll _cost, const int _used) {
        u = _u;
        cost = _cost;
        used = _used;
    }

    inline const bool operator<(const Item& o) const {
        if (used == o.used) {
            if (cost == o.cost) return u > o.u;
            return cost > o.cost;
        }
        return used > o.used;
    }
};

ll dist[MN][4];

void solve(int testcase) {
    cin >> N >> M;
    fill(adj, adj+N, set<pll>());
    for (int i=0; i<M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].emplace(v, w);
        adj[v].emplace(u, w);
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<4; ++j) {
            dist[i][j] = INF;
        }
    }

    priority_queue<Item> pq;
    pq.emplace(0, 0, 0);
    dist[0][0] = 0;

    while (pq.size() > 0) {
        const Item cur = pq.top(); pq.pop();

        if (dist[cur.u][cur.used] < cur.cost) continue;
        debug(cur.u, cur.cost, cur.used);

        for (const pll& p: adj[cur.u]) {
            if (chmn(dist[p.FI][cur.used], cur.cost + p.SE)) {
                pq.emplace(p.FI, dist[p.FI][cur.used], cur.used);
            }
            if ((cur.used & 1) == 0 && chmn(dist[p.FI][cur.used + 1], cur.cost + p.SE + p.SE)) {
                pq.emplace(p.FI, dist[p.FI][cur.used + 1], cur.used + 1);
            }
            if ((cur.used & 2) == 0 && chmn(dist[p.FI][cur.used + 2], cur.cost)) {
                pq.emplace(p.FI, dist[p.FI][cur.used + 2], cur.used + 2);
            }
            if ((cur.used & 3) == 0 && chmn(dist[p.FI][cur.used + 3], cur.cost + p.SE)) {
                pq.emplace(p.FI, dist[p.FI][cur.used + 3], cur.used + 3);
            }
        }
    }

    for (int i=1; i<N; ++i) {
        if (i > 1) cout << ' ';
        cout << dist[i][3];
    }
    cout << endl;
}
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
