//playlist.cpp created at 10/16/20 22:18:43

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

int N;
int A[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    int ans = 0, left = 0;
    map<int,int> pos;
    for (int i=0; i<N; ++i) {
        auto it = pos.emplace(A[i], i);
        if (it.SE == false) {
            while (left < it.FI->SE) {
                pos.erase(A[left++]);
            }
            ++left;
            it.FI->SE = i;
        }
        ans = max(ans, (int)pos.size());
    }

    cout << ans << endl;
}

