//building_skyscrapers2.cpp created at 09/13/20 13:07:40

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;
typedef pair<ll,ll> pll;

const ll MN = 11;
const ll MV = 13;

ll N, T;
pll A[MN];

bool used[MN];
int order[MN];
int ans[MN];
bool grid[MV][MV];

int chr[8] = {1, 1, 1, 0, -1, -1, -1, 0};
int chc[8] = {1, 0, -1, 1, 1, 0, -1, -1};

bool V[MV][MV];
bool reach(int r, int c) {
    for (int i=0; i<MV; ++i) {
        for (int j=0; j<MV; ++j) {
            V[i][j] = false;
        }
    }
    queue<pll> q;
    q.push(pll(r, c));
    V[r][c] = true;
    while (q.size() > 0) {
        pll cur = q.front();q.pop();
        if (cur.FI == 0 || cur.FI > N || cur.SE == 0 || cur.SE > N) return true;

        for (int i=1; i<8; i+=2) {
            if (!V[cur.FI + chr[i]][cur.SE + chc[i]] && !grid[cur.FI + chr[i]][cur.SE + chc[i]]) {
                V[cur.FI + chr[i]][cur.SE + chc[i]] = true;
                q.push(pll(cur.FI + chr[i], cur.SE + chc[i]));
            }
        }
    }
    return false;
}

bool check() {
    for (int i=0; i<MV; ++i) {
        for (int j=0; j<MV; ++j) {
            grid[i][j] = false;
        }
    }

    grid[A[order[0]].FI][A[order[0]].SE] = true;
    for (int i=1; i<N; ++i) {
        bool con = false;
        for (int j=0; j<8; ++j) {
            if (grid[A[order[i]].FI + chr[j]][A[order[i]].SE + chc[j]]) con = true;
        }

        if (!con || !reach(A[order[i]].FI, A[order[i]].SE)) {
            return false;
        }
        grid[A[order[i]].FI][A[order[i]].SE] = true;
    }
    return true;
}

void perm(int idx) {
    for (int i=0; i<N; i++) {
        order[i] = i;
    }
    while (!check()) {
        random_shuffle(order, order+N);
    }
    copy(order, order+N, ans);
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T;
    pll r(1e9, -1e9), c(1e9,-1e9);
    for (int i=0; i<N; ++i) {
        cin >> A[i].FI >> A[i].SE;
        r.FI = min(r.FI, A[i].FI);
        r.SE = max(r.SE, A[i].FI);
        c.FI = min(c.FI, A[i].SE);
        c.SE = max(c.SE, A[i].SE);
    }
    if (r.SE - r.FI >= N || c.SE - c.FI >= N) {
        cout << "NO" << endl;
        return 0;
    }for (int i=0; i<N; ++i) {
        bool ok= false;
        for (int j=0; j<N; ++j) {
            if (i == j) continue;
            if (abs(A[i].FI - A[j].FI) < 2 && abs(A[i].SE - A[j].SE) < 2) {
                ok = true;
            }
        }
        if (!ok) {
        }
    }
    for (int i=0; i<N; i++) {
        A[i].FI -= r.FI - 1;
        A[i].SE -= c.FI - 1;
    }

    ans[0] = -1;
    perm(0);

    if (ans[0] == -1) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    for (int i=0; i<N; ++i) {
        cout << ans[i] + 1 << endl;
    }
}
