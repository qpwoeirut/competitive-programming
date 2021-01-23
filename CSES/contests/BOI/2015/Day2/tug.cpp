//tug.cpp created at 01/13/21 21:59:05

#include <bits/stdc++.h>

using namespace std;

const int MN = 30005;

int N, K;
int B[2][MN], A[MN];
bool used[2][MN];

int x = 0;
bool recurse(const int idx) {
    if (idx == N) {
        return abs(x) <= K;
    }
    for (int i=0; i<2; ++i) {
        if (!used[i][B[i][idx]]) {
            used[i][B[i][idx]] = true;
            if (i) x += A[idx];
            else x -= A[idx];
            if (recurse(idx+1)) return true;
            if (i) x -= A[idx];
            else x += A[idx];
            used[i][B[i][idx]] = false;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    N <<= 1;
    for (int i=0; i<N; ++i) {
        cin >> B[0][i] >> B[1][i] >> A[i];
    }

    fill(used[0], used[0] + N, false);
    fill(used[1], used[1] + N, false);
    cout << (recurse(0) ? "YES\n" : "NO\n");
}

/*
4 1
1 1 1
2 1 2
2 2 8
1 2 2
3 3 5
3 3 2
4 4 1
4 4 2

2 5
1 1 1
1 2 4
2 2 1
2 1 4
*/
