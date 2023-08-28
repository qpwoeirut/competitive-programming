//objetos.cpp created at 08/06/21 11:48:25

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MN = 300005;

ll A[MN], B[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;

    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
    }

    ll below = 0, above = 0;
    ll bw = 0, aw = 0;
    for (int i=0; i<N; ++i) {
        above += B[i] * (A[i] - A[0]);
        aw += B[i];
    }

    pair<ll,int> ans(below + above, 0);
    //cerr << "0 " << below + above << endl;
    for (int i=1; i<N; ++i) {
        const ll diff = A[i] - A[i-1];

        bw += B[i-1];
        aw -= B[i-1];

        below += bw * diff;
        above -= aw * diff;

        const ll cost = below + above;

        ans = min(ans, pair<ll,int>(cost, i));

        //cerr << i << ' ' << cost << endl;
    }

    cout << ans.second << endl;
}

