#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;
typedef long long ll;

const int MN = 50001;

ll N;
int A[MN][5];

map<vector<int>, int> ct;

int subsets[32];
int order[32];

inline const bool cmp_bits(const int a, const int b) {
    int cta = 0, ctb = 0;
    int na = a, nb = b;
    while (na > 0) {
        cta += na & 1;
        na >>= 1;
    }
    while (nb > 0) {
        ctb += nb & 1;
        nb >>= 1;
    }
    if (cta == ctb) return a < b;
    return cta < ctb;
}

vector<int> cur;
void recurse(const int i, const int idx, const int mask) {
    if (idx == 5) {
        if (mask == 0) return;
        subsets[mask] = ct[cur]++;
        return;
    }
    recurse(i, idx+1, mask);
    cur.push_back(A[i][idx]);
    recurse(i, idx+1, mask + (1 << idx));
    cur.pop_back();
}


int main() {
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<5; ++j) {
            cin >> A[i][j];
        }
        sort(A[i], A[i] + 5);
    }

    for (int i=0; i<32; ++i) order[i] = i;
    sort(order, order+32, cmp_bits);

    ll ans = (N * (N - 1)) >> 1;
    for (int i=0; i<N; ++i) {
        recurse(i, 0, 0);
        for (int j=31; j>0; --j) {
            const int x = order[j];
            for (int k=(x - 1) & x; k>0; k=(k - 1) & x) {
                subsets[k] -= subsets[x];
            }
        }

        for (int j=1; j<32; ++j) {
            ans -= subsets[j];
        }
    }

    cout << ans << endl;
}

