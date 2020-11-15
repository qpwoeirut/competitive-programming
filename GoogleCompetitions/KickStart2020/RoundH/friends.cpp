//friends.cpp created at 11/14/20 21:41:09

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

void setIO(const string& filename = "") {
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

ll N, M, K, Q;
string A[MN];
//ll G[MN][MN];
set<ll> adj[256];

bool dist[MN];
int ans[MN];
void solve(int testcase) {
    cin >> N >> Q;

    for (int i='A'; i<='Z'; ++i) {
        adj[i].clear();
    }
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        for (int j=0; j<A[i].size(); ++j) {
            adj[A[i][j]].insert(i);
        }
    }

    for (int i=0; i<Q; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        fill(dist, dist+N, false);

        queue<pll> q;
        q.emplace(u, 1);
        dist[u] = true;
        ans[i] = -1;

        bool stop = false;
        while (q.size() > 0) {
            pll cur = q.front(); q.pop();
            debug(cur);
            if (cur.FI == v) {
                ans[i] = cur.SE;
                break;
            }
            for (char c: A[cur.FI]) {
                for (auto it=adj[c].begin(); it!=adj[c].end(); ++it) {
                    if (*it == v) {
                        ans[i] = cur.SE + 1;
                        stop = true;
                        break;
                    }
                    if (!dist[*it]) {
                        dist[*it] = true;
                        q.emplace(*it, cur.SE + 1);
                    }
                }
                if (stop) break;
            }
            if (stop) break;
        }
    }

    cout << "Case #" << testcase << ":";
    for (int i=0; i<Q; ++i) {
        cout << ' ' << ans[i];
    }
    cout << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
