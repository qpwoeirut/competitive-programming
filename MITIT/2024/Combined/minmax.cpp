#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int main() {
    cin.tie(0)->sync_with_stdio(0);


    int N;
    cin >> N;
    deque<int> A(N);
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());
    bool turn = true;
    while (A.size() > 1) {
        if (turn) {
            A.pop_front();
        } else {
            A.pop_back();
        }
        turn = !turn;
    }

    cout << A[0] << '\n';
}
