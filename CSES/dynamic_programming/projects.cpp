//projects.cpp created at 12/17/20 20:31:28

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pii;

struct Project {
    int a, b;
    ll p;

    inline const bool operator<(const Project& other) {
        if (a == other.a) {
            if (b == other.b) {
                return p < other.p;
            }
            return b < other.b;
        }
        return a < other.a;
    }
};

const int MN = 200005;

int N;
Project A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].a >> A[i].b >> A[i].p;
    }
    sort(A, A+N);

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    ll mx = 0;
    for (int i=0; i<N; ++i) {
        while (pq.size() > 0 && pq.top().fi < A[i].a) {
            mx = max(mx, pq.top().se);
            pq.pop();
        }

        pq.emplace(A[i].b, mx + A[i].p);
    }
    while (pq.size() > 0) {
        mx = max(mx, pq.top().se);
        pq.pop();
    }

    cout << mx << endl;
}

