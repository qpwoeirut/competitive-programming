//unlucky.cpp created at 04/08/23 16:28:06
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

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

template <class T> using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

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

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll INF = 2e18 + 1;
const int INIT = 1001001001;
const int LG = 24;
const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 1001001;

ll N, M, Q;
string A[MN];
ll B[MN];
vector<int> kmp[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

int D;

//bool bcheck(const int R) {
//    for (int i=0; i<N; ++i) {
//        if (A[i].size() > R + 1) continue;
//        bool match = true;
//        for (int j=0; j<A[i].size(); ++j) {
//            match &= A[i][j] == S[R + 1 - (int)(A[i].size()) + j];
//        }
//        if (match) {
//            return false;
//        }
//    }
//    return true;
//}
//
//string brute() {
//    S = string(D, '1');
//    for (int i=0; i<D; ++i) {
//        for (char d='9'; d>='1'; --d) {
//            S[i] = d;
//            if (bcheck(i)) break;
//        }
//    }
//    return S;
//}

bool check(const int R) {
    for (int i=0; i<N; ++i) {
        if (A[i][B[i]] == S[R] && B[i] + 1 == A[i].size()) return false; 
    }
    for (int i=0; i<N; ++i) {
        while (B[i] > 0 && A[i][B[i]] != S[R]) {
            //debug(i, A[i], B[i], kmp[i][B[i] - 1]);
            B[i] = kmp[i][B[i] - 1];
        }
        if (A[i][B[i]] == S[R]) {
            ++B[i];
        }
    }
    return true;
}

string brute() {
    sort(A, A+N, [](const string& a, const string& b) {
        return a.size() != b.size() ? a.size() < b.size() : a < b;
    });
    fill(B, B+N, 0);
    for (int i=0; i<N; ++i) {
        kmp[i] = vector<int>(A[i].size());
        for (int j=1; j<A[i].size(); ++j) {
            int g = kmp[i][j - 1];
            while (g && A[i][j] != A[i][g]) g = kmp[i][g - 1];
            kmp[i][j] = g + (A[i][j] == A[i][g]);
        }
        //debug(A[i], kmp[i]);
    }

    S = string(D, '1');
    for (int i=0; i<D; ++i) {
        for (char d='9'; d>='1'; --d) {
            S[i] = d;
            if (check(i)) break;
        }
    }
    return S;
}


const int K = 10;
struct Vertex {
    int next[K];
    bool leaf = false;
    int p = -1;
    char pch;
    int link = -1;
    int go[K];

    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

namespace AhoCorasick {

    vector<Vertex> t(1);

    void add_string(string const& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - '0';
            if (t[v].next[c] == -1) {
                t[v].next[c] = t.size();
                t.emplace_back(v, ch);
            }
            v = t[v].next[c];
        }
        t[v].leaf = true;
    }

    int go(int v, char ch);

    int get_link(int v) {
        if (t[v].link == -1) {
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        }
        return t[v].link;
    }

    int go(int v, char ch) {
        int c = ch - '0';
        if (t[v].go[c] == -1) {
            if (t[v].next[c] != -1)
                t[v].go[c] = t[v].next[c];
            else
                t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return t[v].go[c];
    }
};

void dfs(int n, const int u) {
    //debug(n, u);
    if (n == 0) return;
    for (char d='9'; d>='0'; --d) {
        int v = AhoCorasick::go(u, d);
        //debug(u, v, d, AhoCorasick::t[v].leaf);
        int w = AhoCorasick::get_link(v);
        //debug(w, AhoCorasick::t[w].leaf);
        if (!AhoCorasick::t[v].leaf && !AhoCorasick::t[w].leaf) {
            S += d;
            dfs(n - 1, v);
            break;
        }
    }
}

string solve() {
    AhoCorasick::t = vector<Vertex>(1);
    for (int i=0; i<N; ++i) {
        //debug(i, A[i]);
        AhoCorasick::add_string(A[i]);
    }
    S = "";
    dfs(D, 0);
    return S;
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=1000; ++N) {
        debug(N);
        for (D=10; D<=100; ++D) {
            for (int t=0; t<10000; ++t) {
                for (int i=0; i<N; ++i) {
                    if (rng() % 3 == 0) {
                        A[i] = to_string(rng() % 1000000000);
                    } else {
                        A[i] = to_string(rng() % 100);
                    }
                }

                string a = solve();
                string b = brute();
                if (a != b) {
                    cout << N << ' ' << D << endl;
                    for (int i=0; i<N; ++i) {
                        cout << A[i] << ' ';
                    }
                    cout << endl;
                    cout << a << ' ' << b << endl;
                    assert(a == b);
                }
            }
        }
    }
}

int main() {
    setIO();

    //test(); return 0;

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N >> D;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }

        cout << solve() << '\n';
    }

    return 0;
}
/*
1
2 47
9 8898

1
2 4
9 8934
*/
