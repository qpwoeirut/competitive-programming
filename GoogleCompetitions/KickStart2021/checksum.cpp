//checksum.cpp created at 03/20/21 21:44:24

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
const int MN = 1001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, K, Q;
ll R[MN], C[MN];
ll A[MN][MN], B[MN][MN];
//set<ll> adj[MN];

ll par[MN], sz[MN];
ll root(const ll u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
void join(const ll u, const ll v) {
    ll ru = root(u), rv = root(v);
    if (ru == rv) return;

    if (sz[ru] < sz[rv]) swap(ru, rv);
    par[rv] = par[u] = par[v] = ru;
    sz[ru] += sz[rv];
}

ll mx[MN], sum[MN];
vector<ll> cols[MN];
ll sol() {
    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = i;
    }
    for (int i=0; i<N; ++i) {
        int prv = -1;
        for (int j=0; j<N; ++j) {
            if (B[i][j] > 0) {
                if (prv != -1) {
                    join(prv, j);
                }
                prv = j;
            }
        }
    }
    fill(mx, mx+N, 0);
    fill(sum, sum+N, 0);
    fill(cols, cols+N, vector<ll>());
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            chmx(mx[j], B[i][j]);
            sum[j] += B[i][j];
        }
    }
    for (int c=0; c<N; ++c) {
        cols[root(c)].pb(c);
    }
    ll ret = 0;
    for (int c=0; c<N; ++c) {
        if (cols[c].empty()) continue;

        ll cur = 0;
        ll best = INF;
        for (const ll x: cols[c]) {
            cur += sum[x] - mx[x];
        }
        for (const ll x: cols[c]) {
            chmn(best, cur - (sum[x] - mx[x]));
        }
        ret += best;
    }

    return ret;
}

set<ll> r1[MN], c1[MN];
ll solve() {
    fill(r1, r1+N, set<ll>());
    fill(c1, c1+N, set<ll>());
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (B[i][j] > 0) {
                r1[i].ins(j);
                c1[j].ins(i);
            }
        }
    }
    queue<int> rq, cq;
    for (int i=0; i<N; ++i) {
        if (r1[i].size() == 1) {
            rq.push(i);
        }
        if (c1[i].size() == 1) {
            cq.push(i);
        }
    }

    while (rq.size() + cq.size() > 0) {
        while (rq.size() > 0) {
            const int r = rq.front(); rq.pop();
            if (r1[r].size() != 1) continue;
            const int c = *r1[r].begin();
            r1[r].erase(r1[r].begin());
            c1[c].erase(r);
            if (c1[c].size() == 1) {
                cq.push(c);
            }
            B[r][c] = 0;
        }
        while (cq.size() > 0) {
            const int c = cq.front(); cq.pop();
            if (c1[c].size() != 1) continue;
            const int r = *c1[c].begin();
            c1[c].erase(c1[c].begin());
            r1[r].erase(c);
            if (r1[r].size() == 1) {
                rq.push(r);
            }
            B[r][c] = 0;
        }
    }

    ll ans = sol();
    for (int i=0; i<N; ++i) {
        for (int j=0; j<i; ++j) {
            swap(B[i][j], B[j][i]);
        }
    }
    chmn(ans, sol());

    return ans;
}

ll brute() {
    fill(r1, r1+N, set<ll>());
    fill(c1, c1+N, set<ll>());
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (B[i][j] > 0) {
                r1[i].ins(j);
                c1[j].ins(i);
            }
        }
    }
    queue<int> rq, cq;
    for (int i=0; i<N; ++i) {
        if (r1[i].size() == 1) {
            rq.push(i);
        }
        if (c1[i].size() == 1) {
            cq.push(i);
        }
    }

    ll ans = 0;
    do {
        while (rq.size() > 0) {
            const int r = rq.front(); rq.pop();
            if (r1[r].size() != 1) continue;
            const int c = *r1[r].begin();
            r1[r].erase(r1[r].begin());
            c1[c].erase(r);
            if (c1[c].size() == 1) {
                cq.push(c);
            }
            B[r][c] = 0;
        }
        while (cq.size() > 0) {
            const int c = cq.front(); cq.pop();
            if (c1[c].size() != 1) continue;
            const int r = *c1[c].begin();
            c1[c].erase(c1[c].begin());
            r1[r].erase(c);
            if (r1[r].size() == 1) {
                rq.push(r);
            }
            B[r][c] = 0;
        }
        while (rq.size() + cq.size() == 0) {
            ll best = INF, br = -1, bc = -1;
            for (int r=0; r<N; ++r) {
                for (int c=0; c<N; ++c) {
                    if (B[r][c] > 0 && chmn(best, B[r][c])) {
                        br = r;
                        bc = c;
                    }
                }
            }
            if (best == INF) break;

            r1[br].erase(bc);
            c1[bc].erase(br);
            ans += B[br][bc];
            B[br][bc] = 0;
            if (r1[br].size() == 1) rq.push(br);
            if (c1[bc].size() == 1) cq.push(bc);
        }
    } while (rq.size() + cq.size() > 0);

    return ans;
}

ll rsum[MN], csum[MN];
ll b_cpy[MN][MN];
void test() {
    for (N=1; N<=4; ++N) {
        for (int t=0; t<100000; ++t) {
            fill(R, R+N, 0);
            fill(C, C+N, 0);
            for (int r=0; r<N; ++r) {
                for (int c=0; c<N; ++c) {
                    A[r][c] = rand() & 1;
                    B[r][c] = 0;
                    R[r] ^= A[r][c];
                    C[c] ^= A[r][c];
                }
            }
            int x = rand() % (N*N + 1);
            while (x--) {
                int r = rand() % N;
                int c = rand() % N;
                A[r][c] = -1;
                B[r][c] = rand() % 10;
            }
            for (int r=0; r<N; ++r) {
                for (int c=0; c<N; ++c) {
                    b_cpy[r][c] = B[r][c];
                }
            }

            ll bans = brute();
            for (int r=0; r<N; ++r) {
                for (int c=0; c<N; ++c) {
                    B[r][c] = b_cpy[r][c];
                }
            }
            ll sans = solve();
            for (int r=0; r<N; ++r) {
                for (int c=0; c<N; ++c) {
                    B[r][c] = b_cpy[r][c];
                }
            }
            if (bans != sans) {
                debug(bans, sans);
                debug(N);
                debug2(A, N, N);
                debug2(B, N, N);
                debug1(R, N);
                debug1(C, N);
            }
            assert(bans == sans);
        }
    }
}
        
int main() {
    //test(); return 0;
    setIO();
    
    ll T = 1;
    cin >> T;
    
    for (int test_case=1; test_case<=T; ++test_case) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                cin >> A[i][j];
            }
        }
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                cin >> B[i][j];
            }
        }
        for (int i=0; i<N; ++i) {
            cin >> R[i];
        }
        for (int i=0; i<N; ++i) {
            cin >> C[i];
        }

        //solve(test_case);
        cout << "Case #" << test_case << ": " << brute() << '\n';
    }
    
    return 0;
}
