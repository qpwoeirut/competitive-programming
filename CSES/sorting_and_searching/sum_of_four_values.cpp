//sum_of_four_values.cpp created at 12/16/20 20:23:30

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 1005;

int N, X;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    map<int, pii> lo, hi;
    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<N; ++j) {
            if (A[i] + A[j] + 2 <= X) {
                hi[A[i] + A[j]] = pii(i + 1, j + 1);
            }
        }
    }
    for (int i=N-1; i>=0; --i) {
        for (int j=N-1; j>i; --j) {
            if (A[i] + A[j] + 2 <= X) {
                lo[A[i] + A[j]] = pii(i + 1, j + 1);
            }
        }
    }

    for (auto x: lo) {
        auto it = hi.find(X - x.fi);
        if (it == hi.end()) continue;

        if (x.se.fi != it->se.fi && x.se.fi != it->se.se && x.se.se != it->se.fi && x.se.se != it->se.se) {
            cout << x.se.fi << ' ' << x.se.se << ' ' << it->se.fi << ' ' << it->se.se << endl;
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
}
