//3d_printing.cpp created at 04/02/22 15:47:34

#include <bits/stdc++.h>

using namespace std;

int A[4];

const int MIL = 1000000;

void solve(int testcase) {
    A[0] = A[1] = A[2] = A[3] = MIL;
    for (int i=0; i<3; ++i) {
        for (int j=0; j<4; ++j) {
            int tmp;
            cin >> tmp;
            A[j] = min(A[j], tmp);
        }
    }

    cout << "Case #" << testcase << ": ";
    if (A[0] + A[1] + A[2] + A[3] < MIL) {
        cout << "IMPOSSIBLE\n";
    } else if (A[0] >= MIL) {
        cout << MIL << " 0 0 0\n";
    } else if (A[0] + A[1] >= MIL) {
        cout << A[0] << ' ' << (MIL - A[0]) << " 0 0\n";
    } else if (A[0] + A[1] + A[2] >= MIL) {
        cout << A[0] << ' ' << A[1] << ' ' << (MIL - A[0] - A[1]) << " 0\n";
    } else {
        assert(A[0] + A[1] + A[2] + A[3] >= MIL);
        cout << A[0] << ' ' << A[1] << ' ' << A[2] << ' ' << (MIL - A[0] - A[1] - A[2]) << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) solve(t);
}
