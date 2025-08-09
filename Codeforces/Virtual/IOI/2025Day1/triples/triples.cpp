#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;

int check(const vi& H, int a, int c) {
    int ans = 0;
    if (a < 0 || a >= H.size() || c < 0 || c >= H.size()) return ans;

    int d = H[a] == c - a ? H[c] : H[a];
    int b1 = a + d;
    if (b1 < H.size() && H[b1] == c - b1) ++ans;

    int b2 = c - d;
    if (b1 != b2 && 0 <= b2 && H[b2] == b2 - a) ++ans;

    return ans;
}

ll count_triples(vi H) {
    ll ans = 0;

    ll mx = *max_element(H.begin(), H.end());

    for (int i=0; i<H.size(); ++i) {
        ans += check(H, i, i + H[i]) + check(H, i - H[i], i);

        if (H.size() <= 2000 || mx <= 10) {
            for (int j=max(0, i - H[i] + 1); j<i && j+H[i] < H.size(); ++j) {
                ans += (i - j == H[j] && j + H[i] - i == H[j + H[i]]) || (i - j == H[j + H[i]] && j + H[i] - i == H[j]);
            }
        }
    }

    return ans;
}

vi construct_range(int M, int K) {
    vi H(M);
    for (int i=0; i<M; ++i) {
        H[i] = 1 + (i % 3 == 0);
    }
    return H;
}
