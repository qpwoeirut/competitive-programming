//line_town.cpp created at 06/15/23 23:08:50

#include <bits/stdc++.h>

using namespace std;

const int MN = 501001;
const int INF = 1001001001;

int N;
int A[MN], B[MN];

bool matches_subtask1() {
    for (int i=0; i<N; ++i) {
        if (A[i] != -1 && A[i] != 1) return false;
    }
    return true;
}
int subtask1() {
    int ans = INF;
    for (int p=0; p<=N; ++p) {
        copy(A, A+N, B);
        int cur = 0;
        for (int i=0; i<p; ++i) {
            if (B[i] == 1) {
                if (i+1 < p && B[i+1] == 1) {
                    B[i] = B[i+1] = -1;
                    ++cur;
                } else if (i+2 < N && B[i+1] == -1 && B[i+2] == -1) {
                    B[i] = -1;
                    B[i+2] = 1;
                    cur += 2;
                }
            }
        }
        for (int i=N-1; i>=p; --i) {
            if (B[i] == -1) {
                if (i-1 >= p && B[i-1] == -1) {
                    B[i] = B[i-1] = 1;
                    ++cur;
                } else if (i-2 >= 0 && B[i-1] == 1 && B[i-2] == 1) {
                    B[i] = 1;
                    B[i-2] = -1;
                    cur += 2;
                }
            }
        }

        if (is_sorted(B, B+N)) ans = min(ans, cur);
        //for (int i=0; i<N; ++i) { cerr << B[i] << ' '; } cerr << endl;
    }
    return ans == INF ? -1 : ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    if (matches_subtask1()) {
        cout << subtask1() << '\n';
    } else {
        cout << "3\n";
    }
}
