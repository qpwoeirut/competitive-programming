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
const int MN = 200001;

ll N, M, K;
//int A[MN];
//int G[MN][MN];
//set<int> adj[MN];
ll before[MN], after[MN];
ll c0[MN], c1[MN];
void solve(int testcase) {
    cin >> N >> K;
    string s, t;
    cin >> s;
    cin >> t;

    for (int i=0; i<K; i++) {
        before[0] = 0;
        after[N-1] = 0;
        for (int j=N-1; j>0; j--) {
            after[j-1] = after[j];
            if (s[j] == t[1]) {
                ++after[j-1];
            }    
        }
        for (int j=0; j<N-1; j++) {
            before[j+1] = before[j];
            if (s[j] == t[0]) {
                ++before[j+1];
            }
        }

        for (int j=0; j<N; j++) {
            c0[j] = after[j];
            if (s[j] == t[1]) {
                --c0[j];
                c0[j] -= before[j];
            } else if (s[j] == t[0]) {
                c0[j] = 0;
            }
            c1[j] = before[j];
            if (s[j] == t[0]) {
                --c1[j];
                c1[j] -= after[j];
            } else if (s[j] == t[1]) {
                c1[j] = 0;
            }
        }

        int idx0 = max_element(c0, c0+N) - c0;
        int idx1 = max_element(c1, c1+N) - c1;
        for (int j=N-1; j>=0; j--) {
            if (c1[j] == c1[idx1]) {
                idx1 = j;
                break;
            }
        }

        debug(idx0);debug(c0[idx0]);
        debug(idx1);debug(c1[idx1]);
        if (c0[idx0] < 0 && c1[idx1] < 0) {
            break;
        }
        if (c0[idx0] >= c1[idx1]) {
            s[idx0] = t[0];
        } else {
            s[idx1] = t[1];
        }
        debug1(before, N);debug1(after,N);
        debug1(c0, N);debug1(c1, N);
        debug(s);
    }

    ll ans = 0;
    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            if (s[i] == t[0] && s[j] == t[1]) {
                ++ans;
            }
        }
    }
    cout << ans << endl;
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
/*
8 2
aaaccaba
*/
