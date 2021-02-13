//cables.cpp created at 02/05/21 22:38:44
// solved in 7 mins

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Device {
    int x, y, z;
};

inline const bool cmp_x(const Device& a, const Device& b) {
    return a.x < b.x;
}
inline const bool cmp_y(const Device& a, const Device& b) {
    return a.y < b.y;
}
inline const bool cmp_z(const Device& a, const Device& b) {
    return a.z < b.z;
}

const int MN = 100005;

int N;
Device A[MN];

int main() {
    freopen("cables.in", "r", stdin);
    freopen("cables.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y >> A[i].z;
    }

    ll ans = 0;
    sort(A, A+N, cmp_x);
    ll prv = A[0].x;
    ll dist = 0;
    for (ll i=0; i<N; ++i) {
        dist += (A[i].x - prv) * i;
        ans += dist;
        prv = A[i].x;
    }
    sort(A, A+N, cmp_y);
    prv = A[0].y;
    dist = 0;
    for (ll i=0; i<N; ++i) {
        dist += (A[i].y - prv) * i;
        ans += dist;
        prv = A[i].y;
    }
    sort(A, A+N, cmp_z);
    prv = A[0].z;
    dist = 0;
    for (ll i=0; i<N; ++i) {
        dist += (A[i].z - prv) * i;
        ans += dist;
        prv = A[i].z;
    }

    cout << ans << endl;
}

