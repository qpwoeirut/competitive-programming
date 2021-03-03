//814d.cpp created at 02/21/21 22:42:33

#include <bits/stdc++.h>

using namespace std;

#define x real()
#define y imag()

typedef long long ll;
typedef long double dbl;
typedef complex<ll> pt;

const int MN = 1003;

int N;
pt A[MN];
ll R[MN];

set<int> child[MN];
dbl dp[MN][2][2];
bool done[MN][2][2];

const dbl PI = acos(-1.0);

dbl solve(const int node, int h1, int h2) {
    if (h1 < h2) swap(h1, h2);
    if (done[node][h1][h2]) return dp[node][h1][h2];

    if (child[node].empty()) {
        dp[node][h1][h2] = PI * R[node] * R[node];
        if (h2 > 0) {
            dp[node][h1][h2] = -dp[node][h1][h2];
        }
    } else {
        dbl val1 = (h1 == 0 ? 1 : -1) * PI * R[node] * R[node];
        dbl val2 = (h2 == 0 ? 1 : -1) * PI * R[node] * R[node];
        for (const int v: child[node]) {
            val1 += solve(v, !h1, h2);
            val2 += solve(v, h1, !h2);
        }

        dp[node][h1][h2] = max(val1, val2);
    }

    done[node][h1][h2] = true;
    return dp[node][h1][h2];
}

bool surrounds(const int i, const int j) {
    if (R[i] <= R[j]) return false;

    return norm(A[i] - A[j]) < R[i] * R[i];
}

int par[MN];
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        ll px, py;
        cin >> px >> py >> R[i];
        A[i] = pt(px, py);
    }

    fill(par, par+N, -1);
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (i == j) continue;

            if (surrounds(i, j) && (par[j] == -1 || R[i] < R[par[j]])) {
                par[j] = i;
            }
        }
    }

    vector<int> roots;
    for (int i=0; i<N; ++i) {
        if (par[i] == -1) roots.push_back(i);
        else child[par[i]].insert(i);
    }

    dbl ans = 0;
    for (const int root: roots) {
        ans += solve(root, 0, 0);
    }

    cout << fixed << setprecision(12);
    cout << ans << endl;
}
