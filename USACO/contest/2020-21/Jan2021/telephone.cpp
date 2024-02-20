#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 50004;
const int MK = 55;
const int INIT = 1e18;

int N, K;
int A[MN];
int dist[MN];
bool S[MK][MN];

int best[MK];

void chmn(int& a, const int b) {if (a>b) a=b;}

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        --A[i];
    }
    for (int i=0; i<K; ++i) {
        for (int j=0; j<K; ++j) {
            char c;
            cin >> c;
            S[i][j] = c == '1';
        }
    }

    fill(dist, dist+MN, INIT);
    dist[0] = 0;
    for (int k=0; k<=K; ++k) {
        fill(best, best+K, INIT);
        for (int i=0; i<N; ++i) {
            for (int j=0; j<K; ++j) {
                if (S[j][A[i]]) {
                    chmn(dist[i], best[j]);
                }
            }
            chmn(best[A[i]], dist[i]);
        }

        //for (int i=0; i<N; ++i) { cerr << dist[i] << ' '; } cerr << endl;

        fill(best, best+K, INIT);
        for (int i=N-1; i>=0; --i) {
            for (int j=0; j<K; ++j) {
                if (S[j][A[i]]) {
                    chmn(dist[i], best[j] - i);
                }
            }
            chmn(best[A[i]], dist[i] + i);
        }
        //for (int i=0; i<N; ++i) { cerr << dist[i] << ' '; } cerr << endl;
    }

    assert(dist[N-1] >= 0);
    if (dist[N-1] >= INIT / 2) {
        cout << -1 << endl;
    } else {
        assert(dist[N-1] < INIT/2);
        cout << N - 1 + (2 * dist[N-1]) << endl;
    }
}
