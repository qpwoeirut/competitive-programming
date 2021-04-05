#include "teams.h"
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 500005;

int N;
pii A[MN];
void init(int n, int a[], int b[]) {
    N = n;
    for (int i=0; i<N; ++i) {
        A[i] = pii(a[i], b[i]);
    }
    sort(A, A+N);
}

struct cmps {
    inline bool operator()(const pii& a, const pii& b) {
        return a.se > b.se || (a.se == b.se && a.fi > b.fi);
    }
};

int can(int M, int K[]) {
    sort(K, K+M);

    int idx = 0;
    priority_queue<pii, vector<pii>, cmps> pq;
    for (int i=0; i<M; ++i) {
        while (idx < N && A[idx].fi <= K[i]) {
            pq.push(A[idx]);
            ++idx;
        }

        int rem = K[i];
        while (rem > 0 && pq.size() > 0) {
            if (pq.top().fi <= K[i] && K[i] <= pq.top().se) --rem;
            pq.pop();
        }
        if (rem > 0) return 0;
    }
    return 1;
}
