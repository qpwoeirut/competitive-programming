#include <bits/stdc++.h>

using namespace std;

void start() {
    cout << "0000\n";
}

const int BASE = 21;
static_assert(BASE * BASE * BASE < 10000);

const auto END_TIME = chrono::high_resolution_clock::now() + 80ms;
void observe() {
    const auto now = chrono::high_resolution_clock::now().time_since_epoch();
    const uint64_t seed = chrono::duration_cast<chrono::nanoseconds>(now).count();
    mt19937 rng(seed);
    int n;
    cin >> n;
    char c;
    cin >> c;

    int br = n % BASE;
    n /= BASE;
    int si = n % BASE;
    n /= BASE;
    int go = n % BASE;
    assert(n < BASE);

    bool add = (rng() % 100) < 9;
    if (add) {
        if (c == 'B') ++br;
        if (c == 'S') ++si;
        if (c == 'G') ++go;
    }

    br = min(br, BASE - 1);
    si = min(si, BASE - 1);
    go = min(go, BASE - 1);

    n = ((go * BASE) + si) * BASE + br;
    string s = to_string(n);
    while (s.size() < 4) s = '0' + s;

    cout << s << '\n';
}

void answer() {
    int n;
    cin >> n;

    int br = n % BASE;
    n /= BASE;
    int si = n % BASE;
    n /= BASE;
    int go = n % BASE;
    assert(n < BASE);

    pair<int, char> vals[3] = {{br, 'B'}, {si, 'S'}, {go, 'G'}};
    sort(vals, vals + 3);
    cout << vals[0].second << vals[1].second << vals[2].second << '\n';
    cerr << vals[0].first << ' ' << vals[1].first << ' ' << vals[2].first << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string S;
    cin >> S;

    if (S == "START") start();
    else if (S == "OBSERVE") observe();
    else if (S == "ANSWER") answer();
    else assert(0);

    while (chrono::high_resolution_clock::now() < END_TIME);
    // try to make times vary
}
