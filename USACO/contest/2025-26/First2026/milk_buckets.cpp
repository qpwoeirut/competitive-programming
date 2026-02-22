#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MN = 200005;

int N;
int A[MN];

int BIT[MN];
void upd(int idx, int inc) {
    for (++idx; idx<MN; idx+=idx&-idx) BIT[idx] += inc;
}
int query(int idx) {
    int ret = 0;
    for (++idx; idx>0; idx-=idx&-idx) ret += BIT[idx];
    return ret;
}

void solve() {
    fill(BIT, BIT+MN, 0);
    for (int i=0; i<N; ++i) {
        upd(i, 1);
    }

    map<int, deque<int>> pos;
    for (int i=0; i<N; ++i) {
        pos[A[i]].push_back(i);
    }

    ll ans = 0;
    int remaining = N;
    for (auto it = pos.rbegin(); it != pos.rend(); ++it) {
        while (it->second.size() > 0) {
            int left = query(it->second.front()) - 1;
            int right = remaining - query(it->second.back());

            if (left < right) {
                ans += left;
                upd(it->second.front(), -1);
                it->second.pop_front();
            } else {
                ans += right;
                upd(it->second.back(), -1);
                it->second.pop_back();
            }
            --remaining;
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T --> 0) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }

        solve();
    }
}
