//1476e.cpp created at 01/28/21 22:49:16

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
const int MN = 101001;
const ll INF = 2e18 + 1;
const int WILD = 1;

ll N, M, K, Q;
ll A[MN];
pll B[MN];
//ll G[MN][MN];
set<ll> adj[MN];

const int SHF = 5;

ll S[4];
ll pack() {
    ll ret = 0;
    for (int i=0; i<K; ++i) {
        ret <<= SHF;
        ret |= S[i];
    }
    return ret;
}
void unpack(ll ret) {
    for (int i=K-1; i>=0; --i) {
        S[i] = ret & ((1LL << SHF) - 1);
        ret >>= SHF;
    }
}

mll pats;
bool gen_matches(const int idx) {
    bool ok = false;
    for (int i=0; i<(1 << K); ++i) {
        unpack(B[idx].FI);
        for (int j=0; j<K; ++j) {
            if ((i >> j) & 1) {
                S[j] = WILD;
            }
        }

        const ll pat = pack();
        if (pat == A[B[idx].SE]) {
            ok = true;
            continue;
        }
        auto it = pats.find(pat);
        if (it != pats.end()) {
            adj[pats[A[B[idx].SE]]].insert(it->SE);
        }
    }
    return ok;
}

ll ans[MN];
int deg[MN];
void solve(int testcase) {
    cin >> N >> M >> K;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<K; ++j) {
            char c;
            cin >> c;
            S[j] = c - '_' + 1;
        }
        A[i] = pack();
        assert(pats.count(A[i]) == 0);
        pats[A[i]] = i;
    }

    for (int i=0; i<M; ++i) {
        for (int j=0; j<K; ++j) {
            char c;
            cin >> c;
            S[j] = c - '_' + 1;
        }
        int x;
        cin >> x;
        --x;
        B[i] = pll(pack(), x);
    }
    for (int i=0; i<M; ++i) {
        if (!gen_matches(i)) {
            cout << "NO\n";
            return;
        }
    }

    fill(ans, ans+M, -1);
    for (int i=0; i<N; ++i) {
        for (const int v: adj[i]) ++deg[v];
    }
    queue<int> q;
    for (int i=0; i<N; ++i) {
        if (deg[i] == 0) q.push(i);
    }

    int idx = 0;
    while (q.size() > 0) {
        const int cur = q.front(); q.pop();
        ans[idx++] = cur + 1;

        for (const int v: adj[cur]) {
            if (--deg[v] == 0) q.push(v);
        }
    }

    if (idx < N) {
        cout << "NO\n";
        return;
    }
    

    cout << "YES\n";
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        solve(t);
    }
    
    return 0;
}
