#include <bits/stdc++.h>

using namespace std;

const int MN = 20;
const int MX = 1000;

int A[MN];
int solve(int N) {
    int mn = -1000000000, mx = 1000000000;
    int a = 0;
    for (int i=0; i<N; ++i) {
        int m = A[i];
        if (i % 2 == 0) {
            mx = min(mx, m - a);
            a = 2 * m - a;
        } else {
            mn = max(mn, a - m);
            a = 2 * m - a;
        }
    }

    return max(0, mx - mn + 1);
}

int brute(int N) {
    int ans = 0;
    for (int x=-MX; x<=MX; ++x) {
        int pre = x;
        bool ok = true;
        for (int i=0; i<N; ++i) {
            const int cur = 2 * A[i] - pre;
            if (pre > cur) {
                ok = false;
                break;
            }
            pre = cur;
        }

        if (ok) ++ans;
    }
    return ans;
}

void test() {
    mt19937 rng(8);
    for (int N=2; N<=MN; ++N) {
        cerr << N << endl;
        for (int t=0; t<100000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = rng() % MX;
            }

            int sans = solve(N);
            int bans = brute(N);

            if (sans != bans) {
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    cout << A[i] << " \n"[i + 1 == N];
                }
                cout << sans << ' ' << bans << endl;
            }
            assert(sans == bans);
        }
    }
}

int main() {
    //test(); return 0;

    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;

    int mn = -1000000000, mx = 1000000000;

    int a = 0;
    for (int i=0; i<N; ++i) {
        int m;
        cin >> m;

        if (i % 2 == 0) {
            // s_i + s_{i+1} = 2m => s_{i+1} = 2m - s_i
            // s_i ≤ 2m - s_i
            // s_0 + a ≤ 2m - s_0 - a
            // 2s_0 ≤ 2m - 2a
            // s_0 ≤ m - a
            mx = min(mx, m - a);

            // s_i = s_0 + a
            // s_{i+1} = 2m - s_i = 2m - s_0 - a = (2m - a) - s_0
            a = 2 * m - a;
        } else {
            // s_i + s_{i+1} = 2m => s_{i+1} = 2m - s_i
            // s_i ≤ 2m - s_i
            // a - s_0 ≤ 2m - a + s_0
            // 2a - 2m ≤ 2s_0
            // a - m ≤ s_0
            mn = max(mn, a - m);

            // s_i = a - s_0
            // s_{i+1} = 2m - s_i = 2m - a + s_0 = (2m - a) + s_0
            a = 2 * m - a;
        }
    }

    cout << max(0, mx - mn + 1) << '\n';
}
