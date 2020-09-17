//1404c.cpp created at 09/05/20 23:36:22

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

ll N, M, K, Q;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

struct Query {
    int idx;
    int x, y;
};

inline const bool cmp_y(const Query& a, const Query& b) {
    return a.y < b.y;
}

ll BIT[MN];
void inc(int idx) {
    for (; idx<N; idx|=idx+1) BIT[idx]++;
}
ll sum(int idx) {
    ll ret = 0;
    for (; idx>0; idx&=idx-1) ret += BIT[idx-1];
    return ret;
}

Query query[MN];
int dep[MN];
int res[MN];
void solve(int testcase) {
    cin >> N >> Q;

    for (int i=0; i<N; i++) {
        cin >> A[i];
        if (A[i] > i+1) {
            A[i] = N+1;
        } else {
            A[i] = i+1 - A[i];
        }
    }
    debug1(A, N);

    vector<ll> rems;
    for (int i=0; i<N; i++) {
        if (A[i] <= sz(rems)) {
            if (A[i] == 0) {
                rems.PB(i);
            } else {
                rems.PB(rems[sz(rems) - A[i]]);
            }
            dep[i] = rems.back();
        } else {
            dep[i] = -1;
        }
    }

    sort(all(rems));

    for (int i=0; i<Q; i++) {
        cin >> query[i].x >> query[i].y;
        query[i].idx = i;
    }
    sort(query, query+Q, cmp_y);

    int y = 0;

    for (int i=0; i<Q; i++) {
        ll ans = sz(rems) - (upper_bound(all(rems), query[i].x) - rems.begin());
        while (y < query[i].y) {
            if (dep[N-y-1] != -1) {
                inc(dep[N-y-1]);
            }
            ++y;
        }
        ans -= sum(query[i].x + 1);
        res[query[i].idx] = ans;
    }

    for (int i=0; i<Q; i++) {
        cout << res[i] << endl;
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
