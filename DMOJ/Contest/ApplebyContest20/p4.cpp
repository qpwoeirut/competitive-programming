//p4.cpp created at 02/14/21 16:55:29

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
const int MN = 1001001;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN]; //, B[MN];
//ll G[MN][MN];
set<ll> adj[MN];

pll edge[MN];

vector<int> solve(int testcase) {
    for (int u=0; u<N; ++u) {
        for (const int v: adj[u]) {
            A[0] = -1;
            set_intersection(all(adj[u]), all(adj[v]), A);
            if (A[0] != -1) {
                return {u+1, v+1, A[0]+1};
            }
        }
    }

    vector<int> ans(4, N+1);
    for (int i=0; i<M; ++i) {
        for (int j=i+1; j<M; ++j) {
            A[0] = edge[i].FI+1;
            A[1] = edge[i].SE+1;
            A[2] = edge[j].FI+1;
            A[3] = edge[j].SE+1;
            sort(A, A+4);
            if (A[0] == A[1] || A[1] == A[2] || A[2] == A[3]) continue;

            ans = min(ans, vector<int>(A, A+4));
        }
    }
    if (ans[0] <= N) return ans;
    return {-1};
}

vector<int> brute() {
    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<N; ++j) {
            for (int k=j+1; k<N; ++k) {
                if (adj[i].count(j) && adj[i].count(k) && adj[j].count(k)) {
                    vector<int> ans;
                    ans.PB(i+1);
                    ans.PB(j+1);
                    ans.PB(k+1);
                    return ans;
                }
            }
        }
    }

    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<N; ++j) {
            for (int k=j+1; k<N; ++k) {
                for (int l=k+1; l<N; ++l) {
                    if ((adj[i].count(j) && adj[k].count(l)) ||
                        (adj[i].count(k) && adj[j].count(l)) ||
                        (adj[i].count(l) && adj[j].count(k))) {
                        vector<int> ans;
                        ans.PB(i+1);
                        ans.PB(j+1);
                        ans.PB(k+1);
                        ans.PB(l+1);
                        return ans;
                    }
                }
            }
        }
    }

    vector<int> ans;
    ans.PB(-1);
    return ans;
}

void test() {
    for (N=2; N<=15; ++N) {
        for (M=2; M<=20; ++M) {
            cerr << N << ' ' << M << endl;
            for (int t=0; t<10000; ++t) {
                for (int i=0; i<N; ++i) adj[i].clear();
                for (int i=0; i<M; ++i) {
                    int u = rand() % N;
                    int v = rand() % N;
                    while ( u == v) v = rand() % N;
                    adj[u].insert(v);
                    adj[v].insert(u);
                    edge[i] = pll(u, v);
                }

                const vector<int> sans = solve(0), bans = brute();
                if (sans != bans) {
                    cout << N << ' ' << M << endl;
                    for (int i=0; i<M; ++i) {
                        cout << edge[i].FI+1 << ' ' << edge[i].SE+1 << endl;
                    }
                    assert(0);
                }
            }
        }
    }
}
        
int main() {
    //test(); return 0;
    setIO();
    
    ll T = 1;
    
    for (int t=1; t<=T; ++t) {
        cin >> N >> M;
        for (int i=0; i<M; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            adj[u].insert(v);
            adj[v].insert(u);
            edge[i] = pll(u, v);
        }

        const vector<int> ans = solve(t);
        if (ans[0] == -1) cout << -1 << endl;
        else {
            cout << ans.size() << endl;
            for (int i=0; i<ans.size(); ++i) {
                if (i) cout << ' ';
                cout << ans[i];
            }
            cout << endl;
        }
    }
    
    return 0;
}
/*
5 4
1 4
2 4
3 4
4 5

5 4
1 2
3 5
3 1
4 2
*/
