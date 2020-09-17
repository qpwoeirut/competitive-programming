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
const int MN = -1; //200001;

ll N, M, K;
//int A[MN];
//int G[MN][MN];
//set<int> adj[MN];

void solve(int t) {
    cin >> N;

    ll total = 0;
    ll dbl = 0;

    set<pll> cur;
    cur.INS(pll(0, 0));

    set<pll>::iterator it=cur.begin();

    ll below = 0, light = 0;
    for (int i=0; i<N; i++) {
        ll type, val;
        cin >> type >> val;

        if (val < 0) {
            val = -val;
            if (type == 0) {
                if (it->FI <= val) {
                    assert(it != cur.begin());
                    dbl += it->FI - val;
                    if (it->SE == 1) {
                        --below;
                    }
                    --it;
                }
            } else {
                --light;
                if (val <= it->FI) {
                    --below;
                    assert(it != cur.end());
                    ++it;
                    if (it->SE == 1) ++below;
                    assert(it != cur.end());
                    dbl -= it->FI;
                } else {
                    dbl -= val;
                }
            }
            total -= val;
            cur.erase(pll(val, type));
        } else {
            total += val;
            cur.INS(pll(val, type));
            if (type == 0) {
                if (val > it->FI) {
                    ++it;
                    assert(it != cur.end());
                    if (it->SE == 1) ++below;
                    dbl += val - it->FI;
                }
            } else {
                ++light;
                if (val < it->FI) {
                    assert(it != cur.begin());
                    dbl += it->FI;
                    if (it->SE == 1) {
                        --below;
                    }
                    --it;
                    ++below;
                } else {
                    dbl += val;
                }
            }
        }    
        ll ans = total + dbl;
        if (below == 0 && light > 0) {
            set<pll>::iterator it2 = it;
            ++it2;
            assert(it2 != cur.end());
            ans -= it2->FI;
            ans += it->FI;
        }
        //debug(cur);debug(*it);debug(total);debug(dbl);debug(light);debug(below);
        cout << ans << endl;
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}


/*
3
1 4
0 5
0 -5

5
1 10
1 12
0 17
1 9
0 -17

*/
