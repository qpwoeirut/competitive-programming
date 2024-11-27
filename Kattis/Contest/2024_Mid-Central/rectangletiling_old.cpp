#include <bits/stdc++.h>

using namespace std;

using i128=__int128;

const int MN = 53;
const i128 INF = (i128)(1) << 110;

string to_string(__int128 n) {
    assert(n >= 0);
    string s = "";
    while (n > 0) {
        s += to_string(n / 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    if (s == "") s = "0";
    return s;
}

i128 W, H, N;
i128 A[MN];

i128 fill_side(i128 n, int p) {
    cerr << "n p: " << to_string(n) << ' ' << p << endl;
    i128 total = 0;
    for (int i=p; i>=0; --i) {
        const int pw = 2 * p - 3 * i;
        i128 req;
        if (pw >= 0) req = n * ((i128)(1) << pw);
        else req = n / ((i128)(1) << pw);

        i128 used = min(req, A[i]);
        cerr << "i n u: " << i << ' ' << to_string(n) << ' ' << to_string(used) << endl;
        A[i] -= used;
        total += used;
        n -= used * (1LL << i);
    }
    if (n > 0) return INF;
    return total;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    long long w, h, n;
    cin >> w >> h >> n;
    W = w, H = h, N = n;
    for (int i=0; i<N; ++i) {
        long long x;
        cin >> x;
        A[i] = x;
    }

    i128 ans = 0;
    for (int p=0; p<N; ++p) {
        if (W & (1LL << p)) {
            W -= 1LL << p;
            ans += fill_side(H, p);
        }
        if (H & (1LL << p)) {
            H -= 1LL << p;
            ans += fill_side(W, p);
        }
        if (ans >= INF) {
            cout << "-1\n";
            return 0;
        }
        cerr << "p: " << p << endl;
        cerr << "A:";
        for (int i=0; i<N; ++i) cerr << ' ' << to_string(A[i]);
        cerr << endl << to_string(W) << ' ' << to_string(H) << endl << endl;
    }
    cout << to_string(ans) << endl;
}
