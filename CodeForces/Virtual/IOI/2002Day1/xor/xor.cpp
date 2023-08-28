//xor.cpp created at 08/27/23 13:34:56

#include <bits/stdc++.h>

using namespace std;
using operation=array<int, 4>;

const int N_ARRAY[11] = { 7, 10, 20, 40, 100, 900, 128, 500, 600, 1500, 2000 };
const string TEST = "04";
const int N = N_ARRAY[3];

bitset<N> grid[N], G[N];
bitset<N+1> flips[N+1];

void apply_grid(const vector<operation>& ops) {
    for (int r=0; r<N; ++r) {
        flips[r].reset();
        G[r] = grid[r];
    }
    for (const operation& op: ops) {
        flips[op[2]][op[0]].flip();
        flips[op[2]][op[1]].flip();
        flips[op[3]][op[0]].flip();
        flips[op[3]][op[1]].flip();
    }

    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            flips[r][c] = flips[r][c] ^ (r > 0 ? flips[r-1][c] : 0) ^ (c > 0 ? flips[r][c-1] : 0) ^ (r > 0 && c > 0 ? flips[r-1][c-1] : 0);
            G[r][c] = G[r][c] ^ flips[r][c];
        }
    }
}

const int EDGE_WEIGHT = 50;
const int CORNER_WEIGHT = 200;
const int COUNT_WEIGHT = 1;

const long long MULT = 1e5;
consteval array<long long, N*N> gen_root() {
    array<long long, N*N> arr;
    arr[0] = MULT;
    for (int i=1; i<N*N; ++i) {
        arr[i] = pow(i, 0.8 / sqrt(N)) * MULT;
    }
    return arr;
}
constexpr array<long long, N*N> root = gen_root();

int score_of(const vector<operation>& ops) {
    apply_grid(ops);

    int score = 0;
    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            const int left = c > 0 ? G[r][c] != G[r][c-1] : 0;
            const int right = c+1 < N ? G[r][c] != G[r][c+1] : 0;
            const int top = r > 0 ? G[r][c] != G[r-1][c] : 0;
            const int bottom = r+1 < N ? G[r][c] != G[r+1][c] : 0;

            score += COUNT_WEIGHT * G[r][c];
            score += EDGE_WEIGHT * (left + right + top + bottom);
            score += CORNER_WEIGHT * ((left & top) + (top & right) + (right & bottom) + (bottom & left));
        }
    }

    return score * (root[ops.size()]) / MULT;
}

template<const int mod> int binpow(long long x, int p) {
    x %= mod;
    long long ret = 1;
    for (; p > 0; p >>= 1) {
        if (p & 1) ret = (ret * x) % mod;
        x = (x * x) % mod;
    }
    return ret;
}

const int N_MOD = 3;
const int MOD[N_MOD] = { 1000000007, 1000000009, 1000000021 }; // 33, 87, 93, 97
static_assert(N <= 128);
const long long BASE = (N + 1) * (N + 1) * (N + 1) * (N + 1);
using hash_t=array<int, N_MOD>;
hash_t hash_of(const vector<operation>& ops) {
    hash_t h;
    for (const operation& op: ops) {
        const int op_hash = ((op[0] * (N + 1) + op[1]) * (N + 1) + op[2]) * (N + 1) + op[3];
        for (int i = 0; i < N_MOD; ++i) {
            h[i] = (h[i] * BASE + op_hash) % MOD[i];
        }
    }
    return h;
}

struct Sol {
    vector<operation> ops;
    int score;
    hash_t hash;

    Sol(const vector<operation>& _ops) {
        ops = _ops;
        ops.shrink_to_fit();
        sort(ops.begin(), ops.end());
        score = score_of(ops);
        hash = hash_of(ops);
    }
    Sol(const Sol& sol, operation op) {
        ops = sol.ops;
        ops.push_back(op);
        ops.shrink_to_fit();
        sort(ops.begin(), ops.end());
        score = score_of(ops);

        const int op_hash = ((op[0] * (N + 1) + op[1]) * (N + 1) + op[2]) * (N + 1) + op[3];
        for (int i = 0; i < N_MOD; ++i) {
            hash[i] = (hash[i] * BASE + op_hash) % MOD[i];
        }
    }
    inline bool operator<(const Sol& o) const {
        return score > o.score || (score == o.score && ops > o.ops);
    }
};

const int B = N / 2;
const int A = B - 1;
int cutoff[N*N];
int main() {
    ifstream fin("tests/" + TEST);
    assert(fin.is_open());

    cerr << "Test " << TEST << endl;

    int n;
    fin >> n;
    assert(n == N);

    for (int r=0; r<N; ++r) {
        for (int c=0; c<N; ++c) {
            char ch;
            fin >> ch;
            grid[r][c] = ch == '1';
        }
    }
    fin.close();

    set<hash_t> visited;
    priority_queue<Sol> pq;
    pq.emplace(vector<operation>());
    for (int i=0; i<N*N; ++i) cutoff[i] = pq.top().score;

    vector<operation> best;
    while (pq.size() > 0) {
        const Sol cur = pq.top(); pq.pop();

        if (cur.score == 0) {
            if (best.size() == 0 || best.size() > cur.ops.size()) {
                best = cur.ops;
                cerr << "best size: " << best.size() << endl;

                ofstream fout("out/" + TEST + ".out");
                assert(fout.is_open());
                fout << best.size() << '\n';
                for (const operation& op: best) {
                    fout << op[0] + 1 << ' ' << op[1] << ' ' << op[2] + 1 << ' ' << op[3] << '\n';
                }
                fout.close();
            }
            continue;
        }
        if (best.size() > 0 && best.size() <= cur.ops.size() + 1) continue;
        if (cur.score * A > cutoff[cur.ops.size()] * B) continue;

        apply_grid(cur.ops);

        //cerr << cur.score << ' ' << cur.ops.size() << '\n';
        //for (int r=0; r<N; ++r) cerr << G[r].to_string() << '\n';
        //cerr << endl;

        for (int left=0; left < N; ++left) {
            for (int top=0; top < N; ++top) {
                if (!G[top][left]) continue;
                for (int right=left + 1; right <= N; ++right) {
                    for (int bottom = top + 1; bottom <= N; ++bottom) {
                        if (!G[bottom - 1][right - 1]) continue;
                        const Sol nxt(cur.ops, array<int, 4>{left, right, top, bottom});
                        if (nxt.score * A <= cutoff[cur.ops.size()] * B && visited.count(nxt.hash) == 0) {
                            cutoff[cur.ops.size()] = min(cutoff[cur.ops.size()], nxt.score);
                            visited.insert(nxt.hash);
                            pq.push(nxt);
                        }
                    }
                }
            }
        }
    }
}

