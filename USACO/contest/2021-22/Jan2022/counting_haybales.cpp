#include <bits/stdc++.h>

using namespace std;

const int MN = 5003;
const int MOD = 1e9 + 7;

int N;
int A[MN];

int solve() {
    
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        cout << solve() << '\n';
    }
}
