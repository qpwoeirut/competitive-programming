#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MN = 1005;
const ll INF = 1e18;
const ll BIG = 1e17;
int ct[MN];
bool has_normal[MN];
vector<ll> add[MN], mult[MN];

ll lo[MN], hi[MN];

void solve() {
    ll N;
    cin >> N;

    for (int i=0; i<N; ++i) {
        add[i].clear();
        mult[i].clear();

        cin >> ct[i];
        for (int j=0; j<ct[i]; ++j) {
            string s;
            int x;
            cin >> s >> x;
            if (s == "ADD") add[i].push_back(x);
            else if (s == "SUB") add[i].push_back(-x);
            else if (s == "MLT") mult[i].push_back(x);
            else assert(0);
        }
    }

    for (int i=0; i<N; ++i) {
        lo[i] = INF;
        hi[i] = -INF;
        has_normal[i] = add[i].size() > 0;
        for (int m: mult[i]) has_normal[i] |= m > 0;
    }

    bool can_flip = false;
    lo[0] = hi[0] = 1;
    lo[N] = INF;
    hi[N] = -INF;
    for (int i=0; i<N; ++i) {
        for (int a: add[i]) {
            if (a > 0) {
                lo[i+1] = min(lo[i+1], lo[i] + a);
                hi[i+1] = INF;
            } else if (a < 0) {
                lo[i+1] = -INF;
                hi[i+1] = max(hi[i+1], hi[i] + a);
            } else {
                lo[i+1] = min(lo[i], lo[i+1]);
                hi[i+1] = max(hi[i], hi[i+1]);
            }
        }
        for (int m: mult[i]) {
            if (m > 1) {
                if (lo[i] < 0) lo[i+1] = -INF;
                else lo[i+1] = min(lo[i+1], lo[i] * m);

                if (hi[i] > 0) hi[i+1] = INF;
                else hi[i+1] = max(hi[i+1], hi[i] * m);
            } else if (m == 1) {
                lo[i+1] = min(lo[i], lo[i+1]);
                hi[i+1] = max(hi[i], hi[i+1]);
            } else if (m == -1) {
                lo[i+1] = min(lo[i+1], -hi[i]);
                hi[i+1] = max(hi[i+1], -lo[i]);
            } else if (m < -1) {
                if (has_normal[i]) can_flip = true;

                if (hi[i] > 0) lo[i+1] = -INF;
                else lo[i+1] = min(lo[i+1], hi[i] * m);

                if (lo[i] < 0) hi[i+1] = INF;
                else hi[i+1] = max(hi[i+1], lo[i] * m);
            } else assert(0);
        }
        //cerr << i << ' ' << lo[i] << ' ' << hi[i] << endl;
    }

    //cerr << lo[N] << ' ' << hi[N] << ' ' << can_flip << endl;
    bool ans = hi[N] >= BIG || (can_flip && lo[N] <= BIG);
    cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--> 0) {
        solve();
    }
}
/*
2
1
ADD 1
1
MLT -1

2
1
SUB 1
1
MLT -1

2
2
ADD 1
SUB 1
1
MLT -1

1
1
MLT 2

1
1
MLT -2
*/
