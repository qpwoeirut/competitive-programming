//304970a.cpp created at 11/25/20 07:16:41

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

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
set<ll> adj[MN];

vector<ll> del;
bool dfs(const int node, const int par) {
    debug(node, adj[node]);
    if (adj[node].size() == 1 && *adj[node].begin() == par) {
        if (A[node]) {
            del.push_back(node);
        }
        return A[node];
    }

    bool ok = A[node];
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (*it == par) continue;

        ok &= A[*it];
        dfs(*it, node);
    }
    if (ok) {
        del.push_back(node);
    }
    return ok;
}
void solve(int testcase) {
    cin >> N;
    ll root = -1;
    for (int i=0; i<N; ++i) {
        ll p;
        cin >> p >> A[i];
        if (p == -1) root = i;
        else {
            --p;
            adj[i].insert(p);
            adj[p].insert(i);
        }
    }
    debug(root);
    debug1(adj, N);
    dfs(root, -1);

    sort(all(del));
    if (del.empty()) {
        del.push_back(-2);
    }
    for (int i=0; i<del.size(); ++i) {
        if (i) cout << ' ';
        cout << del[i] + 1;
    }
    cout << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
