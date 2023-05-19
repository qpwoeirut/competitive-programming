#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N;
bitset<MN> A;
vector<int> adj[MN];

vector<int> depths[MN];
int k;
void get_depth(const int i, const int d, const int u, const int par=-1) {
    if (A[u]) { 
        depths[i].push_back(d);
        return;
    }
    for (const int v: adj[u]) {
        if (v == par) continue;
        get_depth(i, d + 1, v, u);
    }
}

int ct[MN];
void array_subtask() {
    int last = -1;
    for (int i=0; i<N; ++i) {
        if (A[i]) {
            if (last != -1) {
                ++ct[i - last - 1];
            }
            last = i;
        }
    }

    int components = A.count();
    int total_size = A.count();
    for (int k=0; k<=N; ++k) {
        components -= ct[k];
        total_size += ct[k] * k;
        //cerr << k << ' ' << components << ' ' << total_size << endl;

        if (k > 0) {
            cout << total_size + k * components << '\n';
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;

    string S;
    cin >> S;
    A = bitset<MN>(S);

    for (int i=0; i<N-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    array_subtask();
}
