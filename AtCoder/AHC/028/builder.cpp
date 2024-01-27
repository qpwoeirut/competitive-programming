//builder.cpp created at 01/12/24 22:21:54
#include <bits/stdc++.h>

using namespace std;

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


class Xorshift {
    public:
        Xorshift(): x_(1) {}

        Xorshift(uint32_t seed): x_(seed) {
            assert(seed);
        }

        uint32_t randrange(uint32_t stop) {
            // [0, stop)
            assert(stop > 0);
            next();
            return x_ % stop;
        }

        uint32_t randrange(uint32_t start, uint32_t stop) {
            // [start, stop)
            assert(start < stop);
            next();
            return start + x_ % (stop - start);
        }

        uint32_t randint(uint32_t a, uint32_t b) {
            // [a, b]
            assert(a <= b);
            return randrange(a, b + 1);
        }

        double random() {
            // [0.0, 1.0]
            next();
            return static_cast<double>(x_) / static_cast<double>(UINT32_MAX);
        }

        double uniform(double a, double b) {
            // [a, b] or [b, a]
            return a + (b - a) * random();
        }

    private:
        void next() {
            x_ ^= x_ << 13;
            x_ ^= x_ >> 7;
            x_ ^= x_ << 17;
        }

        uint32_t x_;
};

const int N = 15;
const int M = 200;

char G[N][N];
char A[M][5];

Xorshift rng;
void shuffle_a() {
    for (int i=M-1; i>0; --i) {
        swap(A[i], A[rng.randrange(i + 1)]);
    }
}

const int BLOCK_SIZE = 8;
static_assert(M % BLOCK_SIZE == 0);
static_assert(BLOCK_SIZE * BLOCK_SIZE * BLOCK_SIZE >= M);
const int BLOCKS = M / BLOCK_SIZE;
const int PARTS = (BLOCKS + BLOCK_SIZE - 1) / BLOCK_SIZE;
string B[BLOCKS];
string P[PARTS];

const auto finish = chrono::system_clock::now() + 1900ms;

vector<pii> pos[128];

struct Block {
    string str;
    vector<vector<int>> cost;

    Block() {
        str = "";
        cost = vector<vector<int>>();
    }

    Block(const Block& a, const Block& b) {

    }
};

string create_block(int a, int b) {

}

void solve(int s_i, int s_j) {
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            pos[G[r][c]].emplace_back(r, c);
        }
    }

    int best = 1_000_000_000;
    vector<pii> ans;
    while (chrono::system_clock::now() < finish) {
        shuffle_a();
        
        for (int b_i=0; b_i < BLOCKS; ++b_i) {
            B[b_i] = create_block(b_i * BLOCK_SIZE, (b_i + 1) * BLOCK_SIZE);
        }
        for (int p_i=0; p_i < PARTS; ++p_i) {
            P[p_i] = merge_blocks(p_i * BLOCK_SIZE, min((p_i + 1) * BLOCK_SIZE, BLOCKS));
        }
        int cost = 0;
        vector<pii> cur = merge_parts(cost);

        if (best < cost) {
            best = cost;
            swap(ans, cur);
        }
    }

    for (const pii& p: ans) cout << p.first << ' ' << p.second << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    assert(N == n);
    assert(M == m);

    int s_i, s_j;
    cin >> s_i >> s_j;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> G[i][j];
        }
    }
    for (int i=0; i<M; ++i) {
        cin >> A[i][0] >> A[i][1] >> A[i][2] >> A[i][3] >> A[i][4];
    }
    solve(s_i, s_j);
}
