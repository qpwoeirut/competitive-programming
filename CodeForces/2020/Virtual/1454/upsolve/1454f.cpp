//1454f.cpp created at 12/10/20 11:27:27

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
const int MN = 201001;
const int LG = 20;

ll N, M, K;
ll A[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

ll larger[MN];
ll mx[MN];
ll lg_val[MN];
ll sparse[LG][MN];

vector<ll> pos[MN];
void solve(int testcase) {
    cin >> N;
    vector<int> nums;
    fill(pos, pos+N+1, vector<ll>());
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        nums.push_back(A[i]);
    }
    sort(all(nums));
    nums.resize(unique(all(nums)) - nums.begin());
    for (int i=0; i<N; ++i) {
        A[i] = lower_bound(all(nums), A[i]) - nums.begin();
        ++A[i];
        pos[A[i]].push_back(i);
    }
    debug1(A, N);

    fill(larger, larger+N+1, 0);
    for (int i=0; i<N; ++i) {
        larger[A[i]-1] = i;
    }
    for (int i=N-1; i>=0; --i) {
        chmx(larger[i], larger[i+1]);
    }

    mx[N] = 0;
    for (int i=N-1; i>=0; --i) {
        mx[i] = max(A[i], mx[i+1]);
    }

    for (int i=0; i<N; ++i) {
        sparse[0][i] = A[i];
    }
    for (int i=1; i<LG; ++i) {
        for (int j=0; j + (1 << i) <= N; ++j) {
            sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j + (1 << (i-1))]);
        }
    }

    ll x = A[0];
    for (int i=0; i<N; ++i) {
        chmx(x, A[i]);
        auto next_pos = upper_bound(all(pos[x]), i);
        if (next_pos == pos[x].end()) continue;

        int L = i+1, R = max(*next_pos, larger[x]) + 1;
        int lg = lg_val[R - L];
        int middle = min(sparse[lg][L], sparse[lg][R - (1 << lg)]);
        debug(L, R, x, middle, mx[R]);
        if (x == middle && middle == mx[R]) {
            cout << "YES\n";
            cout << L << ' ' << R-L << ' ' << N-R << '\n';
            return;
        }
    }
    cout << "NO\n";

}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;

    lg_val[1] = 0;
    for (int i=2; i<MN; ++i) {
        lg_val[i] = lg_val[i >> 1] + 1;
    }
    
    for (int t=1; t<=T; t++) solve(t);
    
    return 0;
}
