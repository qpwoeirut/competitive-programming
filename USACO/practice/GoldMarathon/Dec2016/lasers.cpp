#include <bits/stdc++.h>

using namespace std;

#define pos first
#define dst second

typedef pair<int,int> pii;

struct Mirror {
    int x, y;
    int idx;
};

inline const bool cmp_x(const Mirror& a, const Mirror& b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
inline const bool cmp_y(const Mirror& a, const Mirror& b) {
    if (a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

const int MN = 100005;

int N;
Mirror A[MN];

int adj[MN << 2];
int dist[MN << 2];

bool chmn(int& a, const int b) {return (a>b) ? ((a=b) || true) : false;}

int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    cin >> A[0].x >> A[0].y >> A[N+1].x >> A[N+1].y;
    A[0].idx = 0;
    A[N+1].idx = (N+1) << 2;

    for (int i=1; i<=N; ++i) {
        cin >> A[i].x >> A[i].y;
        A[i].idx = i << 2;
    }

    ++N;
    fill(adj, adj+(MN << 2), -1);
    sort(A, A+N+1, cmp_x);
    for (int i=1; i<=N; ++i) {
        if (A[i-1].x == A[i].x) {
            adj[A[i-1].idx + 2] = A[i].idx + 2;
            adj[A[i].idx + 0] = A[i-1].idx + 0;
        }
    }
    sort(A, A+N+1, cmp_y);
    for (int i=1; i<=N; ++i) {
        if (A[i-1].y == A[i].y) {
            adj[A[i-1].idx + 1] = A[i].idx + 1;
            adj[A[i].idx + 3] = A[i-1].idx + 3;
        }
    }

    fill(dist, dist+(MN << 2), 1001001001);
    deque<pii> q;
    for (int i=0; i<4; ++i) {
        dist[i] = 0;
        q.emplace_back(i, 0);
    }
    while (q.size() > 0) {
        const pii cur = q.front(); q.pop_front();

        const int id = cur.pos >> 2, dir = cur.pos & 3;
        //cerr << "id,dir,dst: " << id << ' ' << dir << ' ' << cur.dst << endl;
        if (id == N) {
            cout << cur.dst << endl;
            return 0;
        }
        const int turn_left = (id << 2) | ((dir + 3) & 3), turn_right = (id << 2) | ((dir + 1) & 3);
        //cerr << turn_left << ' ' << dist[turn_left] << endl;
        //cerr << turn_right << ' ' << dist[turn_right] << endl;
        if (chmn(dist[turn_left], cur.dst + 1)) {
            q.emplace_back(turn_left, dist[turn_left]);
        }
        if (chmn(dist[turn_right], cur.dst + 1)) {
            q.emplace_back(turn_right, dist[turn_right]);
        }
        if (adj[cur.pos] != -1 && chmn(dist[adj[cur.pos]], cur.dst)) {
            //cerr << "adj id,dir: " << (adj[cur.pos] >> 2) << ' ' << (adj[cur.pos] & 3) << endl;
            q.emplace_front(adj[cur.pos], dist[adj[cur.pos]]);
        }
    }
    cout << -1 << endl;
}
