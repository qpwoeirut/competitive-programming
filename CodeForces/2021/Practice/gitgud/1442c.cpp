//1442c.cpp created at 01/09/21 22:09:59

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

const ll MOD = 998244353; //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 201001;
const int LG = 20;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
set<ll> adj[MN], radj[MN];

struct Item {
    ll node;
    ll dst, revs;

    Item(const ll _node, const ll _dst, const ll _revs) {
        node = _node;
        dst = _dst;
        revs = _revs;
    }
    inline const bool operator<(const Item& o) const {
        if (revs == o.revs) {
            if (dst == o.dst) return node > o.node;
            return dst > o.dst;
        }
        return revs > o.revs;
    }
    void print() const {
        cerr << "Item node,revs,dst: " << node << ' ' <<revs << ' ' << dst << endl;
    }
};

ll dist[2][MN];	
ll p2[MN];
pll V[2][MN];	
 	
void solve(int testcase) {	
    cin >> N >> M;	
    for (int i=0; i<M; ++i) {	
        ll u, v;	
        cin >> u >> v;	
        --u; --v;	
        adj[u].insert(v);	
        radj[v].insert(u);	
    }	
    p2[0] = 1;	
    for (int i=1; i<MN; ++i) {	
        p2[i] = p2[i-1] << 1;	
        if (i >= 56) {	
            p2[i] %= MOD;	
        }	
    }	
 	
    priority_queue<pll, vector<pll>, greater<pll>> pq[2];	
    pq[0].emplace(0, 0);	
    fill(dist[0], dist[0] + N, INF);	
    dist[0][0] = 0;	
    ll ans = INF;	
 	
    for (int rev=0; rev<LG; ++rev) {	
        const int i = rev&1;	
        fill(dist[!i], dist[!i] + N, INF);	
        assert(pq[!i].empty());	
        while (pq[i].size() > 0) {	
            const pll cur = pq[i].top(); pq[i].pop();	
            debug(rev, cur);	
 	
            if (cur.SE == N-1) {	
                chmn(ans, cur.FI);	
                continue;	
            }	
 	
            if (i) {	
                for (const ll v: radj[cur.SE]) {	
                    if (chmn(dist[i][v], cur.FI + 1)) {	
                        pq[i].emplace(dist[i][v], v);	
                    }	
                }	
            } else {	
                for (const ll v: adj[cur.SE]) {	
                    if (chmn(dist[i][v], cur.FI + 1)) {	
                        pq[i].emplace(dist[i][v], v);	
                    }	
                }	
            }	
 	
            if (chmn(dist[!i][cur.SE], cur.FI + p2[rev])) {	
                pq[!i].emplace(dist[!i][cur.SE], cur.SE);	
            }	
        }	
    }	
 	
    if (ans != INF) {	
        cout << ans % MOD << endl;	
        return;	
    }

    fill(V[0], V[0]+N, pll(INF, INF));
    fill(V[1], V[1]+N, pll(INF, INF));
    priority_queue<Item> pq2;
    while (pq[LG & 1].size() > 0) {
        const pll cur = pq[LG & 1].top(); pq[LG & 1].pop();
        if (V[LG & 1][cur.SE].FI == LG) continue;
        const ll D = cur.FI - (p2[LG] - 1);
        if (chmn(V[LG & 1][cur.SE], pll(LG, D))) {
            debug(D, cur.SE);
            assert(0 <= D);
            assert(D < M);
            pq2.emplace(cur.SE, D, LG);
        }
    }

    while (pq2.size() > 0) {
        const Item cur = pq2.top(); pq2.pop();
        //cur.print();

        if (cur.node == N-1) {
            cout << (cur.dst + p2[cur.revs] - 1) % MOD << endl;
            return;
        }

        for (const ll v: adj[cur.node]) {
            const bool flip = cur.revs & 1;
            const ll new_revs = cur.revs + flip;
            if (chmn(V[new_revs & 1][v], pll(new_revs, cur.dst + 1))) {
                pq2.emplace(v, cur.dst + 1, new_revs);
            }
        }
        for (const ll v: radj[cur.node]) {
            const bool flip = !(cur.revs & 1);
            const ll new_revs = cur.revs + flip;
            if (chmn(V[new_revs & 1][v], pll(new_revs, cur.dst + 1))) {
                pq2.emplace(v, cur.dst + 1, new_revs);
            }
        }
    }

    assert(false);
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
/*
6 5
1 2
3 4
5 6
5 4
3 2

12 11
1 2
3 4
5 6
7 8
9 10
11 12
11 10
9 8
7 6
5 4
3 2
*/
