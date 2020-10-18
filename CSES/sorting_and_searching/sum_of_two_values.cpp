//sum_of_two_values.cpp created at 10/16/20 21:35:43

#include <bits/stdc++.h>

using namespace std;

#define val first
#define idx second

typedef pair<int,int> pii;

int N, X;
pii A[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i].val;
        A[i].idx = i + 1;
    }
    sort(A, A+N);
    
    int L = 0, R = N-1;
    while (L < R) {
        if (A[L].val + A[R].val == X) {
            cout << A[L].idx << ' ' << A[R].idx << endl;
            return 0;
        } else if (A[L].val + A[R].val < X) {
            ++L;
        } else {
            --R;
        }
    }

    cout << "IMPOSSIBLE" << endl;
}
