//talent.cpp created at 09/21/20 20:12:40
// okay so greedy does not work :(

#include <bits/stdc++.h>

using namespace std;

#define w first
#define t second

typedef pair<int,int> pii;

const int MN = 251;

int N, W;
pii A[MN];

inline const bool comp_ratio(const pii& a, const pii& b) {
    return double(a.t)/a.w > double(b.t)/b.w;
}

int main() {
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> W;

    for (int i=0; i<N; ++i) {
        cin >> A[i].w >> A[i].t;
    }

    sort(A, A+N, comp_ratio);

    double cw = 0, ct = 0;
    for (int i=0; i<N; ++i) {
        cw += A[i].w;
        ct += A[i].t;
        if (cw >= W) break;
    }

    assert(cw >= W);

    int ratio = 1000 * ct / cw;
    cout << ratio << endl;
}
