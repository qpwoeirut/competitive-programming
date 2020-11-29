#include <bits/stdc++.h>

using namespace std;

#define val first
#define idx second

typedef pair<int,int> pii;

const int MN = 100005;

int N;
pii A[MN];
int BIT[MN];

void inc(int idx) {
    for (; idx<=N; idx+=(idx & -idx)) ++BIT[idx];
}
int query(int idx) {
    int ret = 0;
    for (; idx>0; idx-=(idx & -idx)) ret += BIT[idx];
    return ret;
}

int main() {
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].val;
        A[i].idx = i+1;
    }

    sort(A, A+N, greater<pii>());

    int ans = 0;
    for (int i=0; i<N; ++i) {
        int L = query(A[i].idx);
        int R = i - L;

        if (max(L, R) > 2 * min(L, R)) ++ans;
        //cerr << i << ' ' << A[i].val << ' ' << A[i].idx << ' ' << L << ' ' << R << endl;
        
        inc(A[i].idx);
    }

    cout << ans << endl;
}
