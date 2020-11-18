#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100001;

ll N;
ll A[MN];

int main() {
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);

    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }


    int start = 0;
    int cur = 0;
    for (int i=0; i<N; ++i) {
        cur += A[i] - 1;
        if (cur < 0) {
            start = i+1;
            cur = 0;
        }
    }

    cerr << start << endl;
    
    rotate(A, A+start, A+N);

    --A[0];
    multiset<int> cows;
    cows.insert(0);
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<A[i]; ++j) {
            cows.insert(i);
        }
        assert(cows.size() > 0);
        ll dist = i - *cows.begin();
        cows.erase(cows.begin());

        ans += dist * dist;
    }

    cout << ans << endl;
}

