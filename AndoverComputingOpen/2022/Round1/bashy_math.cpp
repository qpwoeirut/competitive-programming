// got this wrong because I can't read (statement specifies *ordered* pairs but mine calculates *unordered* pairs)

#include <bits/stdc++.h>

using namespace std;

using ll=long long;

constexpr int MN = 200005;
constexpr int MX = 500005;

int N;
int A[MN];

int ct[MX];

ll solve() {
    ll ans = 0;
    sort(A, A+N);
    fill(ct, ct+MX, 0);

    for (int i=0; i<N; ++i) {
        for (int a=1; a*a<=A[i]; ++a) {
            if (A[i] % a == 0) {
                ans += ct[a];
                if (a*a != A[i]) {
                    ans += ct[A[i] / a];
                }
            }
        }
        ++ct[A[i]];
    }
    return ans;
}

ll brute() {
    ll ans2 = 0;
    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<N; ++j) {
            if (A[i] % A[j] == 0 || A[j] % A[i] == 0) ++ans2;
        }
    }
    return ans2;
}

const int inf = 0x3f3f3f3f, mod = 1e9 + 7, maxn = 5e5 + 5;
const long long INFL = 0x3f3f3f3f3f3f3f3f;
long long sieve[maxn];
ll izhang() {
    fill(sieve, sieve+maxn, 0);
    map<int, int> occ;
    for (int i = 0; i < N; ++i) {
        ++occ[A[i]];
    }
    long long sol = 0;
    for (auto &i : occ) {
        sol += (long long) (i.second) * (i.second - 1);
        sol += sieve[i.first] * i.second;
        for (int j = i.first; j < maxn; j += i.first) {
            sieve[j] += i.second;
        }
    }
    return sol;
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=20; ++N) {
        for (int t=0; t<10000; ++t) {
            cout << N << ' ' << t << endl;
            for (int i=0; i<N; ++i) {
                A[i] = (rng() % 50) + 1;
            }
            ll a = solve();
            ll b = izhang();
            if (a != b) {
                cout << a << ' ' << b << endl;
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    cout << A[i] << ' ';
                } cout << endl;
            }
            assert(a == b);
        }
    }
}

int main() {
    test(); return 0;
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    //ll ans = solve();
    ll ans = brute();
    cout << ans << '\n';
}
