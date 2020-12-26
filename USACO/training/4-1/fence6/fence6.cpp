/*
ID: zhongbr1
TASK: fence6
LANG: C++14
*/

//fence6.cpp created at 12/23/20 23:02:07

#include <bits/stdc++.h>

using namespace std;

const int MN = 105;

struct Edge {
    set<int> adj1, adj2;
    int len;
    int last;
};

int N;
Edge A[MN];

int main() {
    freopen("fence6.in", "r", stdin);
    freopen("fence6.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    vector<Edge> edges;
    queue<Edge> q;
    for (int i=0; i<N; ++i) {
        int idx, n1, n2;
        cin >> idx;
        --idx;
        A[idx].last = idx;
        cin >> A[idx].len >> n1 >> n2;
        for (int j=0; j<n1; ++j) {
            int x;
            cin >> x;
            A[idx].adj1.insert(x - 1);
        }
        for (int j=0; j<n2; ++j) {
            int x;
            cin >> x;
            A[idx].adj2.insert(x - 1);
        }

        q.push(A[idx]);
    }

    int ans = 256 * 100;
    while (q.size() > 0) {
        const Edge cur = q.front(); q.pop();

        if (cur.len >= ans) continue;
        if (cur.adj1.count(cur.last)) {
            ans = cur.len;
            continue;
        }

        for (const int v: cur.adj2) {
            Edge nxt = cur;
            if (A[v].adj1.count(cur.last)) {
                nxt.adj2 = A[v].adj2;
            } else {
                assert(A[v].adj2.count(cur.last));
                nxt.adj2 = A[v].adj1;
            }
            nxt.last = v;
            nxt.len += A[v].len;
            q.push(nxt);
        }
    }

    cout << ans << endl;
}
