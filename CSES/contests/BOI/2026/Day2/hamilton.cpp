#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int MN = 500;

bitset<MN> G[MN];
map<pii, char> cache;

char query(int u, int v) {
    auto it = cache.find(pii(u, v));
    if (it != cache.end()) return it->second;

    cout << "? " << u + 1 << ' ' << v + 1 << '\n';
    cout.flush();

    char c;
    cin >> c;
    cache[pii(u, v)] = c;
    cache[pii(v, u)] = c == '>' ? '<' : '>';
    return cache[pii(u, v)];
}

void solve(int N) {
    cache.clear();

    vector<int> remaining;
    for (int i=0; i<N; ++i) remaining.push_back(i);

    deque<int> path;
    while (remaining.size() > 0) {
        int u = remaining.back(); remaining.pop_back();
        path.push_back(u);
        for (int j=(int)(path.size()) - 2; j>=0; --j) {
            if (query(path[j], u) == '>') break;
            swap(path[j], path[j+1]);
        }
        if (path.size() == N && query(path[0], path.back()) == '>') {
            remaining.push_back(path.front()); path.pop_front();
        }
    }

    cout << "!";
    for (int u: path) cout << ' ' << u + 1;
    cout << '\n';
    cout.flush();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, T;
    cin >> N >> T;

    mt19937 rng(8);
    for (int u=0; u<N; ++u) {
        for (int v=u + 1; v<N; ++v) {
            G[u][v] = rng() & 1;
            G[v][u] = !G[u][v];
        }
    }
    for (int u=0; u<N; ++u) {
        for (int v=0; v<N; ++v) cout << G[u][v];
        cout << '\n';
    }
    cout.flush();


    while (T --> 0) {
        solve(N);
    }
}
