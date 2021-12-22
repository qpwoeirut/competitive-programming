#include <bits/stdc++.h>

using namespace std;

char A[10];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i=0; i<10; ++i) {
        cin >> A[i];
    }
    int N;
    cin >> N;


    string ans = "";
    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;
        ans += A[x];
    }

    cout << ans << '\n';
}
