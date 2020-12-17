//towers.cpp created at 12/16/20 18:47:25

#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N;
int A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    multiset<int> tops;
    for (int i=0; i<N; ++i) {
        auto it = tops.upper_bound(A[i]);
        if (it != tops.end()) {
            tops.erase(it);
        }
        tops.insert(A[i]);
    }

    cout << tops.size() << endl;
}

