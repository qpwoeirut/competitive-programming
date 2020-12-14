#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;
typedef long long ll;

const int MN = 100005;

int N;
int A[MN];

int BIT[MN];
void inc(int idx) {
    for (; idx<=N+1; idx+=(idx&-idx)) ++BIT[idx];
}
int query(int idx) {
    int ret = 0;
    for (; idx>0; idx-=(idx&-idx)) ret += BIT[idx];
    return ret;
}

pii order[MN];
ll ans[MN];
int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        ++A[i];
        order[i] = pii(A[i], i + 1);
    }
    sort(order, order+N, greater<pii>());

    for (int i=0; i<N; ++i) {
        const int val = order[i].fi;
        const int idx = order[i].se;
        ans[val+1] += query(idx);
        inc(idx);
    }

    for (int i=1; i<=N; ++i) {
        ans[i] += ans[i-1];
        cout << ans[i] << '\n';
    }
}
