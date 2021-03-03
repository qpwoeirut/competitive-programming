#include <bits/stdc++.h>
#include "coolrot.h"

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pii;

const int MN = 100005;

int N, Q;
int A[MN];
pii score[MN];
int best[MN];

ll BIT[MN];
void inc(int idx) {
    for (; idx<=N; idx+=(idx&-idx)) ++BIT[idx];
}
ll query(int idx) {
    ll ret = 0;
    for (; idx>0; idx-=(idx&-idx)) ret += BIT[idx];
    return ret;
}

void init(const int n, const int a[], const int q) {
    N = n;
    Q = q;
    for (int i=0; i<N; ++i) {
        A[i] = a[i] + 1;
    }

    ll invs = 0;
    for (int i=N-1; i>=0; --i) {
        invs += query(A[i]);
        inc(A[i]);
    }

    for (int i=0; i<N; ++i) {
        score[i] = pii(invs, A[i]);
        invs -= A[i] - 1;
        invs += N - A[i];
    }

    for (int i=1; i<=N; ++i) {
        if (N % i == 0) {
            best[i] = 0;
            pii val = score[0];
            for (int j=i; j<N; j+=i) {
                if (val > score[j]) {
                    val = score[j];
                    best[i] = j;
                }
            }
        }
    }
}

int gcd(const int a, const int b) {
    return b ? gcd(b, a % b) : a;
}

void query(int m, const int ds[]) {
    if (m == 0) return;

    int g = ds[0];
    for (int i=1; i<m; ++i) {
        g = gcd(g, ds[i]);
    }

    int target = best[g];
    if (target == 0) return;
    for (int i=0; i<m; ++i) {
        if (target % ds[i] == 0) {
            update(ds[i], target / ds[i]);
            return;
        }
    }

    for (int i=0; i<m; ++i) {
        for (int j=i+1; j<m; ++j) {
            if (gcd(ds[i], ds[j]) == g) {
                for (int k=1; k<ds[i]; ++k) {
                    target -= ds[j];
                    if (target < 0) target += N;
                    if (target % ds[i] == 0) {
                        update(ds[j], k);
                        update(ds[i], target / ds[i]);
                        return;
                    }
                }
            }
        }
    }
}
/*
6 1
1 3 4 0 2 5
1
2
*/
