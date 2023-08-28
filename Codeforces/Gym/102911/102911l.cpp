//102911l.cpp created at 01/01/21 20:05:29

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
const int MN = 1001;

ll N, M, K;
ll A[MN];

char ans[MN][MN];

void base(const int off_r, const int off_c, const int br, const int bc) {
    set<char> neighbor;
    for (int r=0; r<2; ++r) {
        for (int c=0; c<2; ++c) {
            for (int d=0; d<4; ++d) {
                const int nr = r + chr[d] + off_r;
                const int nc = c + chc[d] + off_c;
                neighbor.insert(ans[nr][nc]);
            }
        }
    }
    char cur = 'A';
    for (; cur<='Z'; ++cur) {
        if (neighbor.count(cur) == 0) break;
    }
    assert(cur <= 'Z');
    for (int r=0; r<2; ++r) {
        for (int c=0; c<2; ++c) {
            if (off_r + r == br && off_c + c == bc) continue;
            ans[off_r + r][off_c + c] = cur;
        }
    }
}

void solve(const int off_r, const int off_c, const int n, const int br, const int bc) {
    debug(off_r, off_c, n, br, bc);
    if (n == 1) {
        base(off_r, off_c, br, bc);
        return;
    }

    const int mid_r = off_r + (1 << (n-1)) - 1;
    const int mid_c = off_c + (1 << (n-1)) - 1;
    base(mid_r, mid_c, br, bc);
    if (br <= mid_r) {
        if (bc <= mid_c) {
            solve(off_r, off_c, n-1, br, bc);
            solve(off_r, mid_c + 1, n-1, mid_r, mid_c + 1);
        } else {
            solve(off_r, off_c, n-1, mid_r, mid_c);
            solve(off_r, mid_c + 1, n-1, br, bc);
        }
        solve(mid_r + 1, off_c, n-1, mid_r + 1, mid_c);
        solve(mid_r + 1, mid_c + 1, n-1, mid_r + 1, mid_c + 1);
    } else {
        if (bc <= mid_c) {
            solve(mid_r + 1, off_c, n-1, br, bc);
            solve(mid_r + 1, mid_c + 1, n-1, mid_r + 1, mid_c + 1);
        } else {
            solve(mid_r + 1, off_c, n-1, mid_r + 1, mid_c);
            solve(mid_r + 1, mid_c + 1, n-1, br, bc);
        }
        solve(off_r, off_c, n-1, mid_r, mid_c);
        solve(off_r, mid_c + 1, n-1, mid_r, mid_c + 1);
    }
}

int main() {
    setIO();
    
    ll br, bc;
    cin >> N >> br >> bc;
    solve(1, 1, N, br, bc);
    ans[br][bc] = '#';

    cout << "YES\n";
    for (int i=1; i<=(1 << N); ++i) {
        for (int j=1; j<=(1 << N); ++j) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}
