#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int MN = 10000;
const int MSG = 50;

int dist[MN];
vi adj[MN];
int cur_ans = -1;
int sh = 0;
int send_message(int N, int i, int Pi) {
    adj[i].push_back(Pi);
    adj[Pi].push_back(i);

    if (i + MSG < N) return 0;

    fill(dist, dist+N, N);
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (q.size() > 0) {
        int u = q.front(); q.pop();
        for (int v: adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    int ans = 0;
    for (int u=0; u<=i; ++u) {
        if (dist[ans] <= dist[u]) {
            ans = u;
        }
    }

    if (ans == i) {
        cur_ans = i;
        sh = 20;
        return 4;
    }
    int val = (ans >> sh) & 1;
    ++sh;
    return val;
}

pii longest_path(vi S) {
    int N = S.size();
    int p = 0;
    int ans = 0;
    for (int i=max(0, N-MSG); i<N; ++i) {
        if (S[i] == 4) {
            ans = i;
            p = 30;
        } else if (p < 30) {
            ans |= S[i] << p;
            ++p;
        }
    }
    return {0, ans};
}
