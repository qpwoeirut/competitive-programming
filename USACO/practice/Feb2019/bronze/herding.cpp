#include <bits/stdc++.h>

using namespace std;

int A[3];
int main() {
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);
    
    cin >> A[0] >> A[1] >> A[2];

    sort(A, A+3);

    if (A[0] + 1 == A[1] && A[1] + 1 == A[2]) {
        cout << 0 << endl;
    } else if (A[0] + 2 == A[1] || A[1] + 2 == A[2]) {
        cout << 1 << endl;
    } else {
        cout << 2 << endl;
    }

    cout << max(A[1] - A[0], A[2] - A[1]) - 1 << endl;
}
