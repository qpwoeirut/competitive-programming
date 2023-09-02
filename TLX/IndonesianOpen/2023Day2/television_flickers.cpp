//television_flickers.cpp created at 08/31/23 16:42:55

#include <bits/stdc++.h>

using namespace std;

const int MN = 200000;
int down[MN];
int up[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n_down = 0, n_up = 0;

    int N, P;
    cin >> N >> P;
    for (int i=0; i<P; ++i) {
        int t, w;
        cin >> t >> w;
        if (t == 1) up[n_up++] = w;
        else down[n_down++] = w;
    }

    sort(down, down+n_down);
    sort(up, up+n_up, greater<int>());

    int Q;
    cin >> Q;
    for (int q=0; q<Q; ++q) {
        int x, y;
        cin >> x >> y;

        const int lo = min(x, y);
        const int hi = max(x, y);

        const int down_ct = upper_bound(down, down+n_down, lo) - down;
        const int up_ct = upper_bound(up, up+n_up, hi, greater<int>()) - up;

        const int ans = (down_ct + up_ct) & 1;
        cout << ans << '\n';
    }

    //for (int i=0; i<n_down; ++i) cerr << down[i] << ' ';
    //cerr << endl;
    //for (int i=0; i<n_up; ++i) cerr << up[i] << ' ';
    //cerr << endl;
}

