//1174f.cpp created at 01/23/21 12:52:13

#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;
const int LG = 20;

int query_dist(const int u) {
    cout << "d " << u+1 << endl;
    int ret;
    cin >> ret;
    assert(ret != -1);
    return ret;
}

int query_next(const int u) {
    cout << "s " << u+1 << endl;
    int ret;
    cin >> ret;
    assert(ret != -1);
    return ret - 1;
}

int N;
set<int> adj[MN];
int dist[MN];
int start[MN], finish[MN];
int anc[LG][MN];

int cur_time = 0;
void prep(const int u, const int par) {
    start[u] = cur_time++;
    anc[0][u] = par;
    for (const int v: adj[u]) {
        if (v == par) continue;
        dist[v] = dist[u] + 1;
        prep(v, u);
    }
    finish[u] = cur_time;
}

void calc_dist(const int u, const int par) {
    for (const int v: adj[u]) {
        if (v == par) continue;
        dist[v] = dist[u] + 1;
        calc_dist(v, u);
    }
}

bool is_anc(const int u, const int v) {
    return start[u] <= start[v] && finish[v] <= finish[u];
}

int lca(int u, const int v) {
    if (is_anc(u, v)) return u;
    if (is_anc(v, u)) return v;
    for (int i=LG-1; i>=0; --i) {
        if (anc[i][u] == -1 || is_anc(anc[i][u], v)) continue;
        u = anc[i][u];
    }
    return anc[0][u];
}

bool in[MN];
int ct[MN];
void calc_ct(const int u, const int par) {
    if (in[u]) ct[u] = 1;
    else ct[u] = 0;
    for (const int v: adj[u]) {
        if (v == par) continue;
        calc_ct(v, u);
        ct[u] += ct[v];
    }
}

int find_centroid(const int u, const int par) {
    for (const int v: adj[u]) {
        if (v == par) continue;
        if (ct[v] >= ct[0]/2) {
            return find_centroid(v, u);
        }
    }
    return u;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    dist[0] = 0;
    prep(0, -1);
    
    for (int i=1; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            if (anc[i-1][j] == -1) anc[i][j] = -1;
            else anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }

    int d = query_dist(0);

    set<int> cur;
    for (int i=0; i<N; ++i) {
        if (dist[i] == d) {
            cur.insert(i);
            in[i] = true;
        }
    }

    int prev = 0;
    int lo = 0, hi = N;
    while (cur.size() > 1) {
        calc_ct(0, -1);
        int centroid = find_centroid(0, -1);

        while (cur.size() > 1 && centroid != prev) {
            d = query_dist(centroid);
            dist[centroid] = 0;
            calc_dist(centroid, -1);

            for (auto it=cur.begin(); it!=cur.end(); ) {
                if (dist[*it] != d) {
                    in[*it] = false;
                    it = cur.erase(it);
                }
                else ++it;
            }

            prev = centroid;

            calc_ct(0, -1);
            centroid = find_centroid(0, -1);
        }
        if (cur.size() == 1) break;

        //cerr << "lo,hi: " << lo << ' ' << hi << endl;
        int group_lca = -1;
        for (auto it=cur.begin(); it!=cur.end(); ) {
            if (finish[*it] <= lo || hi <= start[*it]) {
                in[*it] = false;
                it = cur.erase(it);
            } else {
                group_lca = group_lca == -1 ? *it : lca(group_lca, *it);
                //cerr << *it << endl;
                ++it;
            }
        }
        assert(group_lca != -1);

        if (cur.size() == 1) break;

        int nxt = query_next(group_lca);
        lo = start[nxt];
        hi = finish[nxt];
    }

    assert(cur.size() == 1);
    cout << "! " << *cur.begin() + 1 << endl;
}
/*
10 4
1 2
2 3
3 4
1 8
8 9
9 10
2 6
6 7
3 5
*/
