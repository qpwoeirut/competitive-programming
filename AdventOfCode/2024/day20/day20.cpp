//day20.cpp created at 12/19/24 21:14:05
#include <bits/stdc++.h>

using namespace std;

#ifdef DELETE_FOR_PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class T> using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
#endif

#define pb push_back
#define eb emplace_back
#define ins insert
#define emp emplace

#define fi first
#define se second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pcll = pair<const ll,ll>;

using ull = unsigned long long;
using dbl = long double;
using pib = pair<int,bool>;
using plb = pair<ll,bool>;
using pdd = pair<dbl,dbl>;
using mii = map<int,int>;
using mll = map<ll,ll>;
using mci = map<char,int>;
using msi = map<string,int>;
using mss = map<string,string>;

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

#ifdef DELETE_THIS_IN_CASE_OF_GEO
using _t=PUT_SMTH_HERE;
using pt=complex<_t>;

const dbl EPS = 1e-16;

#define x real()
#define y imag()

namespace std {
    inline bool operator<(const pt& a, const pt& b) {
        if (abs(a.x - b.x) > EPS) return a.x < b.x;
        if (abs(a.y - b.y) > EPS) return a.y < b.y;
        return false;
    }
    inline bool operator>(const pt& a, const pt& b) {
        return b < a;
    }
}

struct Line {
    pt p1, p2;
    Line() {
        p1 = p2 = pt(0, 0);
    }
    Line(const pt& _p1, const pt& _p2) {
        p1 = min(_p1, _p2);
        p2 = max(_p1, _p2);
    }
    Line(const _t a, const _t b, const _t c, const _t d) {
        p1 = pt(a, b);
        p2 = pt(c, d);
        if (p1 > p2) swap(p1, p2);
    }
    inline bool operator<(const Line& o) const {
        return p1 < o.p1 || (p1 == o.p1 && p2 < o.p2);
    }
};

namespace std {
    inline bool operator<(const Line& a, const Line& b) {
        return a.p1 < b.p1 || (a.p1 == b.p1 && a.p2 < b.p2);
    }
}

istream& operator>>(istream& is, pt& p) {
    _t a, b;
    is >> a >> b;
    p = pt(a, b);
    return is;
}
istream& operator>>(istream& is, Line& p) {
    _t a, b, c, d;
    is >> a >> b >> c >> d;
    p = Line(a, b, c, d);
    return is;
}

string to_string(const complex<_t>& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}
string to_string(const Line& a) {
    return "(" + to_string(a.p1) + "--" + to_string(a.p2) + ")";
}
#endif

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

int N;
void setIO() {
    string filename;
    cout << "filename: " << endl;
    cin >> filename;
    if (filename == "input.txt") {
        N = 141;
    } else if (filename == "sample.txt") {
        N = 15;
    } else assert(0);
    freopen(filename.c_str(), "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll INF = 2e18 + 1;
const int INIT = 1001001001;
const int LG = 24;
const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 145;

string G[MN];

int dist[MN][MN];
int cost(int start_r, int start_c, int ssr, int ssc, int ser, int sec, int sd) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            dist[i][j] = INIT;
        }
    }
    queue<pii> q;
    q.emplace(start_r, start_c);
    dist[start_r][start_c] = 0;
    while (q.size() > 0) {
        const pii p = q.front(); q.pop();
        if (G[p.fi][p.se] == 'E') {
            return dist[p.fi][p.se];
        }
        if (p.fi == ssr && p.se == ssc && dist[ser][sec] > dist[p.fi][p.se] + 1) {
            dist[ser][sec] = dist[p.fi][p.se] + sd;
            q.emplace(ser, sec);
        }
        for (int d=0; d<4; ++d) {
            int nr = p.fi + chr[d];
            int nc = p.se + chc[d];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N || dist[nr][nc] <= dist[p.fi][p.se]) continue;
            if (G[nr][nc] != '#' && dist[nr][nc] > dist[p.fi][p.se] + 1) {
                dist[nr][nc] = dist[p.fi][p.se] + 1;
                q.emplace(nr, nc);
            }
        }
    }
    assert(0);
    return -1;
}

int main() {
    setIO();

    int start_r = -1, start_c = -1;
    for (int r=0; r<N; ++r) {
        cin >> G[r];
        for (int c=0; c<N; ++c) {
            if (G[r][c] == 'S') {
                start_r = r;
                start_c = c;
            }
        }
    }
    assert(start_r != -1 && start_c != -1);

    mii costs;
    for (int r=1; r+1<N; ++r) {
        debug(r);
        for (int c=1; c+1<N; ++c) {
            if (G[r][c] == '#') continue;
            map<pii, int> reach, reach2;
            reach[pii(r, c)] = 0;
            for (int i=0; i<20; ++i) {
                map<pii, int> reach2(reach.begin(), reach.end());
                for (const pair<const pii, int>& p: reach) {
                    if (G[p.fi.fi][p.fi.se] == 'E') continue;
                    for (int d=0; d<4; ++d) {
                        int nr = p.fi.fi + chr[d];
                        int nc = p.fi.se + chc[d];
                        if (nr <= 0 || nr + 1 >= N || nc <= 0 || nc + 1 >= N) continue;
                        if (reach2.find(pii(nr, nc)) == reach2.end()) {
                            reach2[pii(nr, nc)] = p.se + 1;
                        }
                    }
                }
                swap(reach, reach2);
            }
            for (const pair<const pii, int>& p: reach) {
                if (G[p.fi.fi][p.fi.se] == '#') continue;
                const int cst = cost(start_r, start_c, r, c, p.fi.fi, p.fi.se, p.se);
                ++costs[cst];
            }
        }
    }

    int init = cost(start_r, start_c, -1, -1, -1, -1, 0);
    debug(init);
    debug(costs);
    int ct50 = 0, ct100 = 0;
    for (const pair<const int, int>& p: costs) {
        if (init - p.fi >= 50) ct50 += p.se;
        if (init - p.fi >= 100) ct100 += p.se;
    }
    debug(ct50, ct100);

    return 0;
}
