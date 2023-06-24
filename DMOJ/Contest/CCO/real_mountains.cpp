//real_mountains.cpp created at 06/15/23 20:57:50

#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pii=pair<int,int>;

const int MN = 1001001;
const int MOD = 1e6 + 3;
const int INF = 1001001001;

int N;
int A[MN];
pii B[MN];

int target[MN];

int pn;
int st[MN * 4];
void build() {
    pn = N - 1; pn |= pn >> 1; pn |= pn >> 2; pn |= pn >> 4; pn |= pn >> 8; pn |= pn >> 16; ++pn;

    for (int i=0; i<pn; ++i) {
        st[pn+i] = (i < N) ? A[i] : INF;
    }
    for (int i=pn-1; i>0; --i) {
        st[i] = min(st[i << 1], st[(i << 1) + 1]);
    }
}
void _upd(int node, int l, int r, int i, int x) {
    if (l > i || i >= r) return;
    if (l == i && i+1 == r) {
        st[node] = x;
        return;
    }

    const int mid = (l + r) / 2;
    _upd((node << 1),     l, mid, i, x);
    _upd((node << 1) + 1, mid, r, i, x);

    st[node] = min(st[node << 1], st[(node << 1) + 1]);
}
void upd(int i, int x) { _upd(1, 0, pn, i, x); }

int _query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return st[node];
    if (qr <= l || r <= ql) return INF;
    
    const int mid = (l + r) / 2;
    return min(_query((node << 1),     l, mid, ql, qr),
               _query((node << 1) + 1, mid, r, ql, qr));
}
int query(int ql, int qr) { return _query(1, 0, pn, ql, qr); }

ll ssum(ll a, ll b) {
    return (b - a) * (a + b - 1) / 2;
}

void calc_target() {
    copy(A, A+N, target);
    const int peak = max_element(A, A+N) - A;
    for (int i=1; i<peak; ++i) {
        target[i] = max(target[i-1], target[i]);
    }
    for (int i=N-2; i>peak; --i) {
        target[i] = max(target[i], target[i+1]);
    }
}

int solve() {
    calc_target();

    for (int i=0; i<N; ++i) {
        B[i] = pii(A[i], i);
    }
    sort(B, B+N);

    priority_queue<pii, vector<pii>, greater<pii>> targets;
    for (int i=0; i<N; ++i) {
        targets.emplace(A[i], i);
        targets.emplace(target[i], i);
    }

    build();

    ll cost = 0;
    set<int> moving;
    while (targets.size() > 0) {
        int cur = targets.top().first;
        while (targets.size() > 0 && targets.top().first == cur) {
            int idx = targets.top().second;
            targets.pop();

            if (!moving.count(idx)) {
                moving.insert(idx);
                upd(idx, INF);
                assert(cur == A[idx]);
            } else {
                moving.erase(idx);
                assert(cur == target[idx]);
            }
        }

        if (targets.empty() || moving.empty()) continue;

        int nxt = targets.top().first;

        int idx_l = *moving.begin(), idx_r = *moving.rbegin();
        int min_l = query(0, idx_l) % MOD, min_r = query(idx_r + 1, N) % MOD;

        //cerr << cur << "->" << nxt << ' ' << idx_l << ',' << idx_r << ' ' << min_l << ',' << min_r << endl << "moving:";
        //for (int x: moving) cerr << ' ' << x;
        //cerr << endl;

        const ll S = ssum(cur, nxt) % MOD;
        const ll n = (nxt - cur) % MOD;
        if (moving.size() == 1) {
            //for (int i=cur; i<nxt; ++i) {
            //    cost += min_l + i + min_r;
            //}
            cost += n * (min_l + min_r) + S;
        } else {
            const ll M = query(0, N) % MOD;
            //for (int i=cur; i<nxt; ++i) {
            //    cost += min_l + i + min_r;
            //    cost += M + i + (i + 1);
            //    cost += ((i + 1) + i + (i + 1)) * (moving.size() - 2);
            //}  ==> cost += min_l + min_r + min(min_l, min_r) + 3i + 1 + (3i + 2) * (sz - 2)
            cost += n * (min_l + min_r + M + 1) + 3*S + (3*S + 2*n) * (moving.size() - 2);
        }

        cost %= MOD;
    }
    assert(moving.empty());

    return cost;
}

int arr[MN];
int brute() {
    copy(A, A+N, arr);
    calc_target();

    ll cost = 0;
    while (true) {
        vector<int> idxs;
        int val = INF;
        for (int i=0; i<N; ++i) {
            if (arr[i] != target[i]) {
                if (val > arr[i]) {
                    val = arr[i];
                    idxs.clear();
                }
                if (val == arr[i]) {
                    idxs.push_back(i);
                }
            }
        }

        if (idxs.empty()) break;

        int cost_l = INF, cost_r = INF;
        for (int i=0; i<idxs[0]; ++i) {
            if (arr[i] > val) cost_l = min(cost_l, arr[i]);
        }
        for (int i=idxs.back() + 1; i<N; ++i) {
            if (arr[i] > val) cost_r = min(cost_r, arr[i]);
        }

        int idx = cost_l >= cost_r ? idxs[0] : idxs.back();
        for (int i=0; i<idx; ++i) {
            if (arr[i] > val) cost_l = min(cost_l, arr[i]);
        }
        for (int i=idx+1; i<N; ++i) {
            if (arr[i] > val) cost_r = min(cost_r, arr[i]);
        }
        cost += cost_l + arr[idx] + cost_r;
        ++arr[idx];

        cost %= MOD;
    }

    return cost;
}

void test() {
    mt19937 rng(8);

    for (N=3; N<=9; ++N) {
        cerr << N << endl;
        for (int t=0; t<1000000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = (rng() % 100) + 1;
            }

            int bans = brute();
            int sans = solve();
            if (bans != sans) {
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    if (i) cout << ' ';
                    cout << A[i];
                }
                cout << endl << endl;
                cout << bans << ' ' << sans << endl;
            }
            assert(bans == sans);
        }
    }
}

int main() {
    //test(); return 0;

    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    cout << solve() << '\n';
    //cout << brute() << '\n';
}

/*
4
2 1 1 5

4
3 1 1 3

5
3 1 2 1 3
*/

// maintain set of indices being moved
// min of left + min of right + min of left and right
