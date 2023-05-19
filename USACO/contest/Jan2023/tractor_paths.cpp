#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;
const int LG = 18;

int N, Q;
int lft[MN], rht[MN];
int jump[LG][MN];
int special[MN]; int M = 0;

int distance(int a, const int b) {
    if (a == b) return 0;
    assert(a < b);

    //cerr << a << ' ' << b << '\n';
    int dist = 0;
    for (int i=LG-1; i>=0; --i) {
        if (jump[i][a] < b) {
            a = jump[i][a];
            dist += 1 << i;
        }
    }
    a = jump[0][a];  // possible that a > b
    ++dist;

    //cerr << a << ' ' << b << ' ' << dist << ' ' << "\n\n";

    return dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    string S;
    cin >> S;

    int slow = 0, fast = 0;
    for (int i=0; i<2*N; ++i) {
        if (S[i] == 'L') lft[fast++] = i;
        else if (S[i] == 'R') rht[slow++] = i;
        else assert(0);
    }
    assert(slow == N && fast == N);

    for (int u=0; u<N; ++u) {
        jump[0][u] = (lower_bound(lft, lft+N, rht[u]) - lft) - 1;
    }
    for (int i=1; i<LG; ++i) {
        for (int u=0; u<N; ++u) {
            jump[i][u] = jump[i-1][jump[i-1][u]];
        }
    }

    cin >> S;
    for (int i=0; i<N; ++i) {
        if (S[i] == '1') {
            special[M++] = i;
        }
    }

    int a, b;
    for (int q=0; q<Q; ++q) {
        cin >> a >> b; --a; --b;
        const int dist = distance(a, b);

        int ct = 0;
        for (int i=0; i<M; ++i) {
            const int u = special[i];
            if (a <= u && u <= b && distance(a, u) + distance(u, b) == dist) ++ct;
        }

        cout << dist << ' ' << ct << '\n';
    }
}
