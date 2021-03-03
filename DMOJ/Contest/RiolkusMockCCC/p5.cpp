//p5.cpp created at 02/15/21 12:02:37

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
const int MN = 1 << 21;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

struct Node {
    ll sum;
    ll val;
    int ct;
    ll lo, hi;
};

Node tree[MN << 1];

void build() {
    const int PN = MN >> 1;
    for (int i=0; i<PN; ++i) {
        tree[PN+i].sum = A[i] ? i : 0;
        tree[PN+i].ct = A[i];
        tree[PN+i].val = i;
        tree[PN+i].lo = i;
        tree[PN+i].hi = i+1;
    }
    for (int i=PN-1; i>0; --i) {
        tree[i].sum = tree[i << 1].sum ^ tree[(i << 1) + 1].sum;
        tree[i].val = 0; //idk
        tree[i].ct = 0;
        tree[i].lo = tree[i << 1].lo;
        tree[i].hi = tree[(i << 1) + 1].hi;
    }
}

void update(const int node, const int lo, const int hi) {
    if (hi <= tree[node].lo || tree[node].hi <= lo) return;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        tree[node].sum ^= tree[node].val;
        tree[node].ct = tree[node].sum > 0;
        return;
    }

    update(node << 1, lo, hi);
    update((node << 1) + 1, lo, hi);
    tree[node].sum = tree[node << 1].sum ^ tree[(node << 1) + 1].sum;
    tree[node].ct = tree[node << 1].ct ^ tree[(node << 1) + 1].ct;
}

int query(const int node, const int lo, const int hi) {
    if (hi <= tree[node].lo || tree[node].hi <= lo) return 0;
    if (lo <= tree[node].lo && tree[node].hi <= hi) return tree[node].sum;

    return query(node << 1, lo, hi) ^ query((node << 1) + 1, lo, hi);
}

int qct(const int node, const int lo, const int hi) {

    if (hi <= tree[node].lo || tree[node].hi <= lo) return 0;
    if (lo <= tree[node].lo && tree[node].hi <= hi) return tree[node].ct;

    return qct(node << 1, lo, hi) + qct((node << 1) + 1, lo, hi);
}

void brute() {
    for (int i=0; i<Q; ++i) {
        int type, L, R, x;
        cin >> type;
        if (type == 1) {
            cin >> x;
            A[x] ^= 1;
        } else if (type == 2) {
            cin >> L >> R >> x;
            queue<int> q;
            for (int j=L; j<=R; ++j) {
                if (A[j]) {
                    q.push(j ^ x);
                    A[j] = 0;
                }
            }
            while (q.size() > 0) {
                const int cur = q.front(); q.pop();
                A[cur] ^= 1;
            }
        } else if (type == 3) {
            cin >> L >> R;
            int ret = 0;
            for (int j=L; j<=R; ++j) {
                ret ^= j * A[j];
            }
            cout << ret << '\n';
        } else assert(false);
    }
}

void solve(int testcase) {
    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;
        A[x] ^= 1;
    }

    if (N <= 2000 && Q <= 2000) {
        brute();
        return;
    }

    build();
    int m = 0;
    for (int i=0; i<Q; ++i) {
        int type, L, R, x;
        cin >> type;
        if (type == 1) {
            cin >> x;
            x ^= m;
            update(1, x, x+1);
        } else if (type == 2) {
            cin >> L >> R >> x;
            m ^= x;
        } else if (type == 3) {
            cin >> L >> R;
            L ^= m;
            R ^= m;
            if (L > R) swap(L, R);
            ++R;
            int a = query(1, L, R);
            int b = qct(1, L, R);
            if (b ^ 1) a ^= m;
            cout << a << '\n';
        } else assert(false);
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
