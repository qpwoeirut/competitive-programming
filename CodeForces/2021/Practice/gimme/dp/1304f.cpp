//1304f.cpp created at 01/23/21 11:20:28

#include <bits/stdc++.h>

using namespace std;

const int MN = 55;
const int MM = 20004;
const int INIT = 1001001001;

int N, M, K;
int PM;
int G[MN][MM];
int dp[MN][MM];

struct Node {
    int lo, hi;
    int mx;
    int lazy;
};

Node tree[MM << 2];

void build(const int row) {
    for (int i=0; i<PM; ++i) {
        tree[PM + i].lo = i;
        tree[PM + i].hi = i+1;
        tree[PM + i].mx = i < M ? dp[row][i] : 0;
        tree[PM + i].lazy = 0;
    }
    for (int i=PM-1; i>=0; --i) {
        tree[i].lo = tree[i << 1].lo;
        tree[i].hi = tree[(i << 1) + 1].hi;
        tree[i].mx = max(tree[i << 1].mx, tree[(i << 1) + 1].mx);
        tree[i].lazy = 0;
    }
}

void prop(const int node) {
    tree[node << 1].lazy += tree[node].lazy;
    tree[node << 1].mx += tree[node].lazy;

    tree[(node << 1) + 1].lazy += tree[node].lazy;
    tree[(node << 1) + 1].mx += tree[node].lazy;

    tree[node].lazy = 0;
}

void update(const int node, const int lo, const int hi, const int val) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return;
    if (lo <= tree[node].lo && tree[node].hi <= hi) {
        tree[node].lazy += val;
        tree[node].mx += val;
        return;
    }

    prop(node);
    update(node << 1, lo, hi, val);
    update((node << 1) + 1, lo, hi, val);

    tree[node].mx = max(tree[node << 1].mx, tree[(node << 1) + 1].mx);
}

int query(const int node, const int lo, const int hi) {
    if (tree[node].hi <= lo || hi <= tree[node].lo) return 0;
    if (lo <= tree[node].lo && tree[node].hi <= hi) return tree[node].mx;

    prop(node);
    return max(query(node << 1, lo, hi), query((node << 1) + 1, lo, hi));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;
    for (int i=1; i<=N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
        }
    }

    PM = M-1; PM |= PM >> 1; PM |= PM >> 2; PM |= PM >> 4; PM |= PM >> 8; PM |= PM >> 16; ++PM;

    int ans = 0;
    for (int i=1; i<=N; ++i) {
        build(i-1);
        int sum = 0;
        for (int j=0; j<K; ++j) {
            sum += G[i][j] + G[i+1][j];
            update(1, 0, j+1, -G[i][j]);
        }
        for (int j=0; j<M; ++j) {
            //cerr << i << ' ' << j << ' ' << query(1, 0, M) << ' ' << sum << endl;
            dp[i][j] = (i > 1 ? query(1, 0, M) : 0) + sum;
            sum -= G[i][j] + G[i+1][j];
            update(1, max(0, j-K+1), j+1, G[i][j]);
            if (j+K < M) {
                sum += G[i][j+K] + G[i+1][j+K];
                update(1, j+1, j+K+1, -G[i][j+K]);
            }

            ans = max(ans, dp[i][j]);
        }
    }

    //for (int i=0; i<=N; ++i) { for (int j=0; j<M; ++j) { cerr << dp[i][j] << ' '; } cerr << endl; }

    cout << ans << endl;
}
