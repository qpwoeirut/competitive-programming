#include <bits/stdc++.h>

using namespace std;

const int MN = 29;

struct Cow {
    bool breed;
    int pos;
    int val;
};

int T, N, K;
Cow A[MN];

bitset<1 << MN> V;

int min_ans = 1e9, max_ans = 0;
void try_things(const int mask) {
    if (V[mask]) return;
    V[mask] = true;

    bool maximal = true;
    for (int i=0; i<N; ++i) {
        if ((mask >> i) & 1) continue;
        for (int j=i+1; j<N; ++j) {
            if (((mask >> j) & 1) == 1 || A[i].breed == A[j].breed) continue;
            if (A[j].pos - A[i].pos > K) break;
            
            try_things(mask | (1 << i) | (1 << j));
            maximal = false;
        }
    }

    if (maximal) {
        int unpaired = 0;
        for (int i=0; i<N; ++i) {
            if (((mask >> i) & 1) == 0) {
                unpaired += A[i].val;
            }
        }
        min_ans = min(min_ans, unpaired);
        max_ans = max(max_ans, unpaired);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> T >> N >> K;
    for (int i=0; i<N; ++i) {
        char c;
        cin >> c >> A[i].pos >> A[i].val;
        A[i].breed = c == 'H';
    }

    try_things(0);

    cout << (T == 1 ? min_ans : max_ans) << '\n';
}
