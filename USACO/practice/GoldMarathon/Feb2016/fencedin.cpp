// retrying with Kruskal now
// read the editorial
// took me 30 mins to understand because the trick the code uses isn't mentioned at all >:(
// we can take advantage of the fact that all the edges separating parts of a column or row will be the same cost

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 2005;

int W, H, N, M;
int A[MN], B[MN];

int par[MN][MN];
int size[MN][MN];
pair<int,int> root(const pii& p) {
    if (par[p.x][p.y] != p) {
        par[p.x][p.y] = root(par[p.x][p.y]);
    }
    return par[p.x][p.y];
}

bool join(const pii& u, const pii& v) {
    const pii ru = root(u), rv = root(v);
    if (ru == rv) return false;

    if (sz[ru.x][ru.y] < sz[rv.x][rv.y]) swap(ru, rv);
    sz[ru.x][ru.y] += sz[rv.x][rv.y];
    par[rv.x][rv.y] = ru;
    return true;
}

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> W >> H >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i]
