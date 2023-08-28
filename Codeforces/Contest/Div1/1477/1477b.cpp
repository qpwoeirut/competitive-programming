//1477b.cpp created at 01/27/21 23:46:09

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
const int MN = 1001001;
const ll INF = 2e18 + 1;

struct Node {
    int lo, hi;
    ll zero, one;
    int lazy;
    int mark;
};

ll N, M, K, Q;
ll PN;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

string S, T;
Node tree[MN << 2];
void build() {
    for (int i=0; i<PN; ++i) {
        tree[PN+i].lo = i;
        tree[PN+i].hi = i+1;
        tree[PN+i].zero = i < N ? S[i] == '0' : 0;
        tree[PN+i].one = i < N ? S[i] == '1' : 0;
    }
    for (int i=PN-1; i>0; --i) {
        tree[i].lo = tree[i << 1].lo;
        tree[i].hi = tree[(i << 1) + 1].hi;
        tree[i].zero = tree[i << 1].zero + tree[(i << 1) + 1].zero;
        tree[i].one = tree[i << 1].one + tree[(i << 1) + 1].one;
    }
    for (int i=0; i<PN+PN; ++i) {
        tree[i].lazy = -1;
    }
}

void prop(const int node) {
    if (tree[node].lazy == -1) return;

    if (tree[node].lazy == 0) {
        tree[node << 1].zero = tree[node << 1].hi - tree[node << 1].lo;
        tree[node << 1].one = 0;
        tree[node << 1].lazy = 0;

        tree[(node << 1) + 1].zero = tree[(node << 1) + 1].hi - tree[(node << 1) + 1].lo;
        tree[(node << 1) + 1].one = 0;
        tree[(node << 1) + 1].lazy = 0;
    } else {
        tree[node << 1].zero = 0;
        tree[node << 1].one = tree[node << 1].hi - tree[node << 1].lo;
        tree[node << 1].lazy = 1;

        tree[(node << 1) + 1].zero = 0;
        tree[(node << 1) + 1].one = tree[(node << 1) + 1].hi - tree[(node << 1) + 1].lo;
        tree[(node << 1) + 1].lazy = 1;
    }
    tree[node].lazy = -1;
}

void update(const int node, const int lo, const int hi, const int val) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        if (val == 0) {
            tree[node].zero = tree[node].hi - tree[node].lo;
            tree[node].one = 0;
            tree[node].lazy = 0;
        } else {
            tree[node].zero = 0;
            tree[node].one = tree[node].hi - tree[node].lo;
            tree[node].lazy = 1;
        }
        return;
    }

    prop(node);

    update(node << 1, lo, hi, val);
    update((node << 1) + 1, lo, hi, val);
    tree[node].zero = tree[node << 1].zero + tree[(node << 1) + 1].zero;
    tree[node].one = tree[node << 1].one + tree[(node << 1) + 1].one;
}

ll query_zero(const int node, const int lo, const int hi) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return 0;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        return tree[node].zero;
    }

    prop(node);
    return query_zero(node << 1, lo, hi) + query_zero((node << 1) + 1, lo, hi);
}

ll query_one(const int node, const int lo, const int hi) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return 0;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        return tree[node].one;
    }

    prop(node);
    return query_one(node << 1, lo, hi) + query_one((node << 1) + 1, lo, hi);
}

pll query[MN];
void solve(int testcase) {
    cin >> N >> Q;
    cin >> T >> S;

    PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;

    for (int i=0; i<Q; ++i) {
        cin >> query[i].FI >> query[i].SE;
        --query[i].FI;
    }
    reverse(query, query + Q);

    build();
    for (int i=0; i<Q; ++i) {
        const ll zero = query_zero(1, query[i].FI, query[i].SE);
        const ll one = query_one(1, query[i].FI, query[i].SE);

        const int len = query[i].SE - query[i].FI;
        debug(i, zero, one, query[i], len, zero < (len+1) / 2);
        assert(zero + one == len);

        if (zero >= (len+1)/2 && one >= (len+1)/2) {
            cout << "no\n";
            return;
        }
        update(1, query[i].FI, query[i].SE, zero < (len+1)/2);
    }

    for (int i=0; i<N; ++i) {
        debug(i, T[i], query_zero(1, i, i+1), query_one(1, i, i+1));
        if (T[i] == '0' && query_zero(1, i, i+1) != 1) {
            cout << "No\n";
            return;
        }
        if (T[i] == '1' && query_one(1, i, i+1) != 1) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
