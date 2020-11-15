//rugby.cpp created at 11/14/20 20:03:03

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
#define sz(obj) ((long long)(obj.size()))
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
pll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

#define x first
#define y second

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
    }
    sort(A, A+N, cmps<ll,ll>());

    mll above, below;
    ll ad = 0, bd = 0;
    ll act = 0, bct = 0;
    for (int i=0; i<N; ++i) {
        if (A[i].y != A[0].y) {
            ++below[A[i].y];
            bd += A[i].y - A[0].y;
            ++bct;
        } else {
            ++above[A[i].y];
            ++act;
        }
    }

    ll yd = bd;
    debug(ad, bd);
    if (below.empty()) yd = 0;
    ll prev = A[0].y;
    while (below.size() > 0) {
        pll cur = *below.begin();
        ll move = cur.FI - prev;

        ad += move * act;
        bd -= move * bct;

        act += below.begin()->SE;
        bct -= below.begin()->SE;
        below.erase(below.begin());
        above[cur.FI] = cur.SE;

        chmn(yd, ad + bd);

        prev = cur.FI;
        debug(ad, bd);
    }

    debug(yd);

    sort(A, A+N);
    multiset<ll, greater<ll>> neg;
    multiset<ll> pos;
    ll cur = 0;
    for (ll i=0; i<N; ++i) {
        ll dist = (ll)-2e9 - A[i].x + i;
        if (dist >= 0) {
            pos.insert(dist);
        } else {
            neg.insert(dist);
        }
        cur += abs(dist);
    }
    debug(pos, neg);
    ll xd = cur;

    ll shf = 0;
    while (neg.size()) {
        ll diff = shf - *neg.begin();
        cur -= diff * sz(neg);
        cur += diff * sz(pos);

        debug(shf, diff, cur, *neg.begin());

        shf = *neg.begin();
        pos.insert(*neg.begin());
        neg.erase(neg.begin());

        chmn(xd, cur);
    }
    debug(xd, yd);

    cout << "Case #" << testcase << ": " << xd + yd << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
5
2
1 1
4 4
3
1 1
1 2
1 3

3
1 1
2 1
3 1

3
-1000000000 -1000000000
-1000000000 -1000000000
-1000000000 -1000000000

3
1 1
1 1
0 0
*/
