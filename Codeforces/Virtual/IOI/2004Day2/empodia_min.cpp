//empodia.cpp created at 09/16/23 16:51:44

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;

const int MN = 2000000;

int M;
int A[MN];

const int TREE = 2097152;

int PN;
int tree[2 * TREE];
void init() {
    PN = M - 1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;
    for (int i = 0; i < PN; ++i) {
        tree[PN + i] = i < M ? A[i] : 0;
    }
    for (int i = PN - 1; i > 0; --i) {
        tree[i] = max(tree[i << 1], tree[(i << 1) | 1]);
    }
}
int query(int node, int tree_lo, int tree_hi, int lo, int hi) {
    if (lo <= tree_lo && tree_hi <= hi) return tree[node];
    if (hi <= tree_lo || tree_hi <= lo) return 0;
    const int tree_mid = (tree_lo + tree_hi) / 2;
    return max(query(node << 1, tree_lo, tree_mid, lo, hi), query((node << 1) | 1, tree_mid, tree_hi, lo, hi));
}

int idx_of[MN];
int get_endpoint(const int i, map<int, vector<int>>& max_seen, map<int, int>& last_update) {
    const int idx = A[i] - i + MN;

    const int new_max = query(1, 0, PN, i, last_update[idx]);
    while (max_seen[idx].size() > 0 && max_seen[idx].back() < new_max) max_seen[idx].pop_back();
    last_update[idx] = i;

    const int endpoint = max_seen[idx].empty() ? -1 : idx_of[max_seen[idx].back()];

    max_seen[idx].push_back(A[i]);

    return endpoint;
}

int close_after[MN];  // lowest index j such that i < j && a_i > a_j
void do_close_after() {
    set<int> seen;
    seen.insert(M);
    for (int v = 0; v < M; ++v) {
        const int i = idx_of[v];
        close_after[i] = *seen.upper_bound(i);
        seen.insert(i);
    }
    seen.clear();
}

vector<pii> find_intervals() {
    map<int, vector<int>> max_seen;
    map<int, int> last_update;
    for (int i = 0; i < M; ++i) {
        ++last_update[A[i] - i];
        max_seen[A[i] - i].reserve(last_update[A[i] - i]);
    }
    for (int i = 0; i < M; ++i) {
        last_update[A[i] - i] = M;
    }
    vector<pii> intervals;
    for (int i = M - 1; i >= 0; --i) {
        const int j = get_endpoint(i, max_seen, last_update);
        if (j == -1 || close_after[i] < j) continue;
        intervals.emplace_back(i, j);
    }
    max_seen.clear();
    last_update.clear();
    return intervals;
}

vector<pii> solve() {
    init();
    for (int i = 0; i < M; ++i) {
        idx_of[A[i]] = i;
    }
    do_close_after();

    vector<pii> intervals = find_intervals();
    sort(intervals.begin(), intervals.end());

    vector<pii> empodia;
    for (const pii& p: intervals) {
        while (empodia.size() > 0 && p.second <= empodia.back().second) empodia.pop_back();
        empodia.push_back(p);
    }

    return empodia;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> A[i];
    }
    
    vector<pii> empodia = solve();
    cout << empodia.size() << '\n';
    for (const pii& p: empodia) {
        cout << p.first + 1 << ' ' << p.second + 1 << '\n';
    }
}
