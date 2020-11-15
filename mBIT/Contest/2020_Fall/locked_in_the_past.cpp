//locked_in_the_past.cpp created at 11/14/20 11:07:04

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
ll A[MN], B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
ll dp[MN];

namespace Segtree{
  #define lson (way<<1)
  #define rson (way<<1|1)
  #define mid (l+r)/2

  struct Node{
    int val,id;
  }seg[MAXN<<2];

  inline void build(int way,int l, int r,int L, int R){
    if (l==r) {seg[way] = (Node){pos[L],L};return;}
    build(lson,l,mid,L,(L+R)/2);
    build(rson,mid+1,r,(L+R)/2+1,R);
    // seg[way] = min(seg[lson],seg[rson]);
    seg[way] = (seg[lson].val<seg[rson].val) ? seg[lson] : seg[rson];
  }

  inline Node query(int way, int l, int r, int qlow,int qhigh){

    if (qlow<=l && r<=qhigh) return seg[way];
    if (l>qhigh || r<qlow) return (Node){1e9,1e9};
    Node fi = query(lson,l,mid,qlow,qhigh),se = query(rson,mid+1,r,qlow,qhigh);
    // Write(fi.val),writeln(se.val);
    return fi.val<se.val ? fi : se;
  }
  #undef lson
  #undef rson
  #undef mid
};
using namespace Segtree;
inline int cost(int x, int y, int del, int ix, int iy){
  int pivot = query(1,1,n,ix,iy).id;
  assert(pivot!=0);
  int re = pos[pivot]-del;
  if (pivot-1>=x) re += cost(x,pivot-1,pos[pivot],ix,iy-(y-pivot+1));
  if (pivot+1<=y) re += cost(pivot+1,y,pos[pivot],ix+(pivot+1-x),iy);
  return re;
}

void solve(int testcase) {
    cin >> N >> K;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N; ++i) {
        B[i] = -(A[i] - K);
    }
    fill(dp, dp+N+1, INIT);

    dp[0] = 0;
    for (int i=1; i<=N; ++i) {
        for (int j=i+1; j<=N; ++j) {
            dp[j] = min(dp[j], dp[i] + min(cost(A, i-1, j), cost(B, i-1, j)));
        }
    }

    cout << dp[N] << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
