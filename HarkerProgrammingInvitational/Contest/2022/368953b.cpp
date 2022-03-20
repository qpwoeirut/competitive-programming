#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

int N, Q;
int A[1003];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    map<int,int> ct;
    for (int i=0; i<Q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        
        ct.clear();
        pii best(-1, -1);
        for (int j=l; j<r; ++j) {
            ++ct[A[j]];
            best = max(best, pii(ct[A[j]], -A[j]));
        }

        cout << -best.second << '\n';
    }
}
