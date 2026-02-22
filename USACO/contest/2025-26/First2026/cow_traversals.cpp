#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N, M;
int A[MN];
int C[MN], T[MN];

int cur[MN];
vector<int> party[MN];

int ct[4];
int par[MN], sz[MN];
int root(int u) {
    return par[u] == u ? u : (par[u] = root(par[u]));
}
void join(int ru, int rv) {
    if (ru == rv) return;
    par[rv] = ru;
    sz[ru] += sz[rv];
}

int ans[MN][3];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        --A[i];
    }

    cin >> M;
    for (int i=0; i<M; ++i) {
        char c;
        cin >> C[i] >> c;
        --C[i];

        if (c == 'C') T[i] = 1;
        else if (c == 'O') T[i] = 2;
        else if (c == 'W') T[i] = 3;
        else assert(0);
    }

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    fill(cur, cur+M, 0);
    for (int i=0; i<M; ++i) {
        party[C[i]].push_back(i);
        cur[C[i]] = T[i];
    }

    fill(ct, ct+4, 0);
    for (int i=0; i<N; ++i) {
        if (cur[i] == 0) join(root(A[i]), root(i));
    }
    for (int i=0; i<N; ++i) {
        if (i == root(i)) {
            ct[cur[i]] += sz[i];
        }
    }
    copy(ct+1, ct+4, ans[M]);

    for (int i=M-1; i>=0; --i) {
        int n = sz[root(C[i])];
        ct[cur[C[i]]] -= n;

        int p_i = lower_bound(party[C[i]].begin(), party[C[i]].end(), i) - party[C[i]].begin();
        if (p_i > 0) {
            cur[C[i]] = T[party[C[i]][p_i - 1]];
            ct[cur[C[i]]] += n;
        } else {
            cur[C[i]] = 0;
            join(root(A[C[i]]), root(C[i]));
            ct[cur[root(C[i])]] += n;
        }

        assert(ct[0] + ct[1] + ct[2] + ct[3] == N);
        copy(ct+1, ct+4, ans[i]);
    }

    for (int i=1; i<=M; ++i) {
        cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
    }
}
