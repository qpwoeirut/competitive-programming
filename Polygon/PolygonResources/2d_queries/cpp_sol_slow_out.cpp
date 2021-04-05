#include <iostream>
#include <cassert>

using namespace std;

const int MN = 1e3;

int N, M, Q;
int G[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> Q;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
        }
    }
    for (int i=0; i<Q; ++i) {
        int query_type, r, c, x;
        cin >> query_type >> r >> c;
        --r; --c;
        if (query_type == 1) {
            cin >> x;
            G[r][c] = x;
        } else if (query_type == 2) {
            cout << G[r][c] << endl;
        } else assert(false);
    }
}
