#include <bits/stdc++.h>

using namespace std;

const int MN = 100;
const int MD = MN / 4;

mt19937 rng(8);

int N, D, Q;
int queries;
int group_of[MN];
int group_order[MD];

int query(const vector<int>& a, const vector<int>& b) {  // TODO cache things, check for transivity
    if (a.empty()) return -1;
    if (b.empty()) return 1;

    assert(queries < Q);
    ++queries;

    cout << a.size() << ' ' << b.size();
    for (int x: a) cout << ' ' << x;
    for (int x: b) cout << ' ' << x;
    cout << '\n';
    cout.flush();

    char resp;
    cin >> resp;
    if (resp == '<') return -1;
    if (resp == '=') return  0;
    if (resp == '>') return +1;
    assert(false);
}

vector<int> get_group(const int grp) {
    vector<int> group;
    for (int i = 0; i < N; ++i) {
        if (group_of[i] == grp) group.push_back(i);
    }
    return group;
}

void sort_groups() {
    for (int i = 0; i < D; ++i) group_order[i] = i;

    // stable_sort uses fewer comparisons I think?
    // TODO: implement sorting algo that minimizes comparisions
    stable_sort(group_order, group_order + D, [](const int ia, const int ib) {
        cout << "# sorting\n";
        return query(get_group(ia), get_group(ib)) == -1;
    });

    cout << "#";
    for (int i = 0; i < D; ++i) {
        cout << ' ' << group_order[i];
    }
    cout << '\n';
}

void print_groups(bool as_comment) {
    if (as_comment) cout << "#c ";
    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << group_of[i];
    }
    cout << '\n';
}

void solve() {
    cin >> N >> D >> Q;
    queries = 0;

    for (int i = 0; i < N; ++i) {
        group_of[i] = (D * i) / N;
    }
    print_groups(true);

    for (int fail_threshold = (Q / 2) / D; fail_threshold <= Q && queries < Q; ++fail_threshold) {
        if (8 * D <= Q - queries) sort_groups();

        int i_lo = 0;
        for (int i_hi = D - 1; i_hi > i_lo && queries < Q; --i_hi) {
            const int lo = group_order[i_lo], hi = group_order[i_hi];
            vector<int> grp_hi_original = get_group(hi);
            shuffle(grp_hi_original.begin(), grp_hi_original.end(), rng);
            int failures = 0;
            for (int x: grp_hi_original) {
                if (queries >= Q) break;

                group_of[x] = lo;

                const int new_result = query(get_group(lo), get_group(hi));
                if (new_result == 0) {
                    ++i_lo;
                    break;
                } else if (new_result == 1) {
                    group_of[x] = hi;
                    if (++failures >= fail_threshold) {
                        ++i_lo;
                        break;
                    }
                }
                
                cout << "# lo, hi, x, res: " << lo << ' ' << hi << ' ' << x << ' ' << new_result << endl;
                print_groups(true);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();
    print_groups(false);
}

