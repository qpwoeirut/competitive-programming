//bohemian.cpp created at 10/07/23 12:51:52
// stupid O(nq log n) which runs in around 6 and a half minutes on my computer
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back
#define ins insert

#define fi first
#define se second

#define LB lower_bound

using ll = long long;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

void setIO(const string& filename = "bohemian") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}

const int MN = 600000;
const int MQ = 400000;

struct Query {
    int L, R, k;
    int idx;
};

ll N, Q;
Query query[MQ];
string A[MN];

int group_of[MN];
bitset<MN> used_g;

int grp_g[MN];
int ct_n[MN + 1];

vector<int> groups[2][MN];

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        reverse(A[i].begin(), A[i].end());
    }
    
    cin >> Q;
    for (int i=0; i<Q; ++i) {
        cin >> query[i].L >> query[i].R >> query[i].k; --query[i].L;
        query[i].idx = i;
    }
    sort(query, query+Q, [](const Query& a, const Query& b) {
        return a.k < b.k || (a.k == b.k && a.idx < b.idx);
    });

    fill(group_of, group_of + N, 0);
    int ng[2] = { 1, 0 };
    groups[0][0] = vector<int>(N);
    for (int i=0; i<N; ++i) groups[0][0][i] = i;

    debug(N, Q);
    ll ans = 0;
    int len = 0;
    for (int q=0; q<Q; ++q) {
        for (; len < query[q].k; ++len) {
            ng[(len & 1) ^ 1] = 0;
            for (int g_i=0; g_i<ng[len & 1]; ++g_i) {
                vector<int> split[26];
                for (int i: groups[len & 1][g_i]) {
                    if (len < A[i].size()) {
                        split[A[i][len] - 'a'].pb(i);
                    } else {
                        group_of[i] = -1;
                    }
                }
                for (int c=0; c<26; ++c) {
                    if (split[c].size() > 0) {
                        for (int i: split[c]) group_of[i] = ng[(len & 1) ^ 1];
                        groups[(len & 1) ^ 1][ng[(len & 1) ^ 1]++] = split[c];
                    }
                }
            }
        }

        int n_grp = 0;
        int total = 0;
        for (int i=query[q].L; i<query[q].R; ++i) {
            const int g = group_of[i];
            if (g == -1 || used_g[g]) continue;
            used_g[g] = true;
            grp_g[n_grp++] = g;
            ++ct_n[LB(groups[len & 1][g].begin(), groups[len & 1][g].end(), query[q].R) - LB(groups[len & 1][g].begin(), groups[len & 1][g].end(), query[q].L)];
            ++total;
        }

        int used = 0;
        for (int n=1; n<=N && total > 0; ++n) {
            used += min(ct_n[n], n - used);
            total -= ct_n[n];
            ct_n[n] = 0;
        }
        for (int i=0; i<n_grp; ++i) {
            used_g[grp_g[i]] = false;
        }
        ans += used;

        if (q > 0 && q % 20000 == 0) debug(q);
    }

    cout << "Case #" << testcase << ": " << ans << '\n';
}

int main() {
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}

// g++-12 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -Wl,-stack_size -Wl,0x10000000 -Ofast -Wall -DLOCAL bohemian.cpp -o temp_bohemian.out

