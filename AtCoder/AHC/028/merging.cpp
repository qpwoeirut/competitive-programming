//merging.cpp created at 01/13/24 00:01:10
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
string A[M];
bitset<M> done;

const auto finish = chrono::system_clock::now() + 1950ms;

vector<pii> pos[128];

inline int dist(const pii& a, const pii& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int pi[M * 5 + 1];
inline int get_overlap(const string& S, const string& T) {
    if (S.empty() || T.empty()) return 0;
    pi[0] = 0;

    const string str = T + '#' + S;  // prefix of T to suffix of S

    for (int i = 1; i < str.size(); ++i) {
        int j = pi[i - 1];
        while (j > 0 && str[i] != str[j]) j = pi[j - 1];
        if (str[i] == str[j]) ++j;
        pi[i] = j;
    }
    return pi[str.size() - 1];
}

const int INIT = 1001001001;

int dp[M * 5][N * N];
int par[M * 5][N * N];
int cost_of(const pii& cur, const string& T, vector<pii>& moves) {
    if (T.empty()) return 0;
    for (int i = 0; i < pos[T[0]].size(); ++i) {
        dp[0][i] = dist(cur, pos[T[0]][i]);
    }
    for (int idx = 1; idx < T.size(); ++idx) {
        for (int i = 0; i < pos[T[idx]].size(); ++i) {
            dp[idx][i] = INIT;
            for (int j = 0; j < pos[T[idx - 1]].size(); ++j) {
                if (chmn(dp[idx][i], dp[idx - 1][j] + dist(pos[T[idx - 1]][j], pos[T[idx]][i]))) {
                    par[idx][i] = j;
                }
            }
        }
    }
    int ret = INIT;
    int end_idx = -1;
    for (int i = 0; i < pos[T.back()].size(); ++i) {
        if (chmn(ret, dp[T.size() - 1][i])) end_idx = i;
    }
    moves.clear();
    for (int idx = T.size() - 1; idx >= 0; --idx) {
        moves.push_back(pos[T[idx]][end_idx]);
        end_idx = par[idx][end_idx];
    }
    reverse(moves.begin(), moves.end());

    return ret;
}

void solve(int s_i, int s_j) {
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            pos[G[r][c]].emplace_back(r, c);
        }
    }

    int m = M;
    for (int over = 4; over >= 1; --over) {
        bool change = true;
        while (change) {
            change = false;
            for (int i=0; i<m; ++i) {
                for (int j=i+1; j<m; ++j) {
                    const int overlap_ij = get_overlap(A[i], A[j]);
                    if (overlap_ij >= over) {
                        A[i] = A[i] + A[j].substr(overlap_ij);
                        swap(A[j--], A[--m]);
                        change = true;
                    } else {
                        const int overlap_ji = get_overlap(A[j], A[i]);
                        if (overlap_ji >= over) {
                            A[i] = A[j] + A[i].substr(overlap_ji);
                            swap(A[j--], A[--m]);
                            change = true;
                        }
                    }
                }
            }
        }
    }
    debug(m);

    int best_time = INIT;
    vector<pii> ans;
    Xorshift rng;
    while (chrono::system_clock::now() < finish) {
        for (int i=m-1; i>0; --i) {
            swap(A[i], A[rng.randrange(i + 1)]);
        }

        string S = "";
        int cur_time = 0;
        vector<pii> path;

        pii cur(s_i, s_j);
        done.reset();
        while (done.count() < m) {
            int target = -1;
            int best = INIT;
            vector<pii> best_path;
            for (int i=0; i<m; ++i) {
                if (!done[i]) {
                    const int overlap = get_overlap(S, A[i]);
                    const string T = A[i].substr(overlap);
                    vector<pii> moves;
                    if (chmn(best, cost_of(cur, T, moves))) {
                        target = i;
                        swap(best_path, moves);
                    }
                }
            }

            cur = best_path.back();
            for (const pii& p: best_path) path.push_back(p);
            cur_time += best;

            done[target] = true;
        }

        if (chmn(best_time, cur_time)) {
            swap(ans, path);
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
        cin >> A[i];
    }
    solve(s_i, s_j);
}
