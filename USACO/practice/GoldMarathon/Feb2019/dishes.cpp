#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

typedef vector<int> vi;

int N;
int A[MN], arr[MN];

inline const bool comp_stack(const vi& a, const vi& b) {
    return a[0] < b[0];
}

bool check(const int M) {
    copy(A, A+M, arr);
    sort(arr, arr+M);

    deque<vi> stacks;

    int idx = 0;
    vi cur(1);
    for (int i=0; i<M; ++i) {
        cur[0] = A[i];
        int pos = lower_bound(stacks.begin(), stacks.end(), cur) - stacks.begin();
        //cerr << M << ' ' << i << ' ' << pos << endl;

        if (pos == stacks.size()) {
            stacks.push_back(cur);
        } else if (stacks[pos].back() <= A[i]) {
            return false;
        } else {
            stacks[pos].push_back(A[i]);
        }

        while (stacks.size() > 0 && idx < M && stacks[0].back() == arr[idx]) {
            stacks[0].pop_back();
            if (stacks[0].empty()) stacks.pop_front();
            ++idx;
        }
    }

    return idx == M;
}

int main() {
    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    int lo = 1, hi = N;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << endl;
}
