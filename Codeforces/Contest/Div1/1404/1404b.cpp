//1404b.cpp created at 09/05/20 23:36:21

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

ll binpow(const ll& x, const ll& p, const ll& mod) {assert(mod>0);
	if (p == 0) return 1;
	if (p == 1) return x % mod;
	if (p & 1) return (binpow((x*x) % mod, p/2, mod) * x) % mod;
	return binpow((x*x) % mod, p/2, mod) % mod;
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
//ll A[MN];
//ll G[MN][MN];
set<ll> adj[MN];
ll A, B, DA, DB;
int in[MN];
bool V[MN];
int ct[MN];
void solve(int testcase) {
    cin >> N >> A >> B >> DA >> DB;
    --A;--B;

    fill(adj, adj+N, set<ll>());
    for (int i=0; i<N-1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].INS(v);
        adj[v].INS(u);
    }


    if (DA*2 >= DB) {
        cout << "Alice" << endl;
        return;
    }

    queue<pii> q;
    for (int i=0; i<N; i++) {
        in[i] = adj[i].size();
        V[i] = false;
        ct[i] = 0;
        if (adj[i].size() == 1) {
            q.push(pii(i, 0));
            V[i] = true;
        }
    }

    pii cur;
    while (q.size() > 0) {
        cur = q.front();
        q.pop();

        for (set<ll>::iterator it=adj[cur.FI].begin(); it!=adj[cur.FI].end(); it++) {
            if (V[*it]) continue;
            if (--in[*it] == 1) {
                q.push(pii(*it, cur.SE + 1));
            }
        }
        ct[cur.SE]++;
    }

    ll mxd = cur.SE;

    fill(V, V+N, false);
    q.push(pii(A, 0));
    while (q.size() > 0) {
        pii p = q.front();
        q.pop();

        for (set<ll>::iterator it=adj[p.FI].begin(); it!=adj[p.FI].end(); it++) {
            if (*it == B) {
                if (p.SE + 1 <= DA) {
                    cout << "Alice" << endl;
                    return;
                }
            }
            if (V[*it]) continue;
            V[*it] = true;
            q.push(pii(*it, p.SE + 1));
        }
    }

    if (ct[mxd] > 1) {
        ++mxd;
    }
    if (DA >= mxd) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
