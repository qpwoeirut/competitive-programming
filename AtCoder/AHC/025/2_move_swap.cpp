#include <bits/stdc++.h>

using namespace std;

const int MN = 100;
const int MD = MN / 4;

mt19937 rng(8);

int N, D, Q;
int queries;
int group_of[MN];
int ord[MN], idx[MN];

int query(vector<int> a, vector<int> b) {  // TODO cache things, check for transivity
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> intersection;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(intersection));

    a.erase(remove_if(a.begin(), a.end(), [&intersection](const int x) { return count(intersection.begin(), intersection.end(), x) > 0; }), a.end());
    b.erase(remove_if(b.begin(), b.end(), [&intersection](const int x) { return count(intersection.begin(), intersection.end(), x) > 0; }), b.end());

    if (a.empty() && b.empty()) return 0;
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

void print_groups(bool as_comment) {
    if (as_comment) cout << "#c ";
    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << group_of[i];
    }
    cout << '\n';
}

void make_moves(int failure_threshold) {
    int failures = 0;
    while (queries < Q && failures < failure_threshold) {
        for (int i = 0; i < N && queries < Q; ++i) {
            const int ga = group_of[i];
            int gb = rng() % (D - 1);
            if (gb >= ga) ++gb;

            group_of[i] = -1;

            const int new_result = query(get_group(ga), get_group(gb));
            if (new_result < 1) {
                group_of[i] = ga;
                ++failures;
            } else if (new_result == 1) {
                group_of[i] = gb;
            }
            
            cout << "# i, ga, gb, res: " << i << ' ' << ga << ' ' << gb << ' ' << new_result << endl;
            print_groups(true);
        }
    }
}

void sort_single() {
    for (int i = 0; i < N; ++i) {
        ord[i] = i;
    }
    stable_sort(ord, ord + N, [](const int a, const int b) {
        return query(vector<int>{a}, vector<int>{b}) == -1;
    });

    for (int i = 0; i < N; ++i) {
        idx[ord[i]] = i;
    }
}

void make_swaps() {
    while (queries + 1 < Q) {
        int a = rng() % N;
        int b = rng() % N;
        while (group_of[a] == group_of[b]) b = rng() % N;

        if (idx[a] > idx[b]) swap(a, b);

        const int ga = group_of[a], gb = group_of[b];
        const vector<int> group_b_orig = get_group(gb);
        if (query(get_group(ga), group_b_orig) == -1) {
            group_of[a] = gb;
            group_of[b] = ga;
            if (query(get_group(ga), group_b_orig) == 1) {  // bad swap, reverse it
                group_of[a] = ga;
                group_of[b] = gb;
            } else print_groups(true);
        }
    }
}

void solve() {
    cin >> N >> D >> Q;
    queries = 0;

    for (int i = 0; i < N; ++i) {
        group_of[i] = (D * i) / N;
    }
    print_groups(true);

    if (Q >= 12 * N) {
        sort_single();
        make_moves(4 * N);
        make_swaps();
    }
    make_moves(Q);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();
    print_groups(false);
}

