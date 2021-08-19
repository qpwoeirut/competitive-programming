//rompepuertas.cpp created at 08/14/21 14:53:15

#include <bits/stdc++.h>

using namespace std;

const int MN = 300005;

int N, M;

int A[MN], B[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int j=0; j<M; ++j) {
        cin >> B[j];
    }

    int start = 0;
    for (int j=0; j<M; ++j) {
        while (start < N && B[j] >= A[start]) {
            B[j] -= A[start];
            ++start;
        }
    }

    cout << start << '\n';
}

