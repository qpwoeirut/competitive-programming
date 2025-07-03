#include <bits/stdc++.h>

using namespace std;

const int MN = 1000;

int A[MN];
int B[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--> 0) {
        int N;
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        for (int i=0; i<N; ++i) {
            cin >> B[i];
        }

        int cost = 0;
        int missing = 0, extra = 0;
        for (int i=0; i<N; ++i) {
            if (A[i] >= B[i]) missing += A[i] - B[i];
            else extra += B[i] - A[i];
        }

        cost = min(missing, extra);
        missing -= min(missing, extra);
        cost += 2 * missing;

        cout << cost << '\n';
    }
}
