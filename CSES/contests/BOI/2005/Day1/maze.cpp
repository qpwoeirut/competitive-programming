//maze.cpp created at 10/01/20 18:06:30

#include <bits/stdc++.h>

using namespace std;

#define r first
#define c second

typedef pair<int,int> pii;

const int MN = 501;

int C, R;
int dist[MN][MN][2];

struct Edge {
    pii u, v;
    int type;

    Edge(int ur, int uc, int vr, int vc, int t) {
        u = pii(ur, uc);
        v = pii(vr, vc);
        type = t;
    }
};

struct Item {
    pii pos;
    int last;
    int dst;

    Item(pii _pos, int _last, int _dist) {
        pos = _pos;
        last = _last;
        dst = _dist;
    }

    const bool operator<(const Item& other) const {
        return dst > other.dst;
    }
    int get_dist() {
        return dist[pos.r][pos.c][last];
    }
    bool update_dist() {
        if (dist[pos.r][pos.c][last] > dst) {
            dist[pos.r][pos.c][last] = dst;
            return true;
        }
        return false;
    }

    void print() {
        //cerr << "(" << pos.r << ',' << pos.c << ") " << last << ' ' << dst << endl;
    }
};

vector<Edge> adj[MN][MN];

void add_edge(int ur, int uc, int vr, int vc, int t) {
    adj[ur][uc].push_back(Edge(ur, uc, vr, vc, t));
    adj[vr][vc].push_back(Edge(vr, vc, ur, uc, t));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    pii start, exit;

    cin >> C >> R;
    cin >> start.c >> start.r >> exit.c >> exit.r;

    string s;
    for (int i=0; i<2*R + 1; ++i) {
        cin >> s;
        int row = (i+1) >> 1;
        if ((i & 1) == 0) {
            assert(s.size() == C);
            for (int j=0; j<C; ++j) {
                if (s[j] == 'n') continue;
                assert(s[j] == 'b' || s[j] == 'w');
                add_edge(row, j, row, j+1, s[j] == 'b');
            }
        } else {
            assert(s.size() == C * 2 + 1);
            for (int j=0; j<2*C + 1; ++j) {
                if (s[j] == 'n') continue;
                assert(s[j] == 'b' || s[j] == 'w');
                int col = j >> 1;
                if ((j & 1) == 0) {
                    add_edge(row, col, row-1, col, s[j] == 'b');
                } else {
                    add_edge(row, col, row-1, col+1, s[j] == 'b');
                }
            }
        }
    }

    for (int i=0; i<=R; ++i) {
        for (int j=0; j<=C; ++j) {
            dist[i][j][0] = dist[i][j][1] = 1001001001;
        }
    }

    dist[start.r][start.c][0] = dist[start.r][start.c][1] = 0;
    priority_queue<Item> pq;
    pq.push(Item(start, 0, 0));
    pq.push(Item(start, 1, 0));

    while (pq.size() > 0) {
        Item cur = pq.top(); pq.pop();
        cur.print();

        if (cur.get_dist() < cur.dst) {
            continue;
        }

        if (cur.pos == exit) {
            cout << cur.dst << endl;
            return 0;
        }

        for (auto it=adj[cur.pos.r][cur.pos.c].begin(); it!=adj[cur.pos.r][cur.pos.c].end(); ++it) {
            if (it->type == cur.last) continue;
            Item nxt(it->v, it->type, cur.dst + 1);
            if (nxt.update_dist()) {
                pq.push(nxt);
            }
        }
    }

    assert(false);
}
/*
2 1
0 0 2 1
bb
nwwnw
bn

5 4
0 2 5 2
nnbnn
nnnwwbwnnnn
nbbbn
nnwbwwbwwnn
bwwww
nnbwbbwwbnn
nwwwn
nnnnbwbbnnn
nnwnn
*/
