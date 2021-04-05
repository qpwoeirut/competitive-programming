//rabbit_house.cpp created at 03/20/21 21:14:23

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

#define pb push_back
#define ins insert

#define fi first
#define se second
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

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int INIT = 1001001001;
const int MN = 1001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN];// , B[MN];
ll G[MN][MN], V[MN][MN];
//set<ll> adj[MN];

struct Item {
    ll r, c;
    ll val;

    Item(const int _r, const int _c, const int _val) {
        r = _r;
        c = _c;
        val = _val;
    }
    inline const bool operator<(const Item& o) const {
        if (val == o.val) {
            if (r == o.r) return c > o.c;
            return r > o.r;
        }
        return val < o.val;
    }
};

void solve(int testcase) {
    cin >> N >> M;
    priority_queue<Item> pq;

    ll sum = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];

            sum += G[i][j];

            pq.emplace(i, j, G[i][j]);
            V[i][j] = G[i][j];
        }
    }

    while (pq.size() > 0) {
        const Item cur = pq.top(); pq.pop();
        if (cur.val < V[cur.r][cur.c]) continue;
        debug(cur.r, cur.c, cur.val);

        for (int i=0; i<4; ++i) {
            int nr = cur.r + chr[i];
            int nc = cur.c + chc[i];
            if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue;

            if (chmx(G[nr][nc], cur.val - 1)) {
                V[nr][nc] = G[nr][nc];
                pq.emplace(nr, nc, G[nr][nc]);
            }
        }
    }
    ll nsum = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            nsum += G[i][j];
        }
    }

    cout << "Case #" << testcase << ": " << nsum - sum << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
