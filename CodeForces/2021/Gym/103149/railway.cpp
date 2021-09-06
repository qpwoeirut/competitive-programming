//railway.cpp created at 09/05/21 20:35:00

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

using pii=pair<int,int>;

const int MN = 2003;
const int MT = 100005;

int N, M;
int S, T;

int start[MT], finish[MT];
int B[MN], C[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> S >> T >> N >> M;
    for (int i=0; i<T; ++i) {
        cin >> start[i];
    }
    for (int i=0; i<T; ++i) {
        cin >> finish[i];
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
    }
    for (int i=0; i<M; ++i) {
        cin >> C[i];
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            int m = (S + C[j] - B[i]);
            bool par = m & 1;
            m = (m+1) >> 1;
            int idx = (lower_bound(finish, finish+T, m)) - finish;
            if (idx < T && ((par && start[idx] < m && m <= finish[idx]) || (start[idx] < m && m < finish[idx]))) ++ans;
        }
    }

    cout << (ans ? "YES" : "NO") << '\n';
}

