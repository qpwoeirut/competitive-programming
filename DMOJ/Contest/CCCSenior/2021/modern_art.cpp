//modern_art.cpp created at 02/26/21 18:02:45

#include <bits/stdc++.h>

using namespace std;

const int MN = 5000006;

int N, M, K;
bool row[MN], col[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;
    for (int i=0; i<K; ++i) {
        char c;
        int x;
        cin >> c >> x;

        --x;
        if (c == 'R') row[x] = !row[x];
        if (c == 'C') col[x] = !col[x];
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            ans += row[i] ^ col[j];
        }
    }

    cout << ans << '\n';
}
