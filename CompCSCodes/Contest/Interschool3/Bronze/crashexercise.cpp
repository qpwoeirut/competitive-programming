//crashexercise.cpp created at 02/04/21 20:31:06

// solved in 4 minutes, back to grappling with question 1

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 1003;

int N;
pii A[MN];

int main() {
    freopen("crashexercise.in", "r", stdin);
    freopen("crashexercise.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].fi >> A[i].se;
    }
    sort(A, A+N);

    int ans = 0;
    int cur = 0;
    for (int i=0; i<N; ++i) {
        if (A[i].se == 1) ++cur;
        else if (A[i].se == -1) {
            if (cur == 0) ++ans;
            else --cur;
        }
    }
    ans += cur;

    cout << ans << endl;
}
