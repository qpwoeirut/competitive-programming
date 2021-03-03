//math_homework.cpp created at 02/26/21 19:40:36

#include <bits/stdc++.h>

using namespace std;

struct Item {
    int lo, hi;
    int val;
};

const int MN = 150005;
const int INIT = 720720;

int N, M;
int A[MN];
Item req[MN];

Item tree[MN << 2];

void build() {
    int PN = N-1; PN |= PN >> 1; PN |= PN >> 2; PN |= PN >> 4; PN |= PN >> 8; PN |= PN >> 16; ++PN;

    for (int i=0; i<PN; ++i) {
        tree[PN+i].lo = i;
        tree[PN+i].hi = i+1;
        tree[PN+i].val = i < N ? A[i] : INIT;
    }
    for (int i=PN-1; i>0; --i) {
        tree[i].lo = tree[i << 1].lo;
        tree[i].hi = tree[(i << 1) + 1].hi;
        tree[i].val = gcd(tree[i << 1].val, tree[(i << 1) + 1].val);
    }
}

int query(const int node, const int lo, const int hi) {
    if (hi <= tree[node].lo || tree[node].hi <= lo) return INIT;
    if (lo <= tree[node].lo && tree[node].hi <= hi) return tree[node].val;

    return gcd(query(node << 1, lo, hi), query((node << 1) + 1, lo, hi));
}

int ct[17];
int get_lcm() {
    int x = 1;
    for (int i=1; i<=16; ++i) {
        if (ct[i]) {
            x = (x * i) / gcd(x, i);
        }
    }
    
    return x;
}

int change[MN][17];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        cin >> req[i].lo >> req[i].hi >> req[i].val;
        --req[i].lo;
        ++change[req[i].lo][req[i].val];
        --change[req[i].hi][req[i].val];
    }

    for (int i=0; i<N; ++i) {
        for (int j=1; j<=16; ++j) {
            ct[j] += change[i][j];
        }

        A[i] = get_lcm();
    }

    build();

    for (int i=0; i<M; ++i) {
        int x = query(1, req[i].lo, req[i].hi);
        if (x != req[i].val) {
            cout << "Impossible" << endl;
            return 0;
        }
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << endl;
}

