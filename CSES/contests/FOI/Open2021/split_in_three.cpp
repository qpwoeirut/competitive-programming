//split_in_three.cpp created at 01/29/21 20:24:38

#include <bits/stdc++.h>

using namespace std;

const int MN = 101;

const int A[7][7] = {
    {0, 0, 0, 0, 0, 0},
    {2, 3, 0, 0, 0, 0},
    {1, 2, 3, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {1, 3, 1, 3, 2, 0},
    {1, 3, 2, 2, 1, 3}
};

int N;
int ans[MN];

int main() {
    cin >> N;

    int extra = ((N - 1) % 6);
    if (extra == 0 || extra == 3) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    copy(A[extra], A[extra] + 6, ans);

    for (int i=extra + 1; i<N; i+=6) {
        ans[i] = ans[i+5] = 1;
        ans[i+1] = ans[i+4] = 2;
        ans[i+2] = ans[i+3] = 3;
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}

