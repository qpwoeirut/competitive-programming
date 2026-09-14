#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MN = 200005;

int N, D;
int A[MN];
int B[MN];
int pa[MN];
int pb[MN];

int f(int b_i) {
    return (pa[B[b_i]] - (b_i ? pa[B[b_i - 1]] : -1) + N - 1) % N;
}

void apply(int c, int x, int y) {
    if (c == 1) {
        swap(A[x], A[y]);
        pa[A[x]] = x;
        pa[A[y]] = y;
    } else {
        swap(B[x], B[y]);
        pb[B[x]] = x;
        pb[B[y]] = y;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> D;

    for (int i=0; i<N; ++i) {
        cin >> A[i]; --A[i];
        pa[A[i]] = i;
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i]; --B[i];
        pb[B[i]] = i;
    }
    
    A[N] = N;
    B[N] = N;
    pa[N] = N;
    pb[N] = N;
    ll ans = 0;
    for (int i=0; i<=N; ++i) {
        ans += f(i);
    }
    cout << ans - f(N) << '\n';

    for (int i=0; i<D-1; ++i) {
        int c, x, y;
        cin >> c >> x >> y; --x; --y;

        int b_x = c == 1 ? pb[A[x]] : x, b_y = c == 1 ? pb[A[y]] : y;
        if (b_x > b_y) swap(b_x, b_y);

        if (b_x + 1 == b_y) {
            int old = f(b_x) + f(b_y) + f(b_y + 1);
            apply(c, x, y);
            int upd = f(b_x) + f(b_y) + f(b_y + 1);
            ans += upd - old;
        } else {
            int old = f(b_x) + f(b_x + 1) + f(b_y) + f(b_y + 1);
            apply(c, x, y);
            int upd = f(b_x) + f(b_x + 1) + f(b_y) + f(b_y + 1);
            ans += upd - old;
        }

        cout << ans - f(N) << '\n';
    }
}
/*
4 4
1 2 3 4
1 2 3 4
1 2 3
2 2 4
1 1 4
*/
