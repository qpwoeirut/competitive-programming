//tasks_and_deadlines.cpp created at 12/16/20 19:31:14

#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef long long ll;

const int MN = 200005;

int N;
pii A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].first >> A[i].second;
    }
    sort(A, A+N);

    ll score = 0, time = 0;
    for (int i=0; i<N; ++i) {
        time += A[i].first;
        score += A[i].second - time;
    }
    cout << score << endl;
}
