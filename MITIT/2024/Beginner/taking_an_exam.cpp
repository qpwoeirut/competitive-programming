#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int D[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;

    while (T --> 0) {
        int N, M;
        cin >> N >> M;

        for (int i=0; i<N; ++i) {
            cin >> D[i];
        }

        sort(D, D+N);

        int bonus = 0;
        int sum = 0;
        for (int i=0; i<N; ++i) {
            if (sum + D[i] <= M) {
                sum += D[i];
                ++bonus;
            }
        }

        cout << M + bonus << '\n';
    }
}
