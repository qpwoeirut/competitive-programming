#include "scales.h"
#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

const string NAMES[] = {"getLightest", "getMedian", "getHeaviest", "getNextLightest"};

struct Query {
    int type;
    int a, b, c;
    int d;
    int ans[3];

    Query() {
        type = a = b = c = d = -1;
        ans[0] = a;
        ans[1] = b;
        ans[2] = c;
    }
    Query(const int _type, const int _a, const int _b, const int _c, const int _d=-1) {
        type = _type;
        a = _a;
        b = _b;
        c = _c;
        d = _d;
        ans[0] = a;
        ans[1] = b;
        ans[2] = c;
    }

    string str() {
        return NAMES[type] + "(" + to_string(a) + ", " + to_string(b) + ", " + to_string(c) + (d == -1 ? ")" : ", " + to_string(d) + ")");
    }
};

const int N = 120;
const int M = 720;
const int K = 6;
int perm[M][6];
bool valid[M];
Query query[N];

int order[3];

const vi mark(const Query& q, const int ans) {
    vi ret;
    for (int i=0; i<M; ++i) {
        if (!valid[i]) continue;

        int oidx = 0;
        for (int j=0; j<6; ++j) {
            if (perm[i][j] == q.a || perm[i][j] == q.b || perm[i][j] == q.c) {
                order[oidx++] = perm[i][j];
            }
        }
        assert(oidx == 3);

        if (q.type != 3 && order[q.type] != ans) {
            valid[i] = false;
            ret.push_back(i);
        }
        if (q.type == 3) {
            int idx = 0;
            for (; idx<6 && perm[i][idx] != q.d; ++idx);
            assert(perm[i][idx] == q.d);
            
            while (perm[i][idx] != q.a && perm[i][idx] != q.b && perm[i][idx] != q.c) idx = (idx + 1) % 6;
            if (perm[i][idx] != ans) {
                valid[i] = false;
                ret.push_back(i);
            }
        }
    }

    return ret;
}

void unmark(const vi& v) {
    for (const int x: v) valid[x] = true;
}

bool done = false;
int qhist[K];
int recurse(int lvl, int prv) {
    if (done) return 0;
    if (lvl == 0) {
        for (int i=0; i<M; ++i) if (valid[i]) return 1;
        return 0;
    }
    cerr << lvl << ' ' << prv << ' ' << count(valid, valid+M, 1) << endl;

    int mn = M;
    for (int i=prv+1; i+lvl<=N; ++i) {
        if (lvl == 5) cerr << i << '\n';
        int mx = 0;
        qhist[lvl-1] = i;
        for (int a=0; a<3 && mx == 0; ++a) {
            const vi& marked = mark(query[i], query[i].ans[a]);
            mx = max(mx, recurse(lvl-1, i));
            unmark(marked);

            if (done) return 0;
        }

        if (mx == 0) {
            reverse(qhist, qhist+K);
            cout << K; for (int k=0; k<K; ++k) { cout << ' ' << qhist[k]; } cout << '\n';
            for (int k=0; k<K; ++k) {
                cout << query[qhist[k]].str() << '\n';
            }
            
            done = true;
            return 0;
        }
        mn = min(mn, mx);
    }
    return mn;
}

void init(int T) {
    for (int i=0; i<6; ++i) perm[0][i] = i+1;

    for (int i=1; i<M; ++i) {
        copy(perm[i-1], perm[i-1] + 6, perm[i]);
        const bool ok = next_permutation(perm[i], perm[i] + 6);
        assert(ok);
    }
    assert(perm[M-1][5] == 1);

    int idx = 0;
    for (int i=0; i<4; ++i) {
        for (int a=1; a<=6; ++a) {
            for (int b=a+1; b<=6; ++b) {
                for (int c=b+1; c<=6; ++c) {
                    if (i == 3) {
                        for (int d=1; d<=6; ++d) {
                            if (a == d || b == d || c == d) continue;
                            query[idx++] = Query(i, a, b, c, d);
                        }
                    } else query[idx++] = Query(i, a, b, c);
                }
            }
        }
    }
    assert(idx == N);

    fill(valid, valid+M, true);
    assert(recurse(K, -1) == 0);
}

void orderCoins() {
}

void orderCoins9Q() {
    int W[] = {1, 2, 3, 4, 5, 6};
    int mn1 = getLightest(1, 2, 3);
    int mn2 = getLightest(4, 5, 6);
    int other = 1;
    for (; other<=6 && (mn1 == other || mn2 == other); ++other);
    assert(mn1 != other && mn2 != other);
    W[0] = getLightest(mn1, mn2, other);

    vector<int> coins;
    for (int i=1; i<=6; ++i) if (i != W[0]) coins.push_back(i);
    assert(coins.size() == 5);

    mn1 = getLightest(coins[0], coins[1], coins[2]);
    W[1] = getLightest(coins[3], coins[4], mn1);
    coins.erase(find(coins.begin(), coins.end(), W[1]));

    mn1 = getLightest(coins[0], coins[1], coins[2]);
    W[2] = getLightest(coins[3], mn1, coins[0] == mn1 ? coins[1] : coins[0]);
    coins.erase(find(coins.begin(), coins.end(), W[2]));

    assert(coins.size() == 3);
    W[3] = getLightest(coins[0], coins[1], coins[2]);
    W[4] = getMedian(coins[0], coins[1], coins[2]);
    for (int i=0; i<3; ++i) {
        if (coins[i] != W[3] && coins[i] != W[4]) W[5] = coins[i];
    }

    answer(W);
}
/*
6! perms * ((6 * 5 * 4) / (3 * 2) * 3 + (6 * 5 * 4) / (3 * 2) * 3) queries * 3 answers * 6 per query-perm check * 6 total queries
720 perms * 120 queries * 3 answers * 6 per query-perm check * 6 total queries
720 * 120 * 3 * 6 * 6

find which query would eliminate the most options, worst-case
*/
