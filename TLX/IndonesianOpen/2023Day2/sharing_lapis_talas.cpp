//sharing_lapis_talas.cpp created at 08/31/23 21:28:47

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 100005;
int N, K, Q;
vector<int> adj[MN];

int value[MN];
ll dfs(int u) {
    ll ret = 0;
    for (int v: adj[u]) {
        ret += dfs(v);
        value[u] = max(value[u], value[v] + 1);
    }
    return ret + value[u];
}

int A[MN];
int perm[MN];
ll simulate() {
    copy(perm, perm+N, A);
    bool done = false;
    ll x = 0;
    while (!done) {
        done = true;

        for (int i=N-1; i>=0 && done; --i) {
            int mn = A[i];
            for (int v: adj[i]) {
                mn = min(mn, A[v]);
            }
            for (int v: adj[i]) {
                if (mn == A[v]) {
                    swap(A[i], A[v]);
                    ++x;
                    done = false;
                    break;
                }
            }
        }
    }
    //cerr << "X = " << x << endl;
    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K >> Q;

    for (int i=1; i<N; ++i) {
        int p;
        cin >> p; --p;
        adj[p].push_back(i);
    }

    if (K == 0) {
        cout << "YA\n";
        for (int i=1; i<=N; ++i) {
            cout << i << ' ';
        }
        cout << endl;
        return 0;
    }

    for (int i=0; i<N; ++i) {
        perm[i] = i;
    }
    do {
        ll x = simulate();
        if (x == K) {
            cout << "YA\n";
            if (Q) {
                for (int i=0; i<N; ++i) {
                    cout << perm[i] + 1 << ' ';
                }
                cout << endl;
            }
            return 0;
        }
    } while (next_permutation(perm, perm+N));
    
    cout << "TIDAK\n";
}

