//book_shop.cpp created at 12/17/20 18:35:33

#include <bits/stdc++.h>

using namespace std;

const int MN = 1005;
const int MX = 100005;
const int INIT = 1001001001;

int N, X;
int A[MN], B[MN];

int kn[MX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
    }

    fill(kn, kn+X+1, -INIT);
    kn[0] = 0;

    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=X; j>=A[i]; --j) {
            kn[j] = max(kn[j], kn[j - A[i]] + B[i]);
            ans = max(ans, kn[j]);
        }
    }

    cout << ans << endl;
}

