//skyscraper.cpp created at 02/06/21 17:54:15

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
const int MN = 301001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

struct Node {
    int mx;
    bool lazy;
    int lo, hi;
};

Node tree[MN << 2];

void build() {
    ll PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;
    for (int i=0; i<PN; ++i) {
        tree[PN+i].lo = i;
        tree[PN+i].hi = i+1;
        tree[PN+i].mx = i<N ? A[i] : 0;
        tree[PN+i].lazy = false;
    }
    for (int i=PN-1; i>0; --i) {
        tree[i].lo = tree[i << 1].lo;
        tree[i].hi = tree[(i << 1) + 1].hi;
        tree[i].mx = max(tree[i << 1].mx, tree[(i << 1) + 1].mx);
        tree[i].lazy = false;
    }
}

void prop(const int node) {
    if (tree[node].lazy) {
        tree[node << 1].mx = tree[node].mx;
        tree[node << 1].lazy = true;
        tree[(node << 1) + 1].mx = tree[node].mx;
        tree[(node << 1) + 1].lazy = true;
        
        tree[node].lazy = false;
    }
}

void update(const int node, const int lo, const int hi, const int val) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        tree[node].mx = val;
        tree[node].lazy = true;
        return;
    }

    prop(node);

    update(node << 1, lo, hi, val);
    update((node << 1) + 1, lo, hi, val);
    tree[node].mx = max(tree[node << 1].mx, tree[(node << 1) + 1].mx);
}

int first_larger(int node, const int lo, const int val) {
    if (tree[node].mx <= val) return -1;
    if (tree[node].hi <= lo) return -1;
    if (lo <= tree[node].lo) {
        while (tree[node].lo + 1 < tree[node].hi) {
            prop(node);
            node <<= 1;
            if (tree[node].mx > val) {
                //pass
            } else {
                ++node;
            }
        }
        return tree[node].lo;
    }

    int left_side = first_larger(node << 1, lo, val);
    if (left_side != -1) return left_side;
    return first_larger((node << 1) + 1, lo, val);
}

int last_larger(int node, const int hi, const int val) {
    if (tree[node].mx <= val) return -1;
    if (hi <= tree[node].lo) return -1;
    if (tree[node].hi <= hi) {
        while (tree[node].lo + 1 < tree[node].hi) {
            prop(node);
            node <<= 1;
            if (tree[node + 1].mx > val) {
                ++node;
            } else {
                //pass
            }
        }

        return tree[node].lo;
    }

    int right_side = last_larger((node << 1) + 1, hi, val);
    if (right_side != -1) return right_side;
    return last_larger(node << 1, hi, val);
}

int height(int node, const int idx) {
    if (tree[node].hi <= idx || idx + 1 <= tree[node].lo) return -1;
    if (tree[node].lo == idx && idx + 1 == tree[node].hi) return tree[node].mx;

    prop(node);

    return max(height(node << 1, idx), height((node << 1) + 1, idx));
}

void solve(int testcase) {
    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    build();
    for (int i=0; i<Q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int idx;
            cin >> idx;
            --idx;
            const int h = height(1, idx);
            int lo = last_larger(1, idx, h);
            int hi = first_larger(1, idx, h);

            if (hi == -1) hi = N;
            cout << hi - lo - 1 << '\n';
        } else if (t == 2) {
            int idx, x;
            cin >> idx >> x;
            --idx;
            update(1, idx, idx+1, x);
        } else if (t == 3) {
            int lo, hi, x;
            cin >> lo >> hi >> x;
            --lo;
            update(1, lo, hi, x);
        }
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
/*
8 6
4 2 3 2 4 7 6 5
1 3
1 2
2 3 8
1 5
3 5 7 1
1 8
*/
