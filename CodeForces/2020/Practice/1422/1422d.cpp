//1422d.cpp created at 10/09/20 15:37:55

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

template <class T> bool chmn(T& a, const T& b) {return (a>b) ? a=b, 1 : 0;}
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

struct Point {
    int r, c;
    int idx;
};

inline const bool cmp_r(const Point& a, const Point& b) {
    if (a.r == b.r) return a.c < b.c;
    return a.r < b.r;
}
inline const bool cmp_c(const Point& a, const Point& b) {
    if (a.c == b.c) return a.r < b.r;
    return a.c < b.c;
}

ll N, M, K;
Point A[MN];
//ll G[MN][MN];
set<pll> adj[MN];
ll dist[MN];

void solve(int testcase) {
    cin >> N >> M;

    Point start, finish;
    cin >> start.c >> start.r >> finish.c >> finish.r;

    for (int i=0; i<M; ++i) {
        cin >> A[i].c >> A[i].r;
        A[i].idx = i;
    }

    sort(A, A+M, cmp_r);
    for (int i=1; i<M; ++i) {
        adj[A[i].idx].insert(pll(A[i-1].idx, A[i].r - A[i-1].r));
        adj[A[i-1].idx].insert(pll(A[i].idx, A[i].r - A[i-1].r));
    }
    sort(A, A+M, cmp_c);
    for (int i=1; i<M; ++i) {
        adj[A[i].idx].insert(pll(A[i-1].idx, A[i].c - A[i-1].c));
        adj[A[i-1].idx].insert(pll(A[i].idx, A[i].c - A[i-1].c));
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for (int i=0; i<M; ++i) {
        dist[A[i].idx] = min(abs(start.r - A[i].r), abs(start.c - A[i].c));
        pq.push(pll(dist[A[i].idx], A[i].idx));
    }
    debug1(dist, M);

    while (pq.size() > 0) {
        pll cur = pq.top(); pq.pop();

        if (dist[cur.SE] < cur.FI) {
            continue;
        }

        for (auto it=adj[cur.SE].begin(); it!=adj[cur.SE].end(); ++it) {
            if (chmn(dist[it->FI], it->SE + cur.FI)) {
                pq.push(pll(dist[it->FI], it->FI));
            }
        }
    }
    debug1(dist, M);

    ll ans = abs(start.r - finish.r) + abs(start.c - finish.c);
    for (int i=0; i<M; ++i) {
        chmn(ans, dist[A[i].idx] + abs(A[i].r - finish.r) + abs(A[i].c - finish.c));
    }

    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
