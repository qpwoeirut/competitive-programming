#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N;
int A[MN], sorted[MN];

int cpy[MN];
int brute() {
    int ret = 0;
    bool done = false;
    while (!done) {
        done = true;
        ++ret;

        for (int i=0; i<N-1; ++i) {
            if (A[i+1] < A[i]) swap(A[i], A[i+1]);
        }
        for (int i=N-2; i>=0; --i) {
            if (A[i+1] < A[i]) swap(A[i], A[i+1]);
        }
        for (int i=0; i<N-1; ++i) {
            if (A[i+1] < A[i]) {
                done = false;
                break;
            }
        }
    }
    return ret;
}

int solve() {
    sort(sorted, sorted+N);
    
    int ans = 1;
    multiset<int> out;
    for (int i=0; i<N; ++i) {
        out.insert(A[i]);
        while (out.size() > 0 && *out.begin() <= sorted[i]) {
            out.erase(out.begin());
        }
        ans = max(ans, (int)out.size());
    }
    return ans;
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        cpy[i] = sorted[i] = A[i];
    }
    cout << solve() << endl;
    return 0;

    for (N=1; N<=10; ++N) {
        for (int t=0; t<10000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = rand() % 10;
            }

            int sans = solve();
            int bans = brute();

            if (sans != bans) {
                cerr << sans << ' ' << bans << endl;
                cerr << N << endl;
                for (int i=0; i<N; ++i) {
                    cerr << A[i] << ' ';
                }
            }
            assert(sans == bans);
        }
    }
}
