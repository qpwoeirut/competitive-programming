#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int MN = 100005;

int N;
int A[MN];
pii pos[MN];

int BIT[MN];
void inc(int idx) {
    for (; idx<=N; idx+=(idx & -idx)) ++BIT[idx];
}
ll query(int idx) {
    ll ret = 0;
    for (; idx>0; idx-=(idx & -idx)) ret += BIT[idx];
    return ret;
}


int main() {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    fill(pos, pos+MN, pii(-1, -1));

    cin >> N;
    N <<= 1;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
        if (pos[A[i]].first == -1) {
            pos[A[i]].first = i;
        } else {
            pos[A[i]].second = i;
        }
    }

    ll ans = 0, removed = 0;
    for (int i=1; i<=N; ++i) {
        if (pos[A[i]].second == i) {
            ll before = query(pos[A[i]].first);
            ll cur = removed - before;
            ll between = pos[A[i]].second - pos[A[i]].first - 1;
            ans += between - cur;

            //cerr << "A, before,removed,cur,between: " << A[i] << ' ' << before << ' ' << removed << ' ' << cur << ' ' << between << endl;
            inc(pos[A[i]].first);
            inc(pos[A[i]].second);
            removed += 2;
        } else assert(pos[A[i]].first == i);
    }

    cout << ans << endl;
}

