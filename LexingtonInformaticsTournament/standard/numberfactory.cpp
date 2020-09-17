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
const int MN = 100001;

ll N, M, K;
ll A[MN];
char B[MN];
pll bval[320];
//int G[MN][MN];
//set<int> adj[MN];
const int BL = 317;

void calc(int i) {
    bval[i] = pll(0, 1);
    for (int j=i*BL; j<(i+1)*BL; j++) {
        assert(j < N);
        if (B[j] == '+') {
            bval[i].FI += A[j];
        } else if (B[j] == '-') {
            bval[i].FI -= A[j];
        } else if (B[j] == '*') {
            bval[i].FI *= A[j];
            bval[i].SE *= A[j];
        } else assert(false);
        bval[i].FI %= MOD;
        bval[i].SE %= MOD;
    }
}

void solve(int t) {
    cin >> N >> M;
    
    for (int i=0; i<N; i++) {
        cin >> B[i] >> A[i];
    }
    
    while ((N % BL) > 0) {
        B[N] = '+';
        A[N] = 0;
        ++N;
    }
    assert(N % BL == 0);
    const int BN = N / BL;

    for (int i=0; i<BN; i++) {
        calc(i);
    }
    //debug1(bval, BN);

    for (int i=0; i<M; i++) {
        char type;
        cin >> type;

        if (type == 'q') {
            ll x, y;
            cin >> x >> y;
            int cur = 0;
            int bidx = 0;
            for (;cur+BL<=y; cur += BL) {
                assert(bidx < BN);
                x *= bval[bidx].SE;
                x += bval[bidx].FI;
                ++bidx;
                x %= MOD;
            }
            for (; cur<y; cur++) {
                if (B[cur] == '+') {
                    x += A[cur];
                } else if (B[cur] == '-') {
                    x -= A[cur];
                } else if (B[cur] == '*') {
                    x *= A[cur];
                } else assert(false);
                x %= MOD;
                //debug(cur);debug(x);
            }
            x = (x + MOD) % MOD;
            cout << x << endl;
        } else if (type == 'c') {
            int m, n;
            char o;
            cin >> m >> n >> o;

            --m;
            A[m] = n;
            B[m] = o;

            int bidx = m / BL;
            calc(bidx);
        } else assert(false);
    }
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
