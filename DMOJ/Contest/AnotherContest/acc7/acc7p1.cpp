//acc7p1.cpp created at 04/04/21 12:05:47

#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) {
        int N;
        cin >> N;
        if (N == 2) {
            cout << 2 << '\n';
        } else {
            cout << N-1 << '\n';
        }
    }
}

