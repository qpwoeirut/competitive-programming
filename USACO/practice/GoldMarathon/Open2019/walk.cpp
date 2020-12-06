#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 7505;
const ll X = 2019201913;
const ll Y = 2019201949;
const ll MOD = 2019201997;

int calc_dist(int x, int y) {
    if (x > y) swap(x, y);
    return (X * (x+1) + Y * (y+1)) % MOD;
}

int N, K;
bool done[MN];
int dist[MN];
vector<int> mst;

int main() {
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);

    cin >> N >> K;

    fill(done, done+N, false);
    fill(dist, dist+N, MOD);

    dist[0] = 0;
    for (int i=0; i<N; ++i) {
        int idx = -1, val = MOD;
        for (int j=0; j<N; ++j) {
            if (!done[j] && val > dist[j]) {
                val = dist[j];
                idx = j;
            }
        }

        if (val == MOD) break;

        done[idx] = true;

        for (int j=0; j<N; ++j) {
            if (!done[j]) dist[j] = min(dist[j], calc_dist(idx, j));
        }
    }
    sort(dist+1, dist+N);
    cout << dist[N-K+1] << endl;
}
