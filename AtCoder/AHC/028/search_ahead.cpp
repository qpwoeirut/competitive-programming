//search_ahead.cpp created at 01/13/24 01:09:14
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

using pii=pair<int,int>;

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

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

const auto finish = chrono::system_clock::now() + 1750ms;

pii pos[N * N];
int i_pos[128];
int pos_size[128];

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
pii moves[M * 5];
int n_moves;
int moves_for(const pii& cur, const string& T) {
    if (T.empty()) return 0;
    for (int i = 0; i < pos_size[T[0]]; ++i) {
        dp[0][i] = dist(cur, pos[i + i_pos[T[0]]]);
    }
    for (int idx = 1; idx < T.size(); ++idx) {
        for (int i = 0; i < pos_size[T[idx]]; ++i) {
            dp[idx][i] = INIT;
            for (int j = 0; j < pos_size[T[idx - 1]]; ++j) {
                if (chmn(dp[idx][i], dp[idx - 1][j] + dist(pos[j + i_pos[T[idx - 1]]], pos[i + i_pos[T[idx]]]) + 1)) {
                    par[idx][i] = j + i_pos[T[idx - 1]];
                }
            }
        }
    }
    int ret = INIT;
    int end_idx = -1;
    for (int i = 0; i < pos_size[T.back()]; ++i) {
        if (chmn(ret, dp[T.size() - 1][i])) end_idx = i;
    }
    n_moves = T.size();
    for (int idx = T.size() - 1; idx >= 0; --idx) {
        moves[idx] = pos[end_idx];
        end_idx = par[idx][end_idx];
    }

    return ret;
}
int cost_of(const pii& cur, const string& T) {
    if (T.empty()) return 0;
    for (int i = 0; i < pos_size[T[0]]; ++i) {
        dp[0][i] = dist(cur, pos[i + i_pos[T[0]]]);
    }
    for (int idx = 1; idx < T.size(); ++idx) {
        for (int i = 0; i < pos_size[T[idx]]; ++i) {
            dp[idx][i] = INIT;
            for (int j = 0; j < pos_size[T[idx - 1]]; ++j) {
                chmn(dp[idx][i], dp[idx - 1][j] + dist(pos[j + i_pos[T[idx - 1]]], pos[i + i_pos[T[idx]]]) + 1);
            }
        }
    }
    int ret = INIT;
    for (int i = 0; i < pos_size[T.back()]; ++i) {
        chmn(ret, dp[T.size() - 1][i]);
    }

    return ret;
}

pii path[M * 5];
int n_path;

pii ans[M * 5];
int n_ans;
void solve(int s_i, int s_j) {
    i_pos['A'] = 0;
    for (int i='A'; i<='Z'; ++i) {
        i_pos[i + 1] = i_pos[i];
        for (int r=0; r<N; ++r) {
            for (int c=0; c<N; ++c) {
                if (G[r][c] == i) {
                    pos[i_pos[i + 1]++] = pii(r, c);
                }
            }
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

    int best_time = INIT;
    n_ans = 0;
    Xorshift rng;

    while (chrono::system_clock::now() < finish) {
        for (int i=m-1; i>0; --i) {
            swap(A[i], A[rng.randrange(i + 1)]);
        }

        string S = "";
        int cur_time = 0;
        n_path = 0;

        pii cur(s_i, s_j);
        done.reset();
        while (done.count() < m) {
            int target = -1;
            int best = INIT;
            for (int i=0; i<m; ++i) {
                if (done[i]) continue;

                const int overlap1 = get_overlap(S, A[i]);
                const string T1 = A[i].substr(overlap1);
                for (int j=0; j<m; ++j) {
                    if (i == j || done[j]) continue;

                    const int overlap2 = get_overlap(S + T1, A[j]);
                    const string T2 = T1 + A[j].substr(overlap2);
                    if (chmn(best, cost_of(cur, T2))) {
                        target = i;
                    }
                }
            }

            if (target == -1) {
                for (int i=0; i<m; ++i) if (!done[i]) target = i;
            }
            const int overlap = get_overlap(S, A[target]);
            const string T = A[target].substr(overlap);
            cur_time += moves_for(cur, T);
            cur = moves[n_moves - 1];
            for (int i = 0; i < n_moves; ++i) path[n_path++] = moves[i];

            done[target] = true;
        }

        if (chmn(best_time, cur_time)) {
            copy(path, path + n_path, ans);
            n_ans = n_path;
        }
    }

    for (int i = 0; i < n_ans; ++i) {
        cout << ans[i].first << ' ' << ans[i].second << '\n';
    }
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
