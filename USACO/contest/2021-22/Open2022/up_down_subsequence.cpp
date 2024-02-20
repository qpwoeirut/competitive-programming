#include <bits/stdc++.h>

using namespace std;

const int MN = 300005;

int N;
int A[MN];
string S;

int BIT_U[MN], BIT_D[MN];
void update(int BIT[], int idx, int val) {
    for (; idx<MN; idx+=idx&-idx) BIT[idx] = max(BIT[idx], val);
}
int query(int BIT[], int idx) {
    int ret = -N;
    for (; idx>0; idx-=idx&-idx) ret = max(ret, BIT[idx]);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    cin >> S;

    fill(BIT_U, BIT_U+MN, -N);
    fill(BIT_D, BIT_D+MN, -N);

    int ans = 0;
    for (int i=0; i<N; ++i) {
        const int inv = N + 1 - A[i];
        const int val = max(0, max(query(BIT_U, A[i]), query(BIT_D, inv)) + 1);

        if (S[val] == 'U') update(BIT_U, A[i], val);
        if (S[val] == 'D') update(BIT_D, inv, val);
        ans = max(ans, val);
        //for (int j=0; j<i; ++j) {
        //    if (S[dp[j]] == 'U' && A[j] < A[i] && dp[i] < dp[j] + 1) {
        //        dp[i] = dp[j] + 1;
        //    }
        //    if (S[dp[j]] == 'D' && A[j] > A[i] && dp[i] < dp[j] + 1) {
        //        dp[i] = dp[j] + 1;
        //    }
        //}
        //ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
}

