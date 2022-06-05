//experiment.cpp created at 05/27/22 21:41:31
#include <bits/stdc++.h>
#include "sparsehash/dense_hash_map"

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

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

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

ll N, M, K, Q, T;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S;

// this only works on 4x4 boards, just an exploratory tool
// most significant byte is in the top left

using board_t = uint64_t;

google::dense_hash_map<board_t, string> path;
mt19937 rng(8);  // won't bother with uniform distrib, this is good enough

int find_zero(const board_t board) {
    int zero;
    for (zero = 0; zero<64 && ((board >> zero) & 0xF) > 0; zero+=4);
    assert(zero < 64);
    return zero;
}

uint64_t make_move(board_t board, const int zero, const char move) {
    if (move == 'L') {
        assert((zero & 0xF) < 12);
        board |= ((board >> (zero + 4)) & 0xF) << zero;
        board ^= ((board >> (zero + 4)) & 0xF) << (zero + 4);
    } else if (move == 'R') {
        assert(4 <= (zero & 0xF));
        board |= ((board >> (zero - 4)) & 0xF) << zero;
        board ^= ((board >> (zero - 4)) & 0xF) << (zero - 4);
    } else if (move == 'U') {
        assert(zero < 48);
        board |= ((board >> (zero + 16)) & 0xF) << zero;
        board ^= ((board >> (zero + 16)) & 0xF) << (zero + 16);
    } else if (move == 'D') {
        assert(16 <= zero);
        board |= ((board >> (zero - 16)) & 0xF) << zero;
        board ^= ((board >> (zero - 16)) & 0xF) << (zero - 16);
    } else assert(0);

    return board;
}
uint64_t make_random_move(const board_t board) {
    const int zero = find_zero(board);
    string options = "";
    if ((zero & 0xF) < 12) options += 'L';
    if (4 <= (zero & 0xF)) options += 'R';
    if (zero < 48) options += 'U';
    if (16 <= zero) options += 'D';
    assert(options.size() > 0);
    return make_move(board, zero, options[rng() % options.size()]);
}

int board_arr[16];
board_t to_board() {
    board_t ret = 0;
    for (int i=0; i<16; ++i) {
        ret <<= 4;
        ret |= board_arr[i];
    }
    return ret;
}

const string HEX = "0123456789abcdef";

string board_to_string(const board_t board) {
    string s = "";
    for (int i=60; i>=0; i-=4) {
        s += HEX[(board >> i) & 0xF];
        if (i == 48 || i == 32 || i == 16 || i == 0) s += '\n';
    }
    return s;
}

int main() {
    setIO();

    N = 4;
    T = 2 * cube(N);

    path.set_empty_key(0);
    
    for (int i=0; i<16; ++i) {
        board_arr[i] = 1 + (rng() % 15);
    }
    board_arr[rng() % 16] = 0;

    const board_t start = to_board();
    board_t target = start;
    for (int i=0; i<30; ++i) target = make_random_move(target);

    cout << N << ' ' << T << endl;
    cout << board_to_string(start) << endl;
    cout << board_to_string(target) << endl;

    int ct = 0;
    queue<pair<board_t, int>> q;  // storing length of path in queue is enough
    q.emplace(start, 0);
    path[start] = "";
    while (q.size() > 0) {
        const pair<board_t, int> cur = q.front(); q.pop();

        if (((++ct) & 0xFFFF) == 0) {
            cout << ct << ' ' << cur.se << endl;
        }

        if (cur.fi == target) break;

        const string& cur_path = path[cur.fi];
        if (sz(cur_path) < cur.se) continue;

        const int zero = find_zero(cur.fi);
        
        if ((zero & 0xF) < 12) {
            const board_t nxt = make_move(cur.fi, zero, 'L');
            if (path.find(nxt) == path.end()) {
                path[nxt] = cur_path + 'L';
                q.emplace(nxt, cur.se + 1);
            }
        }
        if (4 <= (zero & 0xF)) {
            const board_t nxt = make_move(cur.fi, zero, 'R');
            if (path.find(nxt) == path.end()) {
                path[nxt] = cur_path + 'R';
                q.emplace(nxt, cur.se + 1);
            }
        }
        if (zero < 48) {
            const board_t nxt = make_move(cur.fi, zero, 'U');
            if (path.find(nxt) == path.end()) {
                path[nxt] = cur_path + 'U';
                q.emplace(nxt, cur.se + 1);
            }
        }
        if (16 <= zero) {
            const board_t nxt = make_move(cur.fi, zero, 'D');
            if (path.find(nxt) == path.end()) {
                path[nxt] = cur_path + 'D';
                q.emplace(nxt, cur.se + 1);
            }
        }
    }

    cout << path[target] << endl;
}

