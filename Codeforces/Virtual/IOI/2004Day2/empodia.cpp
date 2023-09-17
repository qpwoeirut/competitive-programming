//empodia.cpp created at 09/16/23 16:51:44

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;

const int MN = 2000000;

int M;
int A[MN];

vector<pii> brute() {
    vector<pii> intervals;

    for (int i = 0; i < M; ++i) {
        int mx = A[i];
        for (int j = i + 1; j < M; ++j) {
            if (A[i] > A[j]) break;
            mx = max(mx, A[j]);
            if (j - i == A[j] - A[i] && mx == A[j]) {
                intervals.emplace_back(i, j);
                break;
            }
        }
    }
    sort(intervals.begin(), intervals.end());

    vector<pii> empodia;
    for (const pii& p: intervals) {
        while (empodia.size() > 0 && p.second <= empodia.back().second) empodia.pop_back();
        empodia.push_back(p);
    }

    return empodia;
}

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

void test() {
    mt19937 rng(8);
    for (M = 4; M <= 20; ++M) {
        cerr << M << endl;
        for (int t = 0; t < 100000; ++t) {
            for (int i = 0; i < M; ++i) {
                A[i] = i;
            }
            shuffle(A+1, A+M-1, rng);
            bool ok = false;
            while (!ok) {
                ok = true;
                for (int i = 1; i < M; ++i) {
                    if (A[i - 1] == A[i] - 1) {
                        swap(A[min(i, M - 2)], A[(rng() % (M - 2) + 1)]);
                        ok = false;
                    }
                }
            }

            const vector<pii> bans = brute();
            const vector<pii> sans = solve();
            if (bans != sans) {
                cout << M << '\n';
                for (int i = 0; i < M; ++i) {
                    if (i) cout << ' ';
                    cout << A[i];
                }
                cout << '\n';

                cout << sans.size() << '\n'; for (const pii& p: sans) { cout << p.first << ' ' << p.second << '\n'; }
                cout << bans.size() << '\n'; for (const pii& p: bans) { cout << p.first << ' ' << p.second << '\n'; }
                cout.flush();
            }
            assert(sans == bans);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> A[i];
    }
    
    vector<pii> empodia = solve();
    //vector<pii> empodia = brute();
    cout << empodia.size() << '\n';
    for (const pii& p: empodia) {
        cout << p.first + 1 << ' ' << p.second + 1 << '\n';
    }
}
/*
6
0 2 1 4 3 5

7
0 5 1 3 2 4 6

8
0 3 2 1 4 6 5 7
*/
