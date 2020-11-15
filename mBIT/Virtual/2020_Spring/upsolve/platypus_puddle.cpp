//platypus_puddle.cpp created at 11/11/20 14:51:22

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
const int MN = 1005;

ll N, M, K;
//ll A[MN];
ll G[MN][MN], ans[MN][MN];
//set<ll> adj[MN];

struct Item {
    int r, c;
    ll val;

    Item(int _r, int _c, int _val) {
        r = _r;
        c = _c;
        val = _val;
    }

    inline const bool operator<(const Item& other) const {
        return val > other.val;
    }
};

void solve(int testcase) {
    cin >> N;
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            cin >> G[i][j];
            ans[i][j] = INIT;
        }
    }

    priority_queue<Item> pq;
    for (int i=0; i<=N+1; ++i) {
        pq.emplace(0, i, 0);
        pq.emplace(N+1, i, 0);
        pq.emplace(i, 0, 0);
        pq.emplace(i, N+1, 0);
    }

    while (pq.size() > 0) {
        Item cur = pq.top(); pq.pop();

        for (int i=0; i<4; ++i) {
            int nr = cur.r + chr[i];
            int nc = cur.c + chc[i];
            if (nr < 0 || nr > N+1 || nc < 0 || nc > N+1) continue;
            int nv = max(G[nr][nc], cur.val);
            if (ans[nr][nc] == INIT) {
                ans[nr][nc] = nv;
                pq.emplace(nr, nc, nv);
            }
        }
    }

    ll total = 0;
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            total += ans[i][j] - G[i][j];
        }
    }

    cout << total << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
5
4 5 4 2 2
3 4 1 1 2
3 2 3 1 2
2 3 1 2 2
2 1 2 1 2
*/
