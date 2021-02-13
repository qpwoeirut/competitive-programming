//1343f.cpp created at 01/23/21 21:47:50

#include <bits/stdc++.h>

using namespace std;

const int MN = 205;

int N;
vector<int> A[MN];

bool used[MN];
int ct[MN];
int priority[MN];

int find_single() {
    fill(ct, ct+N+1, 0);
    for (int i=0; i<N-1; ++i) {
        if (used[i]) continue;
        for (const int x: A[i]) ++ct[x];
    }
    int val = -1, p = -1;
    for (int i=1; i<=N; ++i) {
        if (ct[i] == 1) {
            if (priority[i] > p) {
                p = priority[i];
                val = i;
            }
        }
    }
    return val;
}
set<int> cur;
void remove_single(const int single, const int idx) {
    for (int i=0; i<N-1; ++i) {
        if (used[i]) continue;
        bool found = false;
        for (const int x: A[i]) {
            if (x == single) {
                found = true;
                used[i] = true;
                break;
            }
        }
        if (found) {
            for (const int x: A[i]) {
                priority[x] = max(priority[x], idx + 1 - (int)A[i].size());
            }
            priority[single] = -1;
            return;
        }
    }
    assert(false);
}

int ans[MN];

bool check() {
    int B[MN];
    for (int i=0; i<N-1; ++i) {
        if (!used[i]) return false;
        bool ok = false;
        for (int j=0; j+A[i].size()<=N; ++j) {
            copy(ans + j, ans + j + A[i].size(), B);
            sort(B, B+A[i].size());
            if (equal(A[i].begin(), A[i].end(), B)) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

void solve() {
    for (int x=1; x<=N; ++x) {
        fill(ans, ans+N, -1);
        fill(priority, priority+N+1, 0);
        fill(used, used+N, false);

        ans[0] = x;

        bool ok = true;
        for (int i=N-1; i>0; --i) {
            priority[x] = -1;
            ans[i] = find_single();
            if (ans[i] == -1) {
                ok = false;
                break;
            }
            remove_single(ans[i], i);
        }
        if (!ok) continue;
        if (!check()) continue;

        for (int i=0; i<N; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << endl;
        return;
    }
    cerr << "e" << endl;
    for (int i=0; i<N; ++i) {
        cerr << ans[i] << ' ';
    } cerr << endl;
    assert(false);
}

void test() {
    int arr[MN];
    for (N=2; N<=16; ++N) {
        cerr << N << endl;
        for (int t=0; t<100000; ++t) {
            for (int i=0; i<N; ++i) {
                arr[i] = i+1;
            }
            random_shuffle(arr, arr+N);
            for (int i=1; i<N; ++i) {
                const int sz = (rand() % i) + 1;
                A[i-1] = vector<int>(arr + i - sz, arr + i + 1);
                sort(A[i-1].begin(), A[i-1].end());
            }
            random_shuffle(A, A+N-1);

            solve();
            if (!check()) {
                cout << N << endl;
                for (int i=0; i<N-1; ++i) {
                    cout << A[i].size();
                    for (const int x: A[i]) {
                        cout << ' ' << x;
                    }
                    cout << endl;
                }
                assert(false);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //test(); return 0;

    int T;
    cin >> T;
    for (int i=0; i<T; ++i) {
        cin >> N;
        for (int i=0; i<N-1; ++i) {
            int k;
            cin >> k;
            A[i] = vector<int>(k);
            for (int j=0; j<k; ++j) {
                cin >> A[i][j];
            }
        }
        solve();
    }
}
/*
4
3 2 3 4
3 1 2 3
2 1 2

4
2 1 4
3 1 3 4
2 2 4

5
2 1 2
3 1 4 5
5 1 2 3 4 5
2 1 4
*/
