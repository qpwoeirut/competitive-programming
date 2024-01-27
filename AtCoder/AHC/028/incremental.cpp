//incremental.cpp created at 01/12/24 23:19:58
#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

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
bitset<M> done;

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

const auto finish = chrono::system_clock::now() + 1990ms;

vector<pii> pos[128];

inline int cost_of(const pii& a, const pii& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

inline int get_overlap(const string& S, int i) {
    if (S.size() >= 5 && S[S.size() - 5] == A[i][0] && S[S.size() - 4] == A[i][1] && S[S.size() - 3] == A[i][2] && S[S.size() - 2] == A[i][3] && S.back() == A[i][4]) return 5;
    if (S.size() >= 4 && S[S.size() - 4] == A[i][0] && S[S.size() - 3] == A[i][1] && S[S.size() - 2] == A[i][2] && S.back() == A[i][3]) return 4;
    if (S.size() >= 3 && S[S.size() - 3] == A[i][0] && S[S.size() - 2] == A[i][1] && S.back() == A[i][2]) return 3;
    if (S.size() >= 2 && S[S.size() - 2] == A[i][0] && S.back() == A[i][1]) return 2;
    return S.size() >= 1 && S.back() == A[i][0];
}

void solve(int s_i, int s_j) {
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            pos[G[r][c]].emplace_back(r, c);
        }
    }

    int best = 1e9;
    vector<pii> ans;
    while (chrono::system_clock::now() < finish) {
        shuffle_a();
        string S = "";
        int cost = 0;
        vector<pii> path;

        int idx = 0;
        pii cur(s_i, s_j);
        done.reset();
        while (done.count() < M) {
            int target = -1;
            int best = -1;
            for (int i=0; i<M; ++i) {
                if (!done[i]) {
                    const int overlap = get_overlap(S, i);
                    if (best < overlap) {
                        best = overlap;
                        target = i;
                    }
                }
            }
            for (int i=best; i<5; ++i) S += A[target][i];

            for (; idx < S.size(); ++idx) {
                int nearest = 0;
                int best_cost = cost_of(cur, pos[S[idx]][nearest]) + 1;
                for (int i = 1; i < pos[S[idx]].size(); ++i) {
                    if (best_cost > cost_of(cur, pos[S[idx]][i])) {
                        best_cost = cost_of(cur, pos[S[idx]][i]);
                        nearest = i;
                    }
                }

                cost += cost_of(cur, pos[S[idx]][nearest]) + 1;
                cur = pos[S[idx]][nearest];
                path.push_back(cur);
            }
            done[target] = true;
        }

        if (best > cost) {
            best = cost;
            swap(ans, path);
        }
        //debug(S, cost);
    }
    //debug(best);

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
