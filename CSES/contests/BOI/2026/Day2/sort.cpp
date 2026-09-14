#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int MN = 200005;
const int INF = 1001001001;

int N, Q;
int A[MN];
pii query[MN];

int B[MN];

int bans[MN];

void brute() {
    for (int q=0; q<Q; ++q) {
        const auto [a, b] = query[q];

        copy(A, A+N, B);
        int ct_a = 0;
        while (!is_sorted(B, B+N) && (!is_sorted(B, B+a) || !is_sorted(B+N-b, B+N))) {
            if (ct_a % 2 == 0) sort(B, B+a);
            else sort(B+N-b, B+N);
            ++ct_a;
        }
        if (!is_sorted(B, B+N)) ct_a = INF;

        copy(A, A+N, B);
        int ct_b = 0;
        while (!is_sorted(B, B+N) && (!is_sorted(B, B+a) || !is_sorted(B+N-b, B+N))) {
            if (ct_b % 2 == 1) sort(B, B+a);
            else sort(B+N-b, B+N);
            ++ct_b;
        }
        if (!is_sorted(B, B+N)) ct_b = INF;

        bans[q] = min(ct_a, ct_b);
    }
}

int sans[MN];
pii arr[MN];
int perm[MN];
int done[MN];
int pref_max[MN], suff_min[MN];

void set_sort(set<int>& lo, set<int>& hi) {
    while (*lo.rbegin() > *hi.begin()) {
        lo.insert(*hi.begin());
        hi.erase(hi.begin());

        hi.insert(*lo.rbegin());
        auto it = lo.end(); --it;
        lo.erase(it);
    }
}

int count_ops(int a, int b, int i) {
    if (a >= N || b >= N) return 0;
    set<int> lo(B, B+N-b), mid(B+N-b, B+a), hi(B+a, B+N);
    int ct = 0;
    while (*lo.rbegin() > *mid.begin() || *mid.rbegin() > *hi.begin()) {
        if (i % 2 == 0) set_sort(lo, mid);
        else set_sort(mid, hi);
        ++i; ++ct;
    }
    return ct;
}

void solve() {
    for (int i=0; i<N; ++i) {
        arr[i] = pii(A[i], i);
    }
    sort(arr, arr+N);
    for (int i=0; i<N; ++i) {
        perm[arr[i].second] = i;
    }

    pref_max[0] = perm[0];
    for (int i=1; i<N; ++i) {
        pref_max[i] = max(pref_max[i-1], perm[i]);
    }
    suff_min[N-1] = perm[N-1];
    for (int i=N-2; i>=0; --i) {
        suff_min[i] = min(suff_min[i+1], perm[i]);
    }

    done[N] = 0;
    for (int i=N-1; i>=0; --i) {
        if (perm[i] == i) done[i] = 1 + done[i+1];
        else done[i] = 0;
    }

    //for (int i=0; i<N; ++i) cerr << i << ' ' << perm[i] << ' ' << done[i] << ' ' << pref_max[i] << ' ' << suff_min[i] << endl;

    for (int q=0; q<Q; ++q) {
        const auto [a, b] = query[q];
        if (a + b <= N) {
            if (done[a] < N - b - a || pref_max[a - 1] > suff_min[N - b]) sans[q] = INF;
            else {
                int ct = 0;
                if (done[0] < a) ++ct;
                if (done[N - b] < b) ++ct;
                sans[q] = ct;
            }
            continue;
        }

        int ct_a = 0;
        copy(perm, perm+N, B);
        if (!is_sorted(B, B+a)) {
            sort(B, B+a);
            ++ct_a;
        }
        if (!is_sorted(B+N-b, B+N)) {
            sort(B+N-b, B+N);
            ++ct_a;
        }
        ct_a += count_ops(a, b, 0);

        int ct_b = 0;
        copy(perm, perm+N, B);
        if (!is_sorted(B+N-b, B+N)) {
            sort(B+N-b, B+N);
            ++ct_b;
        }
        if (!is_sorted(B, B+a)) {
            sort(B, B+a);
            ++ct_b;
        }
        ct_b += count_ops(a, b, 1);

        sans[q] = min(ct_a, ct_b);
    }
}

void test() {
    mt19937 rng(8);

    for (N=1; N<=1000; ++N) {
        cerr << N << endl;
        for (Q=1; Q<=1000; ++Q) {
            for (int t=0; t<100; ++t) {
                for (int i=0; i<N; ++i) {
                    A[i] = rng() % 12 + 1;
                }
                for (int q=0; q<Q; ++q) {
                    query[q].first = rng() % N + 1;
                    query[q].second = rng() % N + 1;
                }
                brute();
                solve();

                bool ok = true;
                for (int i=0; i<N; ++i) {
                    ok &= min(bans[i], INF) == min(sans[i], INF);
                }
                if (!ok) {
                    cout << N << ' ' << Q << endl;
                    for (int i=0; i<N; ++i) cout << A[i] << ' ';
                    cout << endl;
                    for (int q=0; q<Q; ++q) cout << query[q].first << ' ' << query[q].second << endl;
                    cout << "\n\n";
                    for (int q=0; q<Q; ++q) cout << bans[q] << ' ';
                    cout << endl;
                    for (int q=0; q<Q; ++q) cout << sans[q] << ' ';
                    cout << endl;
                }
                assert(ok);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    test(); return 0;

    cin >> N >> Q;
    for (int i=0; i<N; ++i) cin >> A[i];
    for (int i=0; i<Q; ++i) {
        cin >> query[i].first >> query[i].second;
    }

    solve();
    for (int i=0; i<Q; ++i) {
        cout << (sans[i] >= INF ? -1 : sans[i]) << '\n';
    }
}
