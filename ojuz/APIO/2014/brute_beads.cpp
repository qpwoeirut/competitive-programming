#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 11;

void chmx(ll& a, ll b) {if (a<b) a=b;}

struct Edge {
    int from, to;
    ll len;

    Edge() {
        from = to = len = 0;
    }
    Edge(int _from, int _to, ll _len) {
        from = _from;
        to = _to;
        len = _len;
    }

    inline const bool operator<(const Edge& other) const {
        if (len != other.len) {
            return len < other.len;
        }
        if (from != other.from) {
            return from < other.from;
        }
        return to < other.to;
    }
    inline const bool operator>(const Edge& other) const {
        return other < *this;
    }
};

int N;
set<Edge> adj[MN];
bool leaf[MN], real_leaf[MN];
Edge edge[MN];

ll ans = 0;
int type[MN];
bool in[MN];
void recurse() {
    bool done = true;
    for (int i=0; i<N-1; ++i) {
        if (type[i] == 0) {
            done = false;
            if (in[edge[i].from] == false) continue;
            for (int j=0; j<N-1; ++j) {
                if (i == j) continue;
                if (edge[i].to == edge[j].from && in[edge[i].from] && in[edge[i].to] == false && in[edge[j].to] == false) {
                    in[edge[i].to] = in[edge[i].from] = in[edge[j].to] = in[edge[j].from] = true;
                    type[i] = 1;
                    type[j] = 1;
                    recurse();
                    in[edge[i].to] = in[edge[j].to] = false;
                    type[i] = type[j] = 0;
                }
            }

            in[edge[i].to] = true;
            type[i] = 2;
            recurse();
            type[i] = 0;
            in[edge[i].to] = false;
        }    
    }
                
    if (done) {
        ll total = 0;
        for (int i=0; i<N-1; ++i) {
            if (type[i] == 1) total += edge[i].len;
        }
        ans = max(ans, total);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N-1; ++i) {
        cin >> edge[i].from >> edge[i].to >> edge[i].len;
        --edge[i].from;
        --edge[i].to;
        adj[edge[i].from].insert(edge[i]);
        adj[edge[i].to].insert(Edge(edge[i].to, edge[i].from, edge[i].len));
    }
    for (int i=0; i<N; ++i) {
        in[i] = true;
        recurse();
        in[i] = false;
    }

    cout << ans << endl;
}
/*
5
1 2 10
1 3 40
1 4 15
1 5 20

10
4 10 2
1 2 21
1 3 13
6 7 1
7 9 5
2 4 3
2 5 8
1 6 55
6 8 34
*/

