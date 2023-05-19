#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using pll=pair<ll,ll>;

const int MN = 100005;
const ll MOD = 1e9 + 7;
const ll inv2 = 500000004;

int U;
ll D[MN], B[MN], diff[MN];
int answer[MN];

ll sum(const ll a, const ll n) {
    return ((((n % MOD) * ((2*a + n - 1) % MOD)) % MOD) * inv2) % MOD;  // n * (2a + n - 1) / 2
}

void brute() {
    map<ll, ll> intervals;
    for (int i=0; i<U; ++i) {
        intervals[D[i]] = B[i];

        ll ans = 0;
        ll d = 0;
        for (const auto& interval: intervals) {
            d = max(d, interval.first);
            ans += sum(d, interval.second);
            d += interval.second;
        }
        answer[i] = ans % MOD;
    }
}

void solve() {
    map<ll, ll> intervals;
    for (int i=0; i<U; ++i) {
        const ll cur = intervals[D[i]];
        diff[i] = B[i] - cur;
        intervals[D[i]] = B[i];
    }

    map<ll, ll> fed, fed_end;
    ll ans = 0;
    for (int i=0; i<U; ++i) {
        ll bales = diff[i];
        ll start = D[i];
        auto end_it = fed_end.lower_bound(D[i]);
        if (end_it != fed_end.end()) {
            auto it = fed.find(end_it->first - end_it->second);
            assert(it != fed.end());

            start = min(D[i], it->first);
            while (it != fed.end() && start + bales >= it->first) {
                //cerr << i << ' ' << start << ' ' << bales << ' ' << it->first << ' ' << it->second << endl;
                bales += it->second;
                ans -= sum(it->first, it->second);

                fed_end.erase(it->first + it->second);
                it = fed.erase(it);
            }
        }

        ans += sum(start, bales);

        fed.emplace(start, bales);
        fed_end.emplace(start + bales, bales);

        ans %= MOD;
        if (ans < 0) ans += MOD;
        answer[i] = ans;
    }
}

int cpy[MN];
bool check_match() {
    brute();
    copy(answer, answer+U, cpy);
    solve();

    for (int i=0; i<U; ++i) {
        if (answer[i] != cpy[i]) return false;
    }
    return true;
}

void test() {
    mt19937 rng(8);
    const int D_max = 15;
    for (U=1; U<=D_max - 2; ++U) {
        cout << U << endl;
        for (int t=0; t<100000; ++t) {
            map<int, int> cur;
            for (int i=0; i<U; ++i) {
                int d, b;
                do {
                    d = rng() % D_max;
                    b = rng() % D_max;
                } while (cur[d] >= b);
                cur[d] = b;
                D[i] = d;
                B[i] = b;
            }
            if (!check_match()) {
                cout << U << '\n';
                for (int i=0; i<U; ++i) {
                    cout << D[i] << ' ' << B[i] << '\n';
                }
                for (int i=0; i<U; ++i) {
                    cout << cpy[i] << ' ';
                }
                cout << '\n';
                for (int i=0; i<U; ++i) {
                    cout << answer[i] << ' ';
                }
                cout << endl;
                assert(0);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> U;
    for (int i=0; i<U; ++i) {
        cin >> D[i] >> B[i];
    }

    //solve();
    if (U <= 5000) brute();
    else solve();

    for (int i=0; i<U; ++i) {
        cout << answer[i] << '\n';
    }
}
/*
2
1 6
3 1
21 28

2
1 2
2 1
3 6

2
2 1
1 1
2 3
*/
