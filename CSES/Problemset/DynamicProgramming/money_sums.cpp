//money_sums.cpp created at 12/17/20 19:54:18

#include <bits/stdc++.h>

using namespace std;

const int MN = 105;
const int MV = MN * 1005;

int N;
int A[MN];
bool kn[MV];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    kn[0] = true;

    for (int i=0; i<N; ++i) {
        for (int j=N*1000; j>=A[i]; --j) {
            kn[j] |= kn[j - A[i]];
        }
    }

    vector<int> ans;
    for (int i=1; i<=N*1000; ++i) {
        if (kn[i]) ans.push_back(i);
    }
    cout << ans.size() << endl;
    for (int i=0; i<ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
