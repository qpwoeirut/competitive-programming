//crazy_fencing.cpp created at 02/26/21 17:55:47

#include <bits/stdc++.h>

using namespace std;

const int MN = 10004;

int N;
int A[MN], B[MN];

int area(int h1, int h2, const int w) {
    if (h1 > h2) swap(h1, h2);
    int x = h1 * w;
    return 2 * x + (h2 - h1) * w;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<=N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        ans += area(A[i], A[i+1], B[i]);
    }

    cout << (ans >> 1) << (ans & 1 ? ".5" : "\n");
}
