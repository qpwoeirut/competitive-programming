// This can only get 9/10
// I spent a few hours trying to constant optimize
// TC 9 is around 1600ms on USACO server but TC 10 still TLEs

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 2003;
const int SHF = 11;
const int SHF2 = 22;
const int AND = (1 << SHF) - 1;

int W, H, N, M;
int A[MN], B[MN];
int dist[MN][MN];
bool in[MN][MN];

ll heap[MN * MN * 4];
int sz = 1;
ll ans = 0;
int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> W >> H >> N >> M;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
    }
    for (int i=1; i<=M; ++i) {
        cin >> B[i];
    }
    ++N; ++M;
    sort(A+1, A+N);
    sort(B+1, B+M);
    A[N] = W;
    B[M] = H;

    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=M; ++j) {
            dist[i][j] = 1001001001;
        }
    }
    
    heap[0] = (1 << SHF) | 1;

    dist[1][1] = 0;

    int ct = N*M;
    while (ct > 0) {
        pop_heap(heap, heap+sz, greater<ll>());
        const ll cur = heap[--sz];
        const int x = (cur >> SHF) & AND, y = cur & AND;

        //cerr << ct << ' ' << x << ' ' << y << ' ' << (cur >> SHF2) << endl;

        if (in[x][y] == true) {
            continue;
        }

        ans += cur >> SHF2;
        if (--ct == 0) break;
        in[x][y] = true;

        ll width = A[x] - A[x - 1];
        ll height = B[y] - B[y - 1];
        if (dist[x - 1][y] > height && in[x - 1][y] == false) {
            dist[x - 1][y] = height;
            heap[sz++] = (height << SHF2) | ((x - 1) << SHF) | y;
            push_heap(heap, heap+sz, greater<ll>());
        }
        if (dist[x + 1][y] > height && in[x + 1][y] == false) {
            dist[x + 1][y] = height;
            heap[sz++] = (height << SHF2) | ((x + 1) << SHF) | y;
            push_heap(heap, heap+sz, greater<ll>());
        }
        if (dist[x][y - 1] > width && in[x][y - 1] == false) {
            dist[x][y - 1] = width;
            heap[sz++] = (width << SHF2) | (x << SHF) | (y - 1);
            push_heap(heap, heap+sz, greater<ll>());
        }
        if (dist[x][y + 1] > width && in[x][y + 1] == false) {
            dist[x][y + 1] = width;
            heap[sz++] = (width << SHF2) | (x << SHF) | (y + 1);
            push_heap(heap, heap+sz, greater<ll>());
        }
    }

    cout << ans;
}

