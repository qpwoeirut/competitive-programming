//osumnjiceni.cpp created at 12/23/21 18:22:00

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

using pii=pair<int,int>;

const int MN = 200005;
const int LG = 19;

int N, Q;
pii A[MN];
pii query[MN];

int sparse[LG][MN];

bool conflict(const multiset<pii>& cur, const multiset<pii>::iterator& it) {
    if (it != cur.begin()) {
        auto before = it; --before;
        if (before->se > it->fi) return true;
    }
    auto after = it; ++after;
    return after != cur.end() && it->se > after->fi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].fi >> A[i].se;
        ++A[i].se;
    }
    cin >> Q;
    for (int i=0; i<Q; ++i) {
        cin >> query[i].fi >> query[i].se;
        --query[i].fi;
    }

    multiset<pii> cur;
    int slow = 0;
    for (int fast=0; fast<N; ++fast) {
        auto it = cur.insert(A[fast]);
        while (conflict(cur, it)) {
            sparse[0][slow] = fast;
            cur.erase(cur.find(A[slow]));
            ++slow;
        }
    }
    for (; slow<=N; ++slow) sparse[0][slow] = N;


    for (int i=1; i<LG; ++i) {
        for (int j=0; j<=N; ++j) {
            sparse[i][j] = sparse[i-1][sparse[i-1][j]];
        }
    }

    //for (int i=0; i<LG; ++i) { for (int j=0; j<N; ++j) { cerr << sparse[i][j] << ' '; } cerr << endl; }

    for (int i=0; i<Q; ++i) {
        int p = query[i].fi, q = query[i].se;
        int ans = 0;
        for (int j=LG-1; j>=0; --j) {
            if (sparse[j][p] < q) {
                p = sparse[j][p];
                ans += 1 << j;
            }
        }
        assert(sparse[0][p] >= q);
        ++ans;

        cout << ans << '\n';
    }
}
