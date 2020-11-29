//crash.cpp created at 11/21/20 13:12:27

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

template <class T> bool chmn(T& a, const T& b) {return ((a>b) ? ((a=b) || true) : false);}
template <class T> bool chmx(T& a, const T& b) {return ((a<b) ? ((a=b) || true) : false);}

void setIO(const string& filename = "crash") {
    cin.tie(0)->sync_with_stdio(0);
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353 //1e9+9 //1e9+21 // 1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;

ll N, M, K;
pll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

#define px first
#define py second

struct Item {
    int x, y;
    int dist;

    Item(const int _x, const int _y, const int d) {
        x = _x;
        y = _y;
        dist = d;
    }
};

vector<int> obsx[MN], obsy[MN];
void solve(int testcase) {
    cin >> N;
    int sx, sy, fx, fy;
    cin >> sx >> sy >> fx >> fy;

    vector<int> xpts, ypts;    
    A[0] = pll(sx, sy);
    for (int i=1; i<=N; ++i) {
        cin >> A[i].px >> A[i].py;
    }
    A[N+1] = pll(fx, fy);
    N += 2;
    for (int i=0; i<N; ++i) {
        xpts.push_back(A[i].px - 1);
        xpts.push_back(A[i].px);
        xpts.push_back(A[i].px + 1);
        ypts.push_back(A[i].py - 1);
        ypts.push_back(A[i].py);
        ypts.push_back(A[i].py + 1);
    }
    sort(all(xpts));
    sort(all(ypts));
    xpts.resize(unique(all(xpts)) - xpts.begin());
    ypts.resize(unique(all(ypts)) - ypts.begin());
    for (int i=0; i<N; ++i) {
        A[i].px = lower_bound(all(xpts), A[i].px) - xpts.begin();
        A[i].py = lower_bound(all(ypts), A[i].py) - ypts.begin();

        obsx[A[i].px].push_back(A[i].py);
        obsy[A[i].py].push_back(A[i].px);
    }
    for (int i=0; i<MN; ++i) {
        if (obsx[i].size()) sort(all(obsx[i]));
        if (obsy[i].size()) sort(all(obsy[i]));
    }
    debug1(A, N);
    debug1(obsx, N*3);
    debug1(obsy, N*3);

    set<pii> seen;
    seen.insert(A[0]);
    queue<Item> q;
    q.emplace(A[0].px, A[0].py, 0);
    
    bool first = true;
    while (q.size() > 0) {
        const Item cur = q.front(); q.pop();
        debug(cur.x, cur.y, cur.dist);

        if (cur.x == A[N-1].px && cur.y == A[N-1].py) {
            cout << cur.dist << endl;
            return;
        }

        const int xi = upper_bound(all(obsy[cur.y]), cur.x) - obsy[cur.y].begin();
        const int yi = upper_bound(all(obsx[cur.x]), cur.y) - obsx[cur.x].begin();

        if (first < xi) {
            const int nx = obsy[cur.y][xi-1-first] + 1, ny = cur.y;
            if (nx - 1 == A[N-1].px && ny == A[N-1].py) {
                cout << cur.dist << endl;
                return;
            }
            if (seen.emplace(nx, ny).SE == true) {
                q.emplace(nx, ny, cur.dist + 1);
            }
        }
        if (xi < obsy[cur.y].size()) {
            const int nx = obsy[cur.y][xi] - 1, ny = cur.y;
            if (nx + 1 == A[N-1].px && ny == A[N-1].py) {
                cout << cur.dist << endl;
                return;
            }
            if (seen.emplace(nx, ny).SE == true) {
                q.emplace(nx, ny, cur.dist + 1);
            }
        }
        if (first < yi) {
            const int nx = cur.x, ny = obsx[cur.x][yi-1-first] + 1;
            if (nx == A[N-1].px && ny - 1 == A[N-1].py) {
                cout << cur.dist << endl;
                return;
            }
            if (seen.emplace(nx, ny).SE == true) {
                q.emplace(nx, ny, cur.dist + 1);
            }
        }
        if (yi < obsx[cur.x].size()) {
            const int nx = cur.x, ny = obsx[cur.x][yi] - 1;
            if (nx == A[N-1].px && ny + 1 == A[N-1].py) {
                cout << cur.dist << endl;
                return;
            }
            if (seen.emplace(nx, ny).SE == true) {
                q.emplace(nx, ny, cur.dist + 1);
            }
        }
        first = false;
    }
    cout << -1 << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
