//wiring.cpp created at 02/05/21 21:53:32
// got 9/10 after 14 mins, spent 45 mins fixing case where the lexicographical stuff breaks

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<string, int> psi;

const int MN = 102;
const int INIT = 1001001001;

int N, M, K;
string color[5];
set<psi> adj[MN];
int dist[MN];
map<string, int> state[MN];
vector<string> path[MN];

bool prefix(const string& a, const string& b) {
    if (a.size() > b.size()) return false;
    for (int i=0; i<a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main() {
    freopen("wiring.in", "r", stdin);
    freopen("wiring.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    int a, b;
    cin >> N >> M >> K >> a >> b;
    --a; --b;
    for (int i=0; i<K; ++i) {
        cin >> color[i];
    }
    for (int i=0; i<M; ++i) {
        int u, v;
        string c;
        cin >> u >> v >> c;
        --u; --v;

        adj[u].emplace(c, v);
        adj[v].emplace(c, u);
    }
    // hopefully there's no prefixes since idt the problem defines whether the colors are separated by a space or not when they are compared lexicographically
    for (int i=0; i<K; ++i) {
        for (int j=0; j<K; ++j) {
            assert(i == j || !prefix(color[i], color[j]));
        }
    }

    fill(dist, dist+N, INIT);
    queue<int> q;
    q.push(a);
    dist[a] = 0;
    while (q.size() > 0) {
        const int u = q.front();
        //cerr << u; for (const string s: path[u]) { cerr << ' ' << s; } cerr << endl;
        q.pop();

        if (u == b) break;

        for (const psi v: adj[u]) {
            path[u].push_back(v.fi);
            if (dist[v.se] < dist[u] + 1 || (dist[v.se] == dist[u] + 1 && path[v.se] <= path[u])) {
                path[u].pop_back();
                continue;
            }
            //cerr << v.fi << ' ' << v.se << "  ";
            //for (const string s: path[v.se]) { cerr << ' ' << s; } cerr << endl;
            //for (const string s: path[u]) { cerr << ' ' << s; } cerr << endl;
            //cerr << (path[v.se] > path[u]) << endl;
            dist[v.se] = dist[u] + 1;
            state[v.se] = state[u];
            ++state[v.se][v.fi];
            path[v.se] = path[u];
            q.push(v.se);
            path[u].pop_back();
        }
    }

    //for (int i=0; i<N; ++i) { cerr << visited[i] << ' '; } cerr << endl;
    if (dist[b] < INIT) {
        for (int i=0; i<K; ++i) {
            cout << state[b][color[i]] << '\n';
        }
    } else {
        for (int i=0; i<K; ++i) {
            cout << "-1\n";
        }
    }
}
