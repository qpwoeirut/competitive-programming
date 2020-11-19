// retrying with Kruskal now
// read the editorial
// took me 30 mins to understand because the trick the code uses isn't mentioned at all >:(
// we can take advantage of the fact that all the edges separating parts of a column or row will be the same cost

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 2005;
const int SHF = 11;
const int AND = (1 << 11) - 1;

int W, H, N, M;
int A[MN], B[MN];

int par[MN][MN];
int sz[MN][MN];
int root(const int p) {
    const int x = p >> SHF, y = p & AND;
    if (par[x][y] != p) {
        par[x][y] = root(par[x][y]);
    }
    return par[x][y];
}

bool join(const int u, const int v) {
    const int ru = root(u), rv = root(v);
    if (ru == rv) return false;

    int rux = ru >> SHF, ruy = ru & AND;
    int rvx = rv >> SHF, rvy = rv & AND;
    if (sz[rux][ruy] < sz[rvx][rvy]) {
        swap(rux, rvx);
        swap(ruy, rvy);
    }
    sz[rux][ruy] += sz[rvx][rvy];
    par[rvx][rvy] = ru;
    return true;
}

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> W >> H >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<M; ++i) {
        cin >> B[i];
    }
    sort(A, A+N);
    sort(B, B+M);
    A[N] = W;
    B[M] = H;
    for (int i=N; i>0; --i) {
        A[i] -= A[i-1];
    }
    for (int i=M; i>0; --i) {
        B[i] -= B[i-1];
    }
    ++N; ++M;
    sort(A, A+N);
    sort(B, B+M);

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            par[i][j] = (i << SHF) | j;
            sz[i][j] = 1;
        }
    }

    ll ans = 0;
    for (int i=0, j=0; i<N || j<M;) {
        if (j == M || (i < N && A[i] <= B[j])) {
            for (int k=0; k+1<M; ++k) {
                if (join((i << SHF) | k, (i << SHF) |(k + 1))) ans += A[i];
            }
            ++i;
        } else {
            for (int k=0; k+1<N; ++k) {
                if (join((k << SHF) | j, ((k + 1) << SHF) | j)) ans += B[j];
            }
            ++j;
        }
    }

    cout << ans << endl;
}
