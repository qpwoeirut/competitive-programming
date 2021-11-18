//silly_substitutions.cpp created at 11/13/21 19:16:57
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

using _t=dbl;
using pt=complex<_t>;

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

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

list<pii>::iterator iters[MN];

string solve() {
    queue<int> to_del[10];
    set<int> invalid;
    list<pii> nums;
    
    for (int i=0; i<N; ++i) {
        const int v = S[i] - '0';
        if (!nums.empty() && (nums.back().fi + 1) % 10 == v) {
            to_del[nums.back().fi].push(i-1);
        }
        nums.eb(v, i);

        if (i == 0) {
            iters[i] = nums.begin();
        } else {
            iters[i] = iters[i-1];
            ++iters[i];
        }
    }
    //for (int i=0; i<N; ++i) { debug(*(iters[i])); }

    bool change = true;
    while (change) {
        change = false;
        for (int x=0; x<10; ++x) {
            while (to_del[x].size() > 0) {
                const int idx = to_del[x].front(); to_del[x].pop();
                if (invalid.count(idx) || x != iters[idx]->fi) {
                    continue;
                }
                auto it = iters[idx]; ++it;
                if (it == nums.end()) {
                    continue;
                }
                if ((x + 1) % 10 != it->fi) {
                    continue;
                }

                //debug(x, idx, *iters[idx]);
                iters[idx]->fi = (x + 2) % 10;
                
                invalid.ins(it->se);
                nums.erase(it);
                it = iters[idx]; ++it;
                if (it != nums.end() && (x + 3) % 10 == it->fi) {
                    to_del[(x + 2) % 10].push(idx);
                    change = true;
                }

                if (iters[idx] != nums.begin()) {
                    it = iters[idx]; --it;
                    if ((x + 1) % 10 == it->fi) {
                        to_del[(x + 1) % 10].push(it->se);
                        change = true;
                    }
                }
            }
            //debug(x, nums);
        }
    }

    T = "";
    for (const pii& x: nums) {
        T.pb(x.fi + '0');
    }
    return T;
}

string brute() {
    vector<int> v;
    for (int i=0; i<N; ++i) {
        v.pb(S[i] - '0');
    }
    bool change = true;
    while (change) {
        change = false;
        for (int x=0; x<10; ++x) {
            for (int i=0; i+1<sz(v); ++i) {
                if (x == v[i] && (x + 1) % 10 == v[i+1]) {
                    v[i] = (x + 2) % 10;
                    v.erase(v.begin() + i + 1);
                    change = true;
                }
            }
        }
    }
    T = string(sz(v), '0');
    for (int i=0; i<sz(v); ++i) {
        T[i] = v[i] + '0';
    }

    return T;
}

string brute2() {
    for (int i=0; i<N; ++i) {
        A[i] = S[i] - '0';
    }

    M = N;

    bool change = true;
    while (change) {
        change = false;
        for (int x=0; x<10; ++x) {
            for (int i=0; i+1<M; ++i) {
                if (A[i] == x && A[i+1] == (x + 1) % 10) {
                    change = true;
                    A[i] = (x + 2) % 10;
                    A[i+1] = -1;
                }
            }
            M = stable_partition(A, A+M, [](int n){ return n != -1; }) - A;
            //debug1(A, M);
        }
    }

    T = string(M, '0');
    for (int i=0; i<M; ++i) {
        T[i] = A[i] + '0';
    }

    return T;
}


void test() {
    for (ll x=0; x<100000000; ++x) {
        if ((x & 65535) == 0) {
            debug(x);
        }
        //S = to_string(x);
        //N = sz(S);
        N = (rand() % 100) + 1;
        S = string(N, '0');
        for (int i=0; i<N; ++i) {
            S[i] = (rand() % 10) + '0';
        }
        const string bans = brute();
        const string sans = solve();
        if (bans != sans) {
            debug(x, bans, sans, S);
        }
        assert(bans == sans);
    }
}


int main() {
    //test(); return 0;
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N;
        cin >> S;
        const string ans = solve();
        cout << "Case #" << test_case << ": " << ans << '\n';
    }

    return 0;
}

/*
1
9

3
901

4
8901

4
9010

2
12

3
891

84
816096565588154886179013579080629729081806678248953051222780174055589670930843944206

12
179013579080

8
90135790
*/
