//atrapasuenos.cpp created at 08/14/21 16:55:18

#include <bits/stdc++.h>

using namespace std;

const int MN = 1003;

int N, K;
int X;
int A[MN];
int count_intersections() {
    int intersections = 0;
    for (int i=0; i<N-1; ++i) {
        const int x = A[i];
        const int y = (A[i+1] - x + N) % N;
        for (int j=0; j<i; ++j) {
            const int x0 = (A[j] - x + N) % N, y0 = (A[j+1] - x + N) % N;
            if (((x0 < y && y < y0) || (y0 < y && y < x0)) && x0 != 0 && y0 != 0) {
                if (++intersections > K) return intersections;
            }
        }
    }
    return intersections;
}

void solve() {
    cin >> N >> K;
    
    for (int i=0; i<N; ++i) {
        A[i] = i;
    }
    do {
        const int ct = count_intersections();
        //cerr << ct << endl; for (int i=0; i<N; ++i) { cerr << A[i] << ' '; } cerr << endl;
        if (ct == K) {
            cout << "SI\n";
            for (int i=0; i<N; ++i) {
                if (i) cout << ' ';
                cout << A[i] + 1;
            }
            cout << '\n';
            return;
        }
    }
    while (next_permutation(A, A+N));

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio();

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) {
        solve();
    }
}

/*
5
6 4
2 0
2 1
8 10
5 1000000000
*/
