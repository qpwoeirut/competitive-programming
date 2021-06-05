//room_allocation_cleaner.cpp created at 05/14/21 22:15:26

#include <bits/stdc++.h>

using namespace std;

using pii = pair<int,int>;

#define fi first
#define se second

struct Person {
    int start, finish;
    int idx;

    inline const bool operator<(const Person& o) const {
        return start < o.start || (start == o.start && idx < o.idx);
    }
};

const int MN = 200000;

int N, K;
Person A[MN];
int ans[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].start >> A[i].finish;
        A[i].idx = i;
    }
    sort(A, A+N);

    priority_queue<pii, vector<pii>, greater<pii>> rooms;
    K = 0;
    for (int i=0; i<N; ++i) {
        if (rooms.empty() || rooms.top().fi >= A[i].start) {
            rooms.emplace(A[i].finish, ++K);
            ans[A[i].idx] = K;
        } else {
            rooms.emplace(A[i].finish, rooms.top().se);
            ans[A[i].idx] = rooms.top().se;
            rooms.pop();
        }
    }

    cout << K << '\n';
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}

