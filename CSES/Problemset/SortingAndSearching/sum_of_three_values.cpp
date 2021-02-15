//sum_of_three_values.cpp created at 12/16/20 19:40:52

#include <bits/stdc++.h>

using namespace std;

const int MN = 5005;

int N, X;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    map<int,vector<int>> pos;
    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        pos[A[i]].push_back(i);
    }
    for (auto x: pos) {
        sort(x.second.begin(), x.second.end());
    }

    for (int i=0; i<N; ++i) {
        if (A[i] + 2 > X) continue;
        for (int j=i+1; j<N; ++j) {
            if (A[i] + A[j] + 1 > X) continue;
            auto it = pos.find(X - A[i] - A[j]);
            if (it != pos.end()) {
                if (it->second.back() <= i) continue;
                int above = *upper_bound(it->second.begin(), it->second.end(), i);
                if (above < j) {
                    cout << i+1 << ' ' << above + 1 << ' ' << j+1 << endl;
                    return 0;
                }
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}

