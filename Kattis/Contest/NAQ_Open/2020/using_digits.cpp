//using_digits.cpp created at 02/11/21 17:32:36

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

struct Item {
    int r, c;
    int idx;
    ll cost;

    Item(const int _r, const int _c, const int _idx, const ll _cost) {
        r = _r;
        c = _c;
        idx = _idx;
        cost = _cost;
    }

    inline const bool operator<(const Item& o) const {
        return cost > o.cost;
    }
};

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 200;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
ll G[MN][MN];
//set<ll> adj[MN];

ll dist[MN][MN][MN];
void solve(int testcase) {
    cin >> M >> N;
    string S;
    cin >> S;
    K = S.size();
    for (int i=0; i<K; ++i) {
        A[i] = 1 + S[i] - '0';
    }
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            char c;
            cin >> c;
            G[i][j] = c - '0';
        }
    }
    reverse(G, G+N);

    priority_queue<Item> pq;
    pq.emplace(0, 0, 0, G[0][0]);
    dist[0][0][0] = G[0][0];
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            for (int k=0; k<=K; ++k) {
                dist[i][j][k] = INF;
            }
        }
    }
    while (pq.size() > 0) {
        const Item cur = pq.top(); pq.pop();

        if (chmn(dist[cur.r+1][cur.c][cur.idx], cur.cost + G[cur.r+1][cur.c])) {
            pq.emplace(cur.r+1, cur.c, cur.idx, dist[cur.r+1][cur.c][cur.idx]);
        }
        if (chmn(dist[cur.r][cur.c+1][cur.idx], cur.cost + G[cur.r][cur.c+1])) {
            pq.emplace(cur.r, cur.c+1, cur.idx, dist[cur.r][cur.c+1][cur.idx]);
        }

        if (cur.idx < K) {
            if (chmn(dist[cur.r+A[cur.idx]][cur.c][cur.idx+1], cur.cost + G[cur.r+A[cur.idx]][cur.c])) {
                pq.emplace(cur.r+A[cur.idx], cur.c, cur.idx+1, dist[cur.r+A[cur.idx]][cur.c][cur.idx+1]);
            }
            if (chmn(dist[cur.r][cur.c+A[cur.idx]][cur.idx+1], cur.cost + G[cur.r][cur.c+A[cur.idx]])) {
                pq.emplace(cur.r, cur.c+A[cur.idx], cur.idx+1, dist[cur.r][cur.c+A[cur.idx]][cur.idx+1]);
            }
        }
    }

    ll ans = dist[N-1][M-1][0];
    for (int i=0; i<=K; ++i) {
        chmn(ans, dist[N-1][M-1][i]);
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
