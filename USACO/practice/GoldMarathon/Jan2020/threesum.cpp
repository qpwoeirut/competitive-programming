#include <bits/stdc++.h>

using namespace std;

#define SE second

typedef long long ll;

const int MN = 5005;
const int MX = 1000001;

int N, Q;
int A[MN];
ll dp[MN][MN];
vector<int> pos[MX << 1];

int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        pos[A[i] + MX].push_back(i);
    }

    for (int i=0; i<N; ++i) {
        for (int j=i+2; j<N; ++j) {
            int tar = -(A[i] + A[j]) + MX;
            if (tar < 0 || tar >= (MX << 1) || pos[tar].empty()) continue;
            //cerr << "i,j,tar: " << i << ' ' << j << ' ' << tar << endl;
            
            dp[i][j] += lower_bound(pos[tar].begin(), pos[tar].end(), j) - upper_bound(pos[tar].begin(), pos[tar].end(), i);
        }
    }
    for (int len=2; len<=N; ++len) {
        for (int i=0; i<N; ++i) {
            int j = i + len - 1;
            if (j >= N) break;

            dp[i][j] += dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
        }
    }
    //for (int i=0; i<N; ++i) { for (int j=0; j<N; ++j) { cerr << dp[i][j] << ' '; } cerr << endl; }

    for (int i=0; i<Q; ++i) {
        int L, R;
        cin >> L >> R;
        --L; --R;

        cout << dp[L][R] << '\n';
    }
}

