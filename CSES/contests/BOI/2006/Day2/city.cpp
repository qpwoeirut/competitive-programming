#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using i128=ll;

const int MK = 20005;
ll A[MK];
i128 sum[MK];

ll N, T, K;

const int MB = 7;
ll B[MB];
ll recurse(int idx, ll placed, ll cost) {
    if (idx == MB) {
        if (placed < N) return 9e18;
        ll extra = placed - N;
        ll best = cost;
        for (int i=0; i<MB; ++i) {
            if (4 * (i + 1) >= extra && B[i] > 0) best = min(best, cost - extra * (A[B[i] - 1] + T * i));
        }
        return best;
    }

    ll ct = 4 * (idx + 1);
    ll best = 9e18;
    for (int k=0; k<=K; ++k) {
        B[idx] = k;
        ll new_cost = ct * (sum[k] + T * idx * k);
        ll cur = recurse(idx + 1, placed + ct * k, cost + new_cost);
        best = min(best, cur);
    }

    return best;
}
ll brute() {
    sum[0] = 0;
    for (int i=0; i<K; ++i) {
        sum[i+1] = sum[i] + A[i];
    }
    return recurse(0, 0, 0);
}

ll calculate_floors(i128 d, i128 mx) {
    ll lo = 0, hi = K;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (A[mid - 1] + T * d <= mx) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

ll calculate(i128 mx, i128& cost, bool c) {
    cost = 0;

    ll built = 0;
    for (ll d=0; built<N || c; ++d) {
        i128 ct = 4 * (d + 1);

        ll floors = calculate_floors(d, mx);
        //if (c) cerr << "d=" << d << " ct=" << ct << " floors=" << floors << endl;
        if (floors == 0) break;
        cost += (sum[floors] + T * d * floors) * ct;

        built += ct * floors;
        //if (c) cerr << "built=" << built << " cost=" << cost << endl;
    }

    return built;
}

string to_string(__int128 n) {
    if (n == 0) return "0";
    string s = "";
    while (n > 0) {
        s += to_string((int)(n % 10));
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

i128 solve() {
    sum[0] = 0;
    for (int i=0; i<K; ++i) {
        sum[i+1] = sum[i] + A[i];
    }

    ll lo = 0, hi = 8e18;
    i128 cost;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        ll built = calculate(mid, cost, false);
        if (built < N) lo = mid + 1;
        else hi = mid;
    }

    ll built = calculate(lo, cost, true);
    //cerr << "lo=" << lo << " cost=" << cost << " built=" << built << endl;
    assert(built >= N);

    i128 ans = cost - lo * (i128)(built - N);
    return ans;
}

void test() {
    mt19937 rng(8);

    for (N=4; N<=100; ++N) {
        cerr << "N=" << N << endl;
        for (T=1; T<=100; ++T) {
            for (K=1; K<=5; ++K) {
                for (int i=0; i<K; ++i) {
                    do {
                        A[i] = rng() % 20 + 1;
                    } while (find(A, A+i, A[i]) != A+i);
                }
                sort(A, A+K);

                ll sans = solve();
                ll bans = brute();
                if (sans != bans) {
                    cout << N << ' ' << T << ' ' << K << '\n';
                    for (int i=0; i<K; ++i) cout << A[i] << '\n';
                    cout << sans << ' ' << bans << endl;
                }
                assert(sans == bans);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N >> T >> K;
    for (int i=0; i<K; ++i) {
        cin >> A[i];
    }

    i128 ans = solve();
    //i128 ans = brute();
    cout << to_string(ans) << '\n';
}

/*
10 100 2
1
20

10 10 2
1
20

4000000000 1 1
2000000000

1000000000 500000 1
1000000000

8 1 2
5
16

17 1 4
1
2
13
16
*/
