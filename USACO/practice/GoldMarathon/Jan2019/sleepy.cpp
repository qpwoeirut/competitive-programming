#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N;

int BIT[MN];
void inc(int idx) {
    for (; idx<=N; idx+=(idx & -idx)) ++BIT[idx];
}
int query(int idx) {
    int ret = 0;
    for (; idx>0; idx-=(idx & -idx)) ret += BIT[idx];
    return ret;
}

int main() {
    freopen("sleepy.in", "r", stdin);
    freopen("sleepy.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    deque<int> A(N);
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    int x = N-1;
    for (; x>0; --x) {
        inc(A[x]);
        if (A[x-1] > A[x]) break;
    }
    if (x == 1 && A[0] < A[1]) --x;

    vector<int> ans;
    while (x > 0) {
        const int cur = A.front(); A.pop_front();
        --x;

        ans.push_back(x + query(cur));
        inc(cur);
    }

    cout << ans.size() << endl;
    for (int i=0; i<ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}

