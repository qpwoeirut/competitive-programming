//1506g.cpp created at 04/01/21 11:38:00

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

#define pb push_back
#define ins insert

#define fi first
#define se second
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

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
string A[MN];// , B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];

vector<ll> pos[256];
void solve(int testcase) {
    string S;
    cin >> S;
    N = sz(S);

    fill(pos, pos+256, vector<ll>());
    for (int i=0; i<N; ++i) {
        pos[S[i]].pb(i);
    }
    
    set<ll> ans;
    //ans.ins(N);
    for (char c='a'; c <= 'z'; ++c) {
        if (pos[c].empty()) continue;
        //auto it = UB(all(pos[c]), *ans.begin());
        //if (it != pos[c].begin()) --it;
        //debug(c, it-pos[c].begin());
        bool ok = true;
        //for (int i=it-pos[c].begin(); i<pos[c].size(); ++i) {
        for (int i=0; i<pos[c].size(); ++i) {
            ok = true;
            const int p = pos[c][i];
            for (char hi=c+1; hi<='z'; ++hi) {
                if (pos[hi].size() > 0 && p < pos[hi][0] && pos[hi][0] < pos[c].back()) {
                    ok = false;
                    break;
                }
            }
            debug(i, c, ok);
            auto it = ans.UB(p);
            if (i+1 == sz(pos[c]) || ok || (it != ans.end() && *it < pos[c][i+1])) {
                ans.ins(p);
                break;
            }
        }
        debug(c,  ans);
    }
    for (const int p: ans) {
        cout << S[p];
    }
    cout << '\n';
#ifdef LOCAL 
    cout.flush();
#endif
}
        
        
int main() {
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
/*
yaxyazy
*/
